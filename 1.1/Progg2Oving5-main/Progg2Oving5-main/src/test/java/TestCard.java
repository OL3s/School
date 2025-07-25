import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;
import com.oving5.backend.Card;

import java.awt.Color;

public class TestCard {

    @Test
    public void testCardInitialization() {
        Card card = new Card('H', 10);
        assertEquals('H', card.getSuit(), "Card suit should be 'H'");
        assertEquals(10, card.getValue(), "Card value should be 10");
        assertEquals(Color.RED, card.getColor(), "Card color should be RED for Hearts");
    }

    @Test
    public void testCardToString() {
        Card card = new Card('S', 12);
        String expected = "S12";
        assertEquals(expected, card.toString(), "Card string representation should match");
    }

    @Test
    public void testSuitToString() {
        assertEquals("♥", Card.suitToString('H'), "Suit 'H' should be converted to ♥");
        assertEquals("♦", Card.suitToString('D'), "Suit 'D' should be converted to ♦");
        assertEquals("♠", Card.suitToString('S'), "Suit 'S' should be converted to ♠");
        assertEquals("♣", Card.suitToString('C'), "Suit 'C' should be converted to ♣");
        assertEquals("ERROR", Card.suitToString('X'), "Invalid suit should return 'ERROR'");
    }

    @Test
    public void testValueToString() {
        assertEquals("A", Card.valueToString(1), "Value 1 should be converted to 'A'");
        assertEquals("J", Card.valueToString(11), "Value 11 should be converted to 'J'");
        assertEquals("Q", Card.valueToString(12), "Value 12 should be converted to 'Q'");
        assertEquals("K", Card.valueToString(13), "Value 13 should be converted to 'K'");
        assertEquals("10", Card.valueToString(10), "Value 10 should be converted to '10'");
    }

    @Test
    public void testGetSuits() {
        char[] suits = Card.getSuits();
        assertArrayEquals(new char[]{'H', 'D', 'S', 'C'}, suits, "Suits should be H, D, S, C");
    }

    @Test
    public void testGetColor() {
        Card redCard = new Card('H', 5);
        assertEquals(Color.RED, redCard.getColor(), "Card color should be RED for Hearts");

        Card blackCard = new Card('S', 7);
        assertEquals(Color.BLACK, blackCard.getColor(), "Card color should be BLACK for Spades");
    }
}