//
// Created by shepherd on 2.5.24.
//

#ifndef USER_CONTROLLER_HPP
#define USER_CONTROLLER_HPP

#include <c1/app/controller.hpp>

namespace c1 {

class UserController: public Controller {
public:
    explicit UserController(const std::string& prefix)
        : Controller(prefix)
    {
    }

    void setRoutes() override;
};

} // c1

#endif //USER_CONTROLLER_HPP
