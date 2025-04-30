package com.example;

public class WrapLinesTextCommand extends WrapTextCommand {

  String open, end;

  public WrapLinesTextCommand(String open, String end) {
    super(open, end);
  }

  @Override public String execute(String text) {
    String[] lines = text.split("\n");
    String result = "";

    for (int i = 0; i < lines.length; i++) {
      result += open + lines[i] + end;
      if (i < lines.length - 1) {
        result += "\n";
      }
    }

    return result;
  }

}
