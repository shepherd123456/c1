//
// Created by shepherd on 2.5.24.
//

#include <iostream>
#include <string>
#include <crow/app.h>
#include <c1/authentication/authentication_controller.hpp>
#include <c1/app/app.hpp>
#include <c1/app/jwt.hpp>

namespace c1
{
AuthenticationController::AuthenticationController(const std::string& prefix, Storage& storage,
                                                   UserRepository& user_repository,
                                                   RoleRepository& role_repository,
                                                   RefreshTokenRepository& refresh_token_repository):
    Controller(prefix),
    storage_(storage),
    user_repository_(user_repository), role_repository_(role_repository),
    refresh_token_repository_(refresh_token_repository)
{
}

void AuthenticationController::setRoutes()
{
    CROW_BP_ROUTE(self, "sign-up").methods(crow::HTTPMethod::Post)([this](const crow::request& req, crow::response& res)
    {
        const auto userDtoin = crow::json::load(req.body);
        if (!userDtoin)
        {
            res.code = 400;
            res.end();
            return;
        }
        const auto newUser = storage_.createObject<User>(userDtoin);
        user_repository_.appendRole(newUser->email, "USER");
        res.code = 200;
        res.end();
    });

    CROW_BP_ROUTE(self, "sign-in").methods(crow::HTTPMethod::Post)([this](const crow::request& req, crow::response& res)
    {
        const std::string cookieHeader = req.get_header_value("Cookie");
        if (auto cookieMap = parseCookieHeader(cookieHeader); cookieMap.find("jwt") != cookieMap.end())
        {
            refresh_token_repository_.deleteByToken(cookieMap["jwt"]);
        }
        const auto userDtoin = crow::json::load(req.body);
        if (!userDtoin)
        {
            res.code = 400;
            res.end();
            return;
        }
        const auto email = userDtoin["email"].s();
        const auto password = userDtoin["password"].s();
        try
        {
            User user = user_repository_.findByEmail(email);
            if (!user.isPasswordValid(password))
            {
                res.code = 401;
                res.end();
                return;
            }
            const auto rt = jwt::generateToken(REFRESH_TOKEN_DURATION_SECONDS, {
                                                   {"email", user.email}
                                               });

            const std::string rtjson = R"({"token": ")" + rt + R"(", "user_id": )" + std::to_string(user.id) + "}";
            storage_.createObject<RefreshToken>(crow::json::load(rtjson));
            const auto ac = jwt::generateToken(ACCESS_TOKEN_DURATION_SECONDS, {
                                                   {"email", user.email},
                                                   {"roles", crow::json::wvalue::list(rolesToJsonList(user.roles))}
                                               });
            res.add_header("Set-Cookie", "jwt=" + rt + "; HttpOnly; Secure; SameSite=None");
            res.write(ac);
            res.end();
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what();
            res.code = 401;
            res.end();
        }
    });

    CROW_BP_ROUTE(self, "refresh")([this](const crow::request& req, crow::response& res)
    {
        const std::string cookieHeader = req.get_header_value("Cookie");
        auto cookieMap = parseCookieHeader(cookieHeader);
        if (cookieMap.find("jwt") == cookieMap.end())
        {
            res.code = 401;
            res.end();
            return;
        }
        const std::string rt = cookieMap["jwt"];
        try
        {
            const User user = user_repository_.findByRefreshToken(rt);
            const auto decodedEmail = jwt::extractEmail(rt);
            refresh_token_repository_.deleteByToken(rt);
            if (user.email != decodedEmail)
            {
                std::cerr << "refreshToken compromised";
                const User compromisedUser = user_repository_.findByEmail(decodedEmail);
                refresh_token_repository_.deleteAllByEmail(compromisedUser.email);
                res.code = 401;
                res.end();
                return;
            }
            const auto newRt = jwt::generateToken(REFRESH_TOKEN_DURATION_SECONDS, {
                                                      {"email", user.email}
                                                  });
            const auto newAt = jwt::generateToken(REFRESH_TOKEN_DURATION_SECONDS, {
                                                      {"email", user.email},
                                                      {"roles", crow::json::wvalue::list(rolesToJsonList(user.roles))}
                                                  });
            res.add_header("Set-Cookie", "jwt=" + newRt + "; HttpOnly; Secure; SameSite=None");
            res.write(newAt);
            res.end();
        }
        catch (const std::exception& e)
        {
            res.code = 401;
            res.end();
        }
    });

    CROW_BP_ROUTE(self, "logout")([this](const crow::request& req, crow::response& res)
    {
        const std::string cookieHeader = req.get_header_value("Cookie");
        if (auto cookieMap = parseCookieHeader(cookieHeader); cookieMap.find("jwt") != cookieMap.end())
        {
            refresh_token_repository_.deleteByToken(cookieMap["jwt"]);
        }
        res.add_header("Set-Cookie", "");
        res.end();
    });
}

crow::json::wvalue::list AuthenticationController::rolesToJsonList(const std::vector<Role>& roles)
{
    crow::json::wvalue::list jsonList;
    for (const auto& role : roles)
    {
        jsonList.push_back(role.toJson());
    }
    return jsonList;
}

std::unordered_map<std::string, std::string> AuthenticationController::parseCookieHeader(const std::string& header)
{
    std::unordered_map<std::string, std::string> cookies;
    std::istringstream cookieStream(header);
    std::string cookie;
    while (std::getline(cookieStream, cookie, ';'))
    {
        const auto delimiterPos = cookie.find('=');
        if (delimiterPos == std::string::npos)
        {
            continue;
        }
        std::string name = cookie.substr(0, delimiterPos);
        std::string value = cookie.substr(delimiterPos + 1);
        const auto nameStart = name.find_first_not_of(" \t");
        if (const auto nameEnd = name.find_last_not_of(" \t"); nameStart != std::string::npos && nameEnd !=
            std::string::npos)
        {
            name = name.substr(nameStart, nameEnd - nameStart + 1);
        }
        const auto valueStart = value.find_first_not_of(" \t");
        if (const auto valueEnd = value.find_last_not_of(" \t"); valueStart != std::string::npos && valueEnd !=
            std::string::npos)
        {
            value = value.substr(valueStart, valueEnd - valueStart + 1);
        }
        cookies[name] = value;
    }

    return cookies;
}
} // c1
