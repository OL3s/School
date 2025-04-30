package com.example;

public class CapitalizeTextCommand implements TextCommand {

    @Override
    public String execute(String text) {
        String[] words = text.split(" ");
        for (int i = 0; i < words.length; i++) {
            if (words[i].length() > 0) {
          words[i] = words[i].substring(0, 1).toUpperCase() + words[i].substring(1).toLowerCase();
            }
        }
        return String.join(" ", words);
    }

}
