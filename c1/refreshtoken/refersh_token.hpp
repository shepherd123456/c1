//
// Created by shepherd on 21.5.24.
//

#ifndef REFERSH_TOKEN_HPP
#define REFERSH_TOKEN_HPP

#include <string>
#include <crow/json.h>

namespace c1
{
struct RefreshToken
{
    RefreshToken() = default;
    RefreshToken(const crow::json::rvalue& json);
    [[nodiscard]] crow::json::wvalue toJson() const;
    int id{};
    std::string token;
    int user_id{};
};
} // c1

#endif //REFERSH_TOKEN_HPP
