package com.backend.backend.dtos;

public class LoginRequest {
    private String username;
    private String password;
    
    // Default constructor needed for Jackson deserialization
    public LoginRequest() {
    }
    
    // Constructor with parameters
    public LoginRequest(String username, String password) {
        this.username = username;
        this.password = password;
    }
    
    // Getters and setters
    public String getUsername() {
        return username;
    }
    
    public void setUsername(String username) {
        this.username = username;
    }
    
    public String getPassword() {
        return password;
    }
    
    public void setPassword(String password) {
        this.password = password;
    }
}