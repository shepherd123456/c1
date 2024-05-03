//
// Created by shepherd on 2.5.24.
//

#ifndef JWT_HPP
#define JWT_HPP

#include <string>
#include <crow/json.h>
#include "jwt.hpp"
#include <jwt-cpp/jwt.h>

namespace c1::jwt
{
const std::string secret =
    "b4947c11d199e5a657818ba14b9097c59c189f2122f79d0b7aa2cf434438701fe7a628eb0cbf0ac68ff9c48788d92712e250a8a0cfe33fcb433d67b8ec97a505";

inline std::string generateToken(int seconds, const crow::json::wvalue& context)
{
    picojson::value json;
    parse(json, context.dump());
    return ::jwt::create()
           .set_issued_at(std::chrono::system_clock::now())
           .set_expires_in(std::chrono::seconds(seconds))
           .set_payload_claim("context", json)
           .sign(::jwt::algorithm::hs256(secret));
}

inline crow::json::rvalue decodeToken(const std::string& token)
{
    const auto t = ::jwt::decode(token);
    const auto tok = crow::json::load(t.get_payload());
    const int exp = static_cast<int>(tok["exp"]);
    const auto now = std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
    if (now > exp)
    {
        throw std::runtime_error("jwt token has expired");
    }
    return tok;
}

inline bool validateToken(const std::string& token, const std::string& email)
{
    const auto t = decodeToken(token);
    return t["context"]["email"] == email;
}

inline std::string extractEmail(const std::string& token)
{
    const auto t = decodeToken(token);
    return std::string(t["context"]["email"]);
}

inline std::vector<std::string> extractRoles(const std::string& token)
{
    std::vector<std::string> ret;
    const auto t = decodeToken(token);
    const auto vec = static_cast<crow::json::rvalue>(t["context"]["roles"]).lo();
    for (const auto& i : vec)
    {
        ret.push_back(i.s());
    }
    return ret;
}
} // c1::jwt

#endif //JWT_HPP
