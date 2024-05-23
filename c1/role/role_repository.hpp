//
// Created by shepherd on 21.5.24.
//

#ifndef ROLE_REPOSITORY_HPP
#define ROLE_REPOSITORY_HPP

#include <string>
#include <c1/app/storage.hpp>
#include "sqlite_orm/sqlite_orm.h"

namespace c1 {

class RoleRepository {
public:
    explicit RoleRepository(storage_t& storage) ;
    Role findByName(const std::string& name);

private:
    storage_t& storage_;
};

} // c1

#endif //ROLE_REPOSITORY_HPP
