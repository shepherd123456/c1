//
// Created by shepherd on 21.5.24.
//

#include "refresh_token_repository.hpp"

namespace c1 {
RefreshTokenRepository::RefreshTokenRepository(decltype(init_storage())& storage): storage_(storage) {}

void RefreshTokenRepository::deleteAllByEmail(const std::string& email)
{
    if (const auto users = storage_.get_all<User>(sqlite_orm::where(sqlite_orm::c(&User::email) == email)); !users.empty()) {
        storage_.remove_all<RefreshToken>(sqlite_orm::where(sqlite_orm::c(&RefreshToken::user_id) == users.front().id));
    }
}

void RefreshTokenRepository::deleteByToken(const std::string& token)
{
    storage_.remove_all<RefreshToken>(sqlite_orm::where(sqlite_orm::c(&RefreshToken::token) == token));
}
} // c1