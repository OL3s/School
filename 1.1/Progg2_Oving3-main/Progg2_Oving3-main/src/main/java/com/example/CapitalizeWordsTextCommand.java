package com.example;

public class CapitalizeWordsTextCommand extends CapitalizeTextCommand {

  public CapitalizeWordsTextCommand() {
    super();
  }

  @Override
  public String execute(String text) {
    String[] words = text.split(" ");
    StringBuilder sb = new StringBuilder();
    for (String word : words) {
      sb.append(word.substring(0, 1).toUpperCase() + word.substring(1) + " ");
    }
    return sb.toString().trim();
  }

}
