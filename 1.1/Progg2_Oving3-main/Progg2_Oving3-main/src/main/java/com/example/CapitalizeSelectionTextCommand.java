package com.example;

public class CapitalizeSelectionTextCommand extends CapitalizeTextCommand {

  String replacement;

  public CapitalizeSelectionTextCommand(String replacement) {
    super();
    this.replacement = replacement;
  }

  @Override 
  public String execute(String text) {
    return text.replace(replacement, replacement.substring(0, 1).toUpperCase() + replacement.substring(1));
  }

}
