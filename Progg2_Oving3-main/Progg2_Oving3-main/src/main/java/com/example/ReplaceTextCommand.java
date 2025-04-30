package com.example;

public class ReplaceTextCommand implements TextCommand {

    private String from;
    private String to;

    public ReplaceTextCommand(String from, String to) {
        this.from = from;
        this.to = to;
    }

    @Override
    public String execute(String text) {
        return text.replace(from, to);
    }

}
