package edu.ntnu.id.idatt.oving4;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

@RestController
public class CalculatorController {

  private static final Logger LOGGER = LoggerFactory.getLogger(CalculatorController.class);

  @Autowired
  private CalculatorService calculatorService;

  @PostMapping("/add")
  public double add(@RequestBody CalculationRequest request) {
    LOGGER.info("Adding {} and {}", request.getInputA(), request.getInputB());
    return calculatorService.add(request.getInputA(), request.getInputB());
  }

  @PostMapping("/subtract")
  public double subtract(@RequestBody CalculationRequest request) {
    LOGGER.info("Subtracting {} from {}", request.getInputB(), request.getInputA());
    return calculatorService.subtract(request.getInputA(), request.getInputB());
  }

  @PostMapping("/multiply")
  public double multiply(@RequestBody CalculationRequest request) {
    LOGGER.info("Multiplying {} and {}", request.getInputA(), request.getInputB());
    return calculatorService.multiply(request.getInputA(), request.getInputB());
  }

  @PostMapping("/divide")
  public double divide(@RequestBody CalculationRequest request) {
    LOGGER.info("Dividing {} by {}", request.getInputA(), request.getInputB());
    return calculatorService.divide(request.getInputA(), request.getInputB());
  }
}
