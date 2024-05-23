//
// Created by shepherd on 1.5.24.
//

#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <string>
#include <vector>
#include <utility>
#include <sqlite_orm/sqlite_orm.h>

#include <c1/user/user.hpp>
#include <c1/role/role.hpp>
#include <c1/userrole/user_role.hpp>
#include <c1/refreshtoken/refersh_token.hpp>


namespace c1
{
inline auto init_storage(std::string dbname = "c1.db")
{
    using namespace sqlite_orm;
    auto storage = make_storage(std::move(dbname),
                                make_table("app_user",
                                           make_column("id", &User::id, primary_key().autoincrement()),
                                           make_column("email", &User::email),
                                           make_column("password", &User::password)),
                                make_table("role",
                                           make_column("id", &Role::id, primary_key().autoincrement()),
                                           make_column("name", &Role::name)),
                                make_table("refresh_token",
                                           make_column("id", &RefreshToken::id, primary_key().autoincrement()),
                                           make_column("token", &RefreshToken::token),
                                           make_column("user_id", &RefreshToken::user_id)),
                                make_table("user_roles",
                                           make_column("user_id", &UserRole::user_id),
                                           make_column("role_id", &UserRole::role_id),
                                           foreign_key(&UserRole::user_id).references(&User::id),
                                           foreign_key(&UserRole::role_id).references(&Role::id))
    );
    storage.sync_schema();

    if(storage.count<Role>() == 0)
    {
        std::vector<Role> roles = {{"USER"}, {"ADMIN"}};
        storage.insert_range(roles.begin(), roles.end());
    }

    return storage;
}

using storage_t = decltype(init_storage());

class Storage
{
public:
    Storage(): storage_(init_storage())
    {
    }

    template <typename T>
    T getObject(int id)
    {
        return storage_.get<T>(id);
    }

    template <typename T>
    std::shared_ptr<T> createObject(const crow::json::rvalue& json)
    {
        auto clazz = std::make_shared<T>(json);
        clazz->id = storage_.insert(*clazz);
        return clazz;
    }

    storage_t& get()
    {
        return storage_;
    }

private:
    storage_t storage_;
};
} // c1

#endif //STORAGE_HPP
