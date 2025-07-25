package com.oving5.backend;
import java.util.ArrayList;
import java.util.Collections;

public class Deck {
    protected ArrayList<Card> cards;

    /*
     * Constructor for Deck
     * @param fill: boolean, if true, fills the deck with all 52 cards
     */
    public Deck(boolean fill) {
        cards = new ArrayList<>();
        if (fill) fillDeck();
    }

    public ArrayList<Card> getCards() {
        return cards;
    }

    private void fillDeck() {
        cards.clear();
        for (char suit : Card.getSuits()) {
            for (int value = 1; value <= 13; value++) {
                cards.add(new Card(suit, value));
            }
        }
    }

    public Card drawAt(int Index) {
        return cards.remove(Index);
    }

    public Card drawTop() {
        return cards.remove(0);
    }

    public void addCard(Card card) {
        cards.add(card);
    }

    public void sortValue() {
        cards.sort((c1, c2) -> c1.getValue() - c2.getValue());
    }

    public void sortSuit() {
        cards.sort((c1, c2) -> c1.getSuit() - c2.getSuit());
    }

    public void sortShuffle() {
        Collections.shuffle(cards);
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (Card card : cards) {
            sb.append(card).append(", ");
        }
        return sb.toString();
    }


}
