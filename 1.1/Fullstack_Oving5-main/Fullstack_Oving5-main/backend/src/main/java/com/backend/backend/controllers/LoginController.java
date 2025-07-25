package com.backend.backend.controllers;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import com.backend.backend.dtos.LoginRequest;
import com.backend.backend.dtos.LoginResponse;
import com.backend.backend.services.LoginService;

@RestController
@RequestMapping("/api/auth")
@CrossOrigin(origins = "http://localhost:5173")
public class LoginController {

    @Autowired
    private LoginService loginService;

    @PostMapping("/login")
    public ResponseEntity<LoginResponse> login(@RequestBody LoginRequest loginRequest) {
        String token = loginService.authenticate(
            loginRequest.getUsername(), 
            loginRequest.getPassword()
        );
        
        if (token != null) {
            return ResponseEntity.ok(new LoginResponse(token));
        } else {
            return ResponseEntity.ok(new LoginResponse("Invalid username or password", false));
        }
    }
}