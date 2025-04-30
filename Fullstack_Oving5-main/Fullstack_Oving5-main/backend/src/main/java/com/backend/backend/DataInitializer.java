package com.backend.backend;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.stereotype.Component;

import com.backend.backend.models.User;
import com.backend.backend.repos.UserRepository;

@Component
public class DataInitializer implements CommandLineRunner {

    @Autowired
    private UserRepository userRepository;
    
    @Override
    public void run(String... args) throws Exception {
        // Check if we have any users
        if (userRepository.count() == 0) {
            // Create default users
            System.out.println("Creating default users...");
            userRepository.save(new User("admin", "admin"));
            userRepository.save(new User("user", "password"));
            System.out.println("Default users created.");
        }
    }
}