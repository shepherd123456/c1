//
// Created by shepherd on 2.5.24.
//

#ifndef USER_CONTROLLER_HPP
#define USER_CONTROLLER_HPP

#include <c1/app/controller.hpp>
#include <c1/app/storage.hpp>
#include <c1/user/user_repository.hpp>

namespace c1
{
class UserController final : public Controller
{
public:
    UserController(const std::string& prefix, Storage& storage, UserRepository& userRepo);

    void setRoutes() override;

private:
    Storage& storage_;
    UserRepository& user_repository_;
};
} // c1

#endif //USER_CONTROLLER_HPP
