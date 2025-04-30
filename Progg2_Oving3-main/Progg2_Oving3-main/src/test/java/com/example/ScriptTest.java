package com.example;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;
import java.util.ArrayList;

public class ScriptTest {

    @Test
    public void testScriptExecution() {
      Script script = new Script();
      String result = script.execute("a lot of text, b not much else");
      assertEquals("(B Lot Of Text, B Not Much Else)", result);
    }

}
