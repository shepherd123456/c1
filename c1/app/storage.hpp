//
// Created by shepherd on 1.5.24.
//

#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <string>

#include <sqlite_orm/sqlite_orm.h>
#include <c1/user/user.hpp>
#include <utility>


namespace c1
{
inline auto init_storage(std::string dbname = "c1.db")
{
    using namespace sqlite_orm;
    auto storage = make_storage(std::move(dbname),
                                make_table("app_user",
                                           make_column("id", &User::id, primary_key().autoincrement()),
                                           make_column("email", &User::email),
                                           make_column("password", &User::password))
    );
    storage.sync_schema();
    return storage;
}

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
    void createObject(const crow::json::rvalue& json)
    {
        T clazz(json);
        int inserted_id = storage_.insert(clazz);
        clazz.id = inserted_id;
    }

private:
    decltype(init_storage()) storage_;
};
} // c1

#endif //STORAGE_HPP
