package com.backend.backend.dtos;

public class LoginResponse {
    private boolean success;
    private String token;
    private String message;
    
    // Default constructor for Jackson
    public LoginResponse() {
    }
    
    // Constructor for successful login
    public LoginResponse(String token) {
        this.success = true;
        this.token = token;
        this.message = null;
    }
    
    // Constructor for failed login
    public LoginResponse(String message, boolean success) {
        this.success = false;
        this.token = null;
        this.message = message;
    }
    
    // Getters and setters
    public boolean isSuccess() {
        return success;
    }
    
    public void setSuccess(boolean success) {
        this.success = success;
    }
    
    public String getToken() {
        return token;
    }
    
    public void setToken(String token) {
        this.token = token;
    }
    
    public String getMessage() {
        return message;
    }
    
    public void setMessage(String message) {
        this.message = message;
    }
}