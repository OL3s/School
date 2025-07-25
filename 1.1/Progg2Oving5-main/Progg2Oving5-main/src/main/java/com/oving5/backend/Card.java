package com.oving5.backend;
import java.awt.Color;

public class Card {
    private final char suit;
    private final int value;
    private final Color color;

    public Card(char suit, int value) {
        this.suit = suit;
        this.value = value;
        this.color = getColorInit();
    }

    public char getSuit() {
        return suit;
    }

    /*
     * Returns a string array with the suit image and value of the card
     * @param suit: char, the suit of the card
     * @param value: int, the value of the card
     * @return String[], the suit image and value of the card
     */
    public static String[] getCardStringDraw(char suit, int value) {
        return new String[]{suitToString(suit), String.valueOf(value)};
    }

    /*
     * Method to convert the suit to a string as an image
     * @param suit: char, the suit of the card
     * @return String, the suit as an image in string format
     */
    public static String suitToString(char suit) {
        switch (suit) {
            case 'H':
                return "♥";
            case 'D':
                return "♦";
            case 'S':
                return "♠";
            case 'C':
                return "♣";
            default:
                return "ERROR";
        }
    }

    /*
     * Method to convert the value to a string
     * @param value: int, the value of the card
     */
    public static String valueToString(int value) {
        switch (value) {
            case 1:
                return "A";
            case 11:
                return "J";
            case 12:
                return "Q";
            case 13:
                return "K";
            default:
                return String.valueOf(value);
        }
    }

    public static char[] getSuits() {
        return new char[]{'H', 'D', 'S', 'C'};
    }


    public int getValue() {
        return value;
    }

    private Color getColorInit() {
        if (suit == 'H' || suit == 'D') {
            return Color.RED;
        } else {
            return Color.BLACK;
        }
    }

    public Color getColor() {
        return color;
    }

    @Override
    public String toString() {
        return String.valueOf(suit) + value;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == this) {
            return true;
        }
        if (!(obj instanceof Card)) {
            return false;
        }
        Card card = (Card) obj;
        return card.getSuit() == suit && card.getValue() == value;
    }
}
