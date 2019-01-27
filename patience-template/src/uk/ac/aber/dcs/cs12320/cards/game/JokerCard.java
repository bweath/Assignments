/**
 * Represents a Joker Card object - inherits from Card
 * @author Ben Weatherley
 * @version 1.0 (25th April 2018)
 */
package uk.ac.aber.dcs.cs12320.cards.game;
public class JokerCard implements Card {
    /**
     * Constructor for a Joker card, it has no suit or value, and is only for use in certain rulesets
     */
    public JokerCard(){
    }

    /**
     * What is the cards name?
     *
     * @return The name of the joker card - Joker
     */
    @Override
    public String toString(){
        return ("Joker");
    }

    /**
     * What is the cards file name?
     *
     * @return The file name of the joker card for the gui to use
     */
    public String getCardFile(){
        return ("j.gif");
    }


    /**
     * A Joker card is always considered equal to another joker card
     *
     * @param o the other card to compare against
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        return true;
    }
}
