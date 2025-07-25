package com.example;

public class WrapTextCommand implements TextCommand{
    
    private String open, end;

    WrapTextCommand(String open, String end) {
        this.open = open;
        this.end = end;
    }

    @Override
    public String execute(String text) {
        return open + text + end;
    }

}
