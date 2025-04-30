package com.oving5.backend;

import java.util.ArrayList;

public class Hand extends Deck {

    public Hand() {
        super(false);
    }

    public int getHandSize() {
        return getCards().size();
    }

    public void setHandFill(ArrayList<Card> cards) {
        getCards().addAll(cards);
    }

    public boolean isFlush(int threshold) {
    
        // Check if the hand has a flush
        for(char suit : Card.getSuits()) {
            int count = 0;
            for(Card card : getCards()) {
                if(card.getSuit() == suit) {
                    count++;
                }
            }
            if (count >= threshold) {
                return true;
            }
        }

        return false;
    }

    public boolean isStraight(int threshold) {
        // Handle edge cases
        if (cards.size() < threshold) {
            return false;
        }
    
        // Sort the cards by value
        sortValue();
    
        int count = 0;
        int currentValue = cards.get(0).getValue();
    
        for (int i = 1; i < cards.size(); i++) {
            int gap = cards.get(i).getValue() - currentValue;
    
            if (gap == 1) { // Increment count for consecutive cards
                count++;
                if (count >= threshold - 1) return true; // Adjust for threshold
            } else if (gap > 1) { // Reset count if gap is too large
                count = 0;
            }
    
            currentValue = cards.get(i).getValue();
        }
    
        return false;
    }



    public int getCountSpesificValue(int value) {
        return (int) getCards().stream()
                .filter(card -> card.getValue() == value)
                .count();
    }

    public int getCountSpesificSuit(char suit) {
        return (int) getCards().stream()
                .filter(card -> card.getSuit() == suit)
                .count();
    }

    public ArrayList<Card> getSpesificSuit(char suit) {
        ArrayList<Card> cards = new ArrayList<>();
        getCards().stream()
                .filter(card -> card.getSuit() == suit)
                .forEach(c -> cards.add(c));
        return cards;
    }

    public void printSpesificSuit(char suit) {
        StringBuilder printString = new StringBuilder();
        getCards().stream()
                .filter(card -> card.getSuit() == suit)
                .forEach(c -> printString.append(c.toString()).append(", "));
    }

    public boolean isSpadeQueen() {
        return getCards().stream()
                .anyMatch(card -> card.getSuit() == 'S' && card.getValue() == 12);
    }



}
