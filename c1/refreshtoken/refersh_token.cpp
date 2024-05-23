//
// Created by shepherd on 21.5.24.
//

#include "refersh_token.hpp"

namespace c1 {
RefreshToken::RefreshToken(const crow::json::rvalue& json)
{
    token = json["token"].s();
    user_id = json["user_id"].i();
}

crow::json::wvalue RefreshToken::toJson() const
{
    return {
        {"token", token},
        {"user_id", user_id}
    };
}
} // c1