package com.backend.backend.repos;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

import com.backend.backend.models.User;

@Repository
public interface UserRepository extends JpaRepository<User, Long> {
    
    /**
     * Find a user by their username
     * @param username the username to search for
     * @return the User if found, null otherwise
     */
    User findByUsername(String username);
}