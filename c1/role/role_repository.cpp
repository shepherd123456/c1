//
// Created by shepherd on 21.5.24.
//

#include "role_repository.hpp"

namespace c1 {
RoleRepository::RoleRepository(decltype(init_storage())& storage): storage_(storage) {}

Role RoleRepository::findByName(const std::string& name)
{
    if (auto roles = storage_.get_all<Role>(sqlite_orm::where(sqlite_orm::c(&Role::name) == name)); !roles.empty()) {
        return roles.front();
    }
    throw std::runtime_error("Role not found");
}
} // c1