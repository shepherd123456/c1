//
// Created by shepherd on 21.5.24.
//

#ifndef USER_REPOSITORY_HPP
#define USER_REPOSITORY_HPP

#include <string>
#include <vector>
#include <c1/app/storage.hpp>
#include <c1/user/user.hpp>

namespace c1 {

class UserRepository {
public:
    explicit UserRepository(storage_t& storage);

    std::vector<User> getAll() const;
    User findByEmail(const std::string& email);
    User findByRefreshToken(const std::string& refreshToken);
    void appendRole(const std::string& email, const std::string& roleName);

private:
    storage_t& storage_;
    std::vector<Role> getRolesForUser(int userId);
};

} // c1

#endif //USER_REPOSITORY_HPP
