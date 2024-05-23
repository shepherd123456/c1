//
// Created by shepherd on 21.5.24.
//

#ifndef REFRESH_TOKEN_REPOSITORY_HPP
#define REFRESH_TOKEN_REPOSITORY_HPP

#include <string>
#include <sqlite_orm/sqlite_orm.h>
#include <c1/app/storage.hpp>

namespace c1 {

class RefreshTokenRepository {
public:
    explicit RefreshTokenRepository(storage_t& storage);
    void deleteAllByEmail(const std::string& email);
    void deleteByToken(const std::string& token);

private:
    storage_t storage_;
};

} // c1

#endif //REFRESH_TOKEN_REPOSITORY_HPP
