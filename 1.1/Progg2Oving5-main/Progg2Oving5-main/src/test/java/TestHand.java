import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;
import com.oving5.backend.Card;
import com.oving5.backend.Hand;

import java.util.ArrayList;

public class TestHand {

    @Test
    public void testHandInitialization() {
        Hand hand = new Hand();
        assertEquals(0, hand.getHandSize(), "Hand should be empty after initialization");
    }

    @Test
    public void testSetHandFill() {
        Hand hand = new Hand();
        ArrayList<Card> cards = new ArrayList<>();
        cards.add(new Card('H', 10));
        cards.add(new Card('S', 5));
        hand.setHandFill(cards);
        assertEquals(2, hand.getHandSize(), "Hand size should be 2 after adding cards");
        assertEquals(cards, hand.getCards(), "Hand should contain the added cards");
    }

    @Test
    public void testIsFlush() {
        Hand hand = new Hand();
        hand.addCard(new Card('H', 2));
        hand.addCard(new Card('H', 5));
        hand.addCard(new Card('H', 10));
        assertTrue(hand.isFlush(3), "Hand should be a flush with 3 cards of the same suit");
        assertFalse(hand.isFlush(4), "Hand should not be a flush with 4 cards of the same suit");
    }

    @Test
    public void testIsStraight() {
        Hand hand = new Hand();
        hand.addCard(new Card('H', 2));
        hand.addCard(new Card('S', 3));
        hand.addCard(new Card('D', 4));
        assertTrue(hand.isStraight(3), "Hand should be a straight with 3 consecutive cards");
        hand.addCard(new Card('C', 6));
        assertFalse(hand.isStraight(4), "Hand should not be a straight with 4 consecutive cards");
    }

    @Test
    public void testGetCountSpecificValue() {
        Hand hand = new Hand();
        hand.addCard(new Card('H', 10));
        hand.addCard(new Card('S', 10));
        hand.addCard(new Card('D', 5));
        assertEquals(2, hand.getCountSpesificValue(10), "Hand should contain 2 cards with value 10");
        assertEquals(1, hand.getCountSpesificValue(5), "Hand should contain 1 card with value 5");
        assertEquals(0, hand.getCountSpesificValue(7), "Hand should contain 0 cards with value 7");
    }

    @Test
    public void testGetCountSpecificSuit() {
        Hand hand = new Hand();
        hand.addCard(new Card('H', 10));
        hand.addCard(new Card('H', 5));
        hand.addCard(new Card('S', 7));
        assertEquals(2, hand.getCountSpesificSuit('H'), "Hand should contain 2 cards of suit 'H'");
        assertEquals(1, hand.getCountSpesificSuit('S'), "Hand should contain 1 card of suit 'S'");
        assertEquals(0, hand.getCountSpesificSuit('D'), "Hand should contain 0 cards of suit 'D'");
    }

    @Test
    public void testGetSpecificSuit() {
        Hand hand = new Hand();
        hand.addCard(new Card('H', 10));
        hand.addCard(new Card('H', 5));
        hand.addCard(new Card('S', 7));
        ArrayList<Card> hearts = hand.getSpesificSuit('H');
        assertEquals(2, hearts.size(), "Should return 2 cards of suit 'H'");
        assertTrue(hearts.get(0).getSuit() == (new Card('H', 10).getSuit()), "Should contain card 'H10'");
        assertTrue(hearts.get(1).getSuit() == (new Card('H', 5).getSuit()), "Should contain card 'H5'");
    }

    @Test
    public void testIsSpadeQueen() {
        Hand hand = new Hand();
        hand.addCard(new Card('S', 12)); // Queen of Spades
        assertTrue(hand.isSpadeQueen(), "Hand should contain the Queen of Spades");
        hand.getCards().clear();
        assertFalse(hand.isSpadeQueen(), "Hand should not contain the Queen of Spades after clearing");
    }
}