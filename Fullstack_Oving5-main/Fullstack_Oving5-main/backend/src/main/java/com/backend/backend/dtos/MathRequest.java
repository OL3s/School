package com.backend.backend.dtos;

public class MathRequest {
    private double num1;
    private double num2;

    // Default constructor needed for Jackson deserialization
    public MathRequest() {
    }

    public MathRequest(double num1, double num2) {
        this.num1 = num1;
        this.num2 = num2;
    }

    public double getNum1() {
        return num1;
    }

    public void setNum1(double num1) {
        this.num1 = num1;
    }

    public double getNum2() {
        return num2;
    }

    public void setNum2(double num2) {
        this.num2 = num2;
    }
}