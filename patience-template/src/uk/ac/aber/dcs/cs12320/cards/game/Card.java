/**
 * An interface for all card objects
 * @author Ben Weatherley
 * @version 1.0 (25th April 2018)
 */
package uk.ac.aber.dcs.cs12320.cards.game;
public interface Card {
    //No requirements to be a card, as the Jokers have nothing in common with playing cards other than the fact that they are a card
    @Override
    String toString();
    
    String getCardFile();

    boolean equals(Object o);

}