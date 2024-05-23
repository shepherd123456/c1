//
// Created by shepherd on 20.5.24.
//

#include <c1/authentication/auth_filter.hpp>
#include <c1/app/jwt.hpp>

namespace c1::jwt
{
void AuthFilter::before_handle(crow::request& req, crow::response& res, context& ctx)
{
    try
    {
        if (const std::string authHeader = req.get_header_value("Authorization"); !authHeader.empty() && authHeader.
            find("Bearer ") == 0)
        {
            if (const std::string token = authHeader.substr(7); !token.empty())
            {
                ctx.email = extractEmail(token);
                ctx.roles = extractRoles(token);
                ctx.isAuthenticated = true;
            }
        }
    }
    catch (const std::exception& e)
    {
        res.code = 401;
        res.body = crow::json::wvalue{{"message", e.what()}}.dump();
        res.end();
    }
}

void AuthFilter::after_handle(crow::request& req, crow::response& res, context& ctx)
{
}
} // c1::jwt
