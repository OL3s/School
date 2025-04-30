package com.example;
import java.util.ArrayList;

public class Script {
  ArrayList<TextCommand> commands = new ArrayList<>();
  
  public Script() {
    commands.add(new WrapTextCommand("(", ")"));
    commands.add(new ReplaceTextCommand("a", "b"));
    commands.add(new CapitalizeTextCommand());
  }

  public String execute(String text) {
    for (TextCommand command : commands) {
      text = command.execute(text);
    }
    return text;
  }
}
