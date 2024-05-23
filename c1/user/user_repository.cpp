//
// Created by shepherd on 21.5.24.
//

#include "user_repository.hpp"

#include <c1/userrole/user_role.hpp>
#include <c1/refreshtoken/refersh_token.hpp>

namespace c1
{
UserRepository::UserRepository(storage_t& storage): storage_(storage)
{
}

std::vector<User> UserRepository::getAll() const
{
    return storage_.get_all<User>();
}

User UserRepository::findByEmail(const std::string& email)
{
    const auto users = storage_.get_all<User>(sqlite_orm::where(sqlite_orm::c(&User::email) == email));
    if (users.empty())
    {
        throw std::runtime_error("User not found");
    }
    auto user = users.front();
    user.roles = getRolesForUser(user.id);
    return user;
}

User UserRepository::findByRefreshToken(const std::string& refreshToken)
{
    const auto tokens = storage_.get_all<RefreshToken>(
        sqlite_orm::where(sqlite_orm::c(&RefreshToken::token) == refreshToken));
    if (tokens.empty())
    {
        throw std::runtime_error("Refresh token not found");
    }
    auto user = storage_.get<User>(tokens.front().user_id);
    user.roles = getRolesForUser(user.id);
    return user;
}

void UserRepository::appendRole(const std::string& email, const std::string& roleName)
{
    const auto users = storage_.get_all<User>(sqlite_orm::where(sqlite_orm::c(&User::email) == email));
    if (users.empty())
    {
        throw std::runtime_error("User not found");
    }

    const auto roles = storage_.get_all<Role>(sqlite_orm::where(sqlite_orm::c(&Role::name) == roleName));
    if (roles.empty())
    {
        throw std::runtime_error("Role not found");
    }

    const UserRole userRole{users.front().id, roles.front().id};
    storage_.insert(userRole);
}

std::vector<Role> UserRepository::getRolesForUser(const int userId)
{
    return storage_.get_all<Role>(
        sqlite_orm::join<UserRole>(sqlite_orm::on(sqlite_orm::c(&UserRole::role_id) == &Role::id)),
        sqlite_orm::where(sqlite_orm::c(&UserRole::user_id) == userId)
    );
}
} // c1
