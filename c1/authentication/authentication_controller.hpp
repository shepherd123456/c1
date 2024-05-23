//
// Created by shepherd on 2.5.24.
//

#ifndef AUTHENTICATION_CONTROLLER_HPP
#define AUTHENTICATION_CONTROLLER_HPP

#include <unordered_map>

#include <c1/app/controller.hpp>
#include <c1/app/storage.hpp>
#include <c1/user/user_repository.hpp>
#include <c1/role/role_repository.hpp>
#include <c1/refreshtoken/refresh_token_repository.hpp>

namespace c1
{
class AuthenticationController : public Controller
{
public:
    explicit AuthenticationController(
        const std::string& prefix,
        Storage& storage,
        UserRepository& user_repository,
        RoleRepository& role_repository,
        RefreshTokenRepository& refresh_token_repository
    );

    void setRoutes() override;

private:
    static crow::json::wvalue::list rolesToJsonList(const std::vector<Role>& roles);
    static std::unordered_map<std::string, std::string> parseCookieHeader(const std::string& header);

    Storage& storage_;
    UserRepository& user_repository_;
    RoleRepository& role_repository_;
    RefreshTokenRepository& refresh_token_repository_;
};
} // c1

#endif //AUTHENTICATION_CONTROLLER_HPP
