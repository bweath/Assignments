/**
 * Represents a Playing Card object - inherits from Card
 * @author Ben Weatherley
 * @version 1.0 (25th April 2018)
 */
package uk.ac.aber.dcs.cs12320.cards.game;

import java.util.Objects;

public class PlayingCard implements Card{
    /**
     * The suit of our card, using Suit enum.
     */
    private final Suit suit;

    /**
     * The value of our card, using CardValue enum.
     */
    private final CardValue value;
    
    /**
     * The name of our card for use in the GUI (e.g. 4d)
     */
    private final String cardName;

    /**
     * Constructor for the card
     * @param suit The cards suit
     * @param value The cards value
     */
    public PlayingCard(Suit suit, CardValue value){
        this.suit = suit;
        this.value = value;
        cardName = setCardName();
    }

    /**
     * Returns the suit of the card
     *
     * @return the cards suit
     */
    public Suit getSuit() {
        return suit;
    }

    /**
     *Returns the value of the card
     *
     * @return the cards value
     */

    public CardValue getValue() {
        return value;
    }

    /**
     * Displays the cards information in a user friendly format
     *
     * @return The cards information
     */
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append(this.value).append(" of ").append(this.suit);

        return sb.toString();
    }

	/**
	 * Note that this only compares equality based on a
	 * cards value or a cards suit (if either are the same the cards are deemed equal
	 *
	 * @param o the other card to compare against
	 */
	@Override
	public boolean equals(Object o) {
		if (this == o) return true;
		if (o == null || getClass() != o.getClass()) return false;
		PlayingCard that = (PlayingCard) o;
		return suit == that.suit ||
				value == that.value;
	}

	/**
     * On creation of the card the cards name is set so that cards can be added to the gui
     */
    private String setCardName() {
    	String _cardname = "";
    	switch (this.value) {
    	case Ace: _cardname = "a";
    	break;
    	case Two: _cardname = "2";
    	break;
    	case Three: _cardname = "3";
    	break;
    	case Four: _cardname = "4";
    	break;
    	case Five: _cardname = "5";
    	break;
    	case Six: _cardname = "6";
    	break;
    	case Seven: _cardname = "7";
    	break;
    	case Eight: _cardname = "8";
    	break;
    	case Nine: _cardname = "9";
    	break;
    	case Ten: _cardname = "t";
    	break;
    	case Jack: _cardname = "j";
    	break;
    	case Queen: _cardname = "q";
    	break;
    	case King: _cardname = "k";
    	break;
    	default: System.exit(1);
    	break;
    	}
    	StringBuilder sb = new StringBuilder();
        sb.append(this.suit);
        String tempValue = sb.toString();
    	_cardname = _cardname + tempValue.toLowerCase().charAt(0) + ".gif";
    	return _cardname;
    }

    public String getCardFile(){
    	return cardName;
	}
    
}


