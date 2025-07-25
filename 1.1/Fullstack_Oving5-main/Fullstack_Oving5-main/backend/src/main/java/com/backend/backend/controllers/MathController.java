package com.backend.backend.controllers;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.security.access.prepost.PreAuthorize;
import org.springframework.web.bind.annotation.*;

import com.backend.backend.dtos.MathRequest;
import com.backend.backend.dtos.MathResponse;
import com.backend.backend.services.MathService;

@CrossOrigin(origins = "http://localhost:5173")
@RestController("MathController")
@RequestMapping("/api")
public class MathController {

    @Autowired
    private MathService mathService;

    // Support both GET and POST for add
    @GetMapping("/add")
    @PreAuthorize("isAuthenticated() or #token == 'guest'")
    public ResponseEntity<?> addGet(@RequestParam double num1, 
                                 @RequestParam double num2,
                                 @RequestHeader(value = "Authorization", required = false) String token) {
        double result = mathService.add(num1, num2);
        return ResponseEntity.ok(new MathResponse(true, result, null));
    }

    @PostMapping("/add")
    @PreAuthorize("isAuthenticated() or #token == 'guest'")
    public ResponseEntity<?> addPost(@RequestBody MathRequest request,
                                  @RequestHeader(value = "Authorization", required = false) String token) {
        double result = mathService.add(request.getNum1(), request.getNum2());
        return ResponseEntity.ok(new MathResponse(true, result, null));
    }

    // Support both GET and POST for subtract
    @GetMapping("/subtract")
    @PreAuthorize("isAuthenticated() or #token == 'guest'")
    public ResponseEntity<?> subtractGet(@RequestParam double num1, 
                                      @RequestParam double num2,
                                      @RequestHeader(value = "Authorization", required = false) String token) {
        double result = mathService.subtract(num1, num2);
        return ResponseEntity.ok(new MathResponse(true, result, null));
    }

    @PostMapping("/subtract")
    @PreAuthorize("isAuthenticated() or #token == 'guest'")
    public ResponseEntity<?> subtractPost(@RequestBody MathRequest request,
                                       @RequestHeader(value = "Authorization", required = false) String token) {
        double result = mathService.subtract(request.getNum1(), request.getNum2());
        return ResponseEntity.ok(new MathResponse(true, result, null));
    }

    // Support both GET and POST for multiply
    @GetMapping("/multiply")
    @PreAuthorize("isAuthenticated() or #token == 'guest'")
    public ResponseEntity<?> multiplyGet(@RequestParam double num1, 
                                      @RequestParam double num2,
                                      @RequestHeader(value = "Authorization", required = false) String token) {
        double result = mathService.multiply(num1, num2);
        return ResponseEntity.ok(new MathResponse(true, result, null));
    }

    @PostMapping("/multiply")
    @PreAuthorize("isAuthenticated() or #token == 'guest'")
    public ResponseEntity<?> multiplyPost(@RequestBody MathRequest request,
                                       @RequestHeader(value = "Authorization", required = false) String token) {
        double result = mathService.multiply(request.getNum1(), request.getNum2());
        return ResponseEntity.ok(new MathResponse(true, result, null));
    }

    // Support both GET and POST for divide
    @GetMapping("/divide")
    @PreAuthorize("isAuthenticated() or #token == 'guest'")
    public ResponseEntity<?> divideGet(@RequestParam double num1, 
                                    @RequestParam double num2,
                                    @RequestHeader(value = "Authorization", required = false) String token) {
        try {
            double result = mathService.divide(num1, num2);
            return ResponseEntity.ok(new MathResponse(true, result, null));
        } catch (IllegalArgumentException e) {
            return ResponseEntity.badRequest().body(new MathResponse(false, 0, e.getMessage()));
        }
    }

    @PostMapping("/divide")
    @PreAuthorize("isAuthenticated() or #token == 'guest'")
    public ResponseEntity<?> dividePost(@RequestBody MathRequest request,
                                     @RequestHeader(value = "Authorization", required = false) String token) {
        try {
            double result = mathService.divide(request.getNum1(), request.getNum2());
            return ResponseEntity.ok(new MathResponse(true, result, null));
        } catch (IllegalArgumentException e) {
            return ResponseEntity.badRequest().body(new MathResponse(false, 0, e.getMessage()));
        }
    }
}