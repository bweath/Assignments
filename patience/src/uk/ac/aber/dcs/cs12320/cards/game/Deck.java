/**
 * Represents a Deck object which is a collection of cards
 * @author Ben Weatherley
 * @version 1.0 (25th April 2018)
 */
package uk.ac.aber.dcs.cs12320.cards.game;
import java.util.Random;

 class Deck {

    /**
     * An array of cards in the deck
     */
    private final Card[] cards;

    /**
     * The number of cards currently in the deck
     */
    private int cardsRemaining;

    /**
     * Default constructor for a deck, that creates a deck compliant with the standard rule set of the game
     */

    public Deck(){
        this(1,true,false);
    }

    /**
     * Constructor for the deck
     *
     * @param numDecks The amount of decks we will use (For alternate rule sets)
     * @param shuffle If we shuffle the deck or not
     * @param Joker If the deck contains Jokers (
     */
    public Deck(int numDecks, boolean shuffle, boolean Joker){

        int _joker = 0;
        if (Joker) {
            _joker = numDecks * 2;
        }

        //the number of cards in the deck equals the number of decks * 52  plus the number of Jokers.
        this.cards = new Card[(numDecks * 52 + _joker)];
        cardsRemaining = this.cards.length;
        //adds the cards to our deck in the format of all clubs, then diamonds, then spades, then hearts
        //for each of our decks:
        for (int d = 0; d < numDecks; d++){
            //for each of our suits:
            for (int s = 0; s < 4; s++){
                //for each of our values:
                for (int v = 0; v < 13; v++ ){
                    //code to add a card to the deck
                    int _index = (numDecks * ((s * 13 ) + v) + d);
                    this.cards[_index] = new PlayingCard(Suit.values()[s],CardValue.values()[v]);
                }
            }
        }

        //If the deck contains jokers, two jokers are added after the standard playing cards
        for (int d = numDecks * 52; d < this.cards.length; d++) {
            this.cards[d] = new JokerCard();
        }

        //Shuffle the deck if we need to
        if(shuffle){
            this.shuffle();
        }
    }

    public void shuffle(){
        //creating the random number generator
        Random rng = new Random();

        //creating a temporary card to hold our card while we swap it
        Card temp;
        int b;

        //loop 50 times to ensure the deck is fully shuffled
        for (int i = 0; i <50; i++){
            //for each card in our array
            for (int a = 0; a < this.cards.length; a++){
                //generate a random card which we will swap with card a
                b = rng.nextInt(this.cards.length);//generates a random number between 1 and our number of cards
                //swapping the cards around using our temporary card
                temp = this.cards[a];
                this.cards[a] = this.cards[b];
                this.cards[b] = temp;
            }
        }
    }


    /**
     * Prints the deck in a human readable format
     *
     * @return The deck in a human readable format
     */
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < this.cards.length; i++){
            sb.append(this.cards[i].toString()).append(". ");
        }
        return sb.toString();
    }

    /**
     * Gets a card from the 'top' of the deck and lowers the 'top' of the deck by 1
     *
     * @return the drawn card
     */
    public Card getCurrentCard() {
    	return cards[--cardsRemaining];
    }

    /**
     * How many cards are left in the deck
     *
     * @return the number of cards left in the deck
     */
    public int getCardsRemaining(){
        return cardsRemaining;
    }
}
