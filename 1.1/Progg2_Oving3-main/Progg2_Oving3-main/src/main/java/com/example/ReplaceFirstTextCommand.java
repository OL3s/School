package com.example;

public class ReplaceFirstTextCommand extends ReplaceTextCommand {

  String from, to;

  public ReplaceFirstTextCommand(String from, String to) {
    super(from, to);
  }

  @Override
  public String execute(String text) {
    String[] words = text.split(" ", 2);
    if (words.length > 0 && words[0].equals(from)) { // If the first word is the same as the word to replace
      return to + (words.length > 1 ? " " + words[1] : ""); // Replace the first word with the new word
    }
    return text; // Otherwise, return the original text
  }

}
