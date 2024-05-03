//
// Created by shepherd on 30.4.24.
//

#include "user.hpp"
#include <c1/app/utils.hpp>

namespace c1
{
User::User(const crow::json::rvalue& json)
{
    email = json["email"].s();
    password = utils::sha256(json["password"].s());
}

crow::json::wvalue User::toJson() const
{
    return {
        {"id", id},
        {"email", email}
    };
}
} // c1
