package com.backend.backend.dtos;

public class MathResponse {
    private boolean success;
    private double result;
    private String message;

    public MathResponse(boolean success, double result, String message) {
        this.success = success;
        this.result = result;
        this.message = message;
    }

    public boolean isSuccess() {
        return success;
    }

    public double getResult() {
        return result;
    }

    public String getMessage() {
        return message;
    }
}