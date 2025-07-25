import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;
import com.oving5.backend.Card;
import com.oving5.backend.Deck;

import java.util.ArrayList;

public class TestDeck {

    @Test
    public void testDeckInitialization() {
        Deck deck = new Deck(true); // Fill the deck with all 52 cards
        assertEquals(52, deck.getCards().size(), "Deck should contain 52 cards after initialization");
    }

    @Test
    public void testEmptyDeckInitialization() {
        Deck deck = new Deck(false); // Create an empty deck
        assertEquals(0, deck.getCards().size(), "Deck should be empty when initialized with 'false'");
    }

    @Test
    public void testFillDeck() {
        Deck deck = new Deck(false); // Start with an empty deck
        assertEquals(0, deck.getCards().size(), "Deck should initially be empty");
        deck = new Deck(true); // Fill the deck
        assertEquals(52, deck.getCards().size(), "Deck should contain 52 cards after filling");
    }

    @Test
    public void testDrawTop() {
        Deck deck = new Deck(true);
        Card topCard = deck.getCards().get(0); // Get the top card
        Card drawnCard = deck.drawTop(); // Draw the top card
        assertEquals(topCard, drawnCard, "The drawn card should match the top card");
        assertEquals(51, deck.getCards().size(), "Deck size should decrease by 1 after drawing a card");
    }

    @Test
    public void testDrawAt() {
        Deck deck = new Deck(true);
        Card cardAtIndex = deck.getCards().get(10); // Get the card at index 10
        Card drawnCard = deck.drawAt(10); // Draw the card at index 10
        assertEquals(cardAtIndex, drawnCard, "The drawn card should match the card at the specified index");
        assertEquals(51, deck.getCards().size(), "Deck size should decrease by 1 after drawing a card");
    }

    @Test
    public void testAddCard() {
        Deck deck = new Deck(false); // Start with an empty deck
        Card card = new Card('H', 10); // Create a new card
        deck.addCard(card); // Add the card to the deck
        assertEquals(1, deck.getCards().size(), "Deck size should increase by 1 after adding a card");
        assertEquals(card, deck.getCards().get(0), "The added card should be present in the deck");
    }

    @Test
    public void testSortByValue() {
        Deck deck = new Deck(true);
        deck.sortShuffle(); // Shuffle the deck
        deck.sortValue(); // Sort the deck by value
        ArrayList<Card> cards = deck.getCards();
        for (int i = 1; i < cards.size(); i++) {
            assertTrue(cards.get(i).getValue() >= cards.get(i - 1).getValue(),
                "Cards should be sorted by value in ascending order");
        }
    }

    @Test
    public void testSortBySuit() {
        Deck deck = new Deck(true);
        deck.sortShuffle(); // Shuffle the deck
        deck.sortSuit(); // Sort the deck by suit
        ArrayList<Card> cards = deck.getCards();
        for (int i = 1; i < cards.size(); i++) {
            assertTrue(cards.get(i).getSuit() >= cards.get(i - 1).getSuit(),
                "Cards should be sorted by suit in ascending order");
        }
    }

    @Test
    public void testShuffle() {
        Deck deck = new Deck(true);
        ArrayList<Card> originalOrder = new ArrayList<>(deck.getCards()); // Save the original order
        deck.sortShuffle(); // Shuffle the deck
        assertNotEquals(originalOrder, deck.getCards(), "Deck order should change after shuffling");
    }

    @Test
    public void testToString() {
        Deck deck = new Deck(true);
        String deckString = deck.toString();
        assertTrue(deckString.contains("H1"), "Deck string should contain card representations");
        assertTrue(deckString.contains("S13"), "Deck string should contain card representations");
    }
}