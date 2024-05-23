//
// Created by shepherd on 30.4.24.
//

#include <c1/user/user.hpp>
#include "c1/bcrypt/bcrypt.h"

namespace c1
{
User::User(const crow::json::rvalue& json)
{
    email = json["email"].s();
    password = bcrypt::generateHash(json["password"].s());
}

bool User::isPasswordValid(const std::string& pass) const
{
    return bcrypt::validatePassword(pass, password);
}

crow::json::wvalue User::toJson() const
{
    return {
        {"email", email}
    };
}
} // c1
