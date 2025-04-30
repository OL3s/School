package edu.ntnu.id.idatt.oving4;

import org.springframework.stereotype.Service;

@Service
public class CalculatorService {
    public double add(double a, double b) {
        try {
            return a + b;
        } catch (Exception e) {
            System.err.println("Exception in add: " + e.getMessage());
            return 0.0;
        }
    }

    public double subtract(double a, double b) {
        try {
            return a - b;
        } catch (Exception e) {
            System.err.println("Exception in subtract: " + e.getMessage());
            return 0.0;
        }
    }

    public double multiply(double a, double b) {
        try {
            return a * b;
        } catch (Exception e) {
            System.err.println("Exception in multiply: " + e.getMessage());
            return 0.0;
        }
    }

    public double divide(double a, double b) {
        try {
            return a / b;
        } catch (Exception e) {
            System.err.println("Exception in divide: " + e.getMessage());
            return 0.0;
        }
    }
}