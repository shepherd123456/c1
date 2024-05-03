//
// Created by shepherd on 2.5.24.
//

#ifndef AUTHENTICATION_CONTROLLER_HPP
#define AUTHENTICATION_CONTROLLER_HPP

#include <c1/app/controller.hpp>

namespace c1 {

class AuthenticationController : public Controller {
public:
    explicit AuthenticationController(const std::string& prefix)
        : Controller(prefix)
    {
    }

    void setRoutes() override;
};

} // c1

#endif //AUTHENTICATION_CONTROLLER_HPP
