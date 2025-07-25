package com.example;

public class WrapSelectionTextCommand extends WrapTextCommand {
    
  public String open, close, selection;
  public WrapSelectionTextCommand(String open, String close, String selection) {
      super(open, close);
  }

  @Override public String execute(String text) {
    String[] parts = text.split(selection);
    StringBuilder result = new StringBuilder();
    for (int i = 0; i < parts.length; i++) {
      result.append(parts[i]);
      if (i < parts.length - 1) {
        result.append(open).append(selection).append(close);
      }
    }
    return result.toString();
  }

}
