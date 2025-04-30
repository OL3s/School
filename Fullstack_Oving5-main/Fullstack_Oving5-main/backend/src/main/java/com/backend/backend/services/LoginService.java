package com.backend.backend.services;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import com.backend.backend.models.User;
import com.backend.backend.repos.UserRepository;

@Service
public class LoginService {
    
    @Autowired
    private UserRepository userRepository;
    
    @Autowired
    private TokenService tokenService;

    /**
     * Authenticate a user with username and password
     * @param username The username
     * @param password The password
     * @return A token if authentication is successful, null otherwise
     */
    public String authenticate(String username, String password) {
        // Check if credentials are valid using the database
        User user = userRepository.findByUsername(username);
        
        if (user != null && user.getPassword().equals(password)) {
            // Generate JWT token
            return tokenService.generateToken(username);
        }
        
        return null;
    }

    /**
     * Validate if a token is valid
     * @param token The token to validate
     * @return true if the token is valid, false otherwise
     */
    public boolean validateToken(String token) {
        return tokenService.isTokenValid(token);
    }

    /**
     * Get the username associated with a token
     * @param token The token
     * @return The username, or null if the token is invalid
     */
    public String getUsernameFromToken(String token) {
        return tokenService.getUsernameFromToken(token);
    }
}