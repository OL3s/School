package edu.ntnu.id.idatt.oving4;

public class CalculationRequest {
    private double inputA;
    private double inputB;
    private String operator;

    // Getters and setters
    public double getInputA() {
        return inputA;
    }
    public void setInputA(double inputA) {
        this.inputA = inputA;
    }
    public double getInputB() {
        return inputB;
    }
    public void setInputB(double inputB) {
        this.inputB = inputB;
    }
    public String getOperator() {
        return operator;
    }
    public void setOperator(String operator) {
        this.operator = operator;
    }
}
