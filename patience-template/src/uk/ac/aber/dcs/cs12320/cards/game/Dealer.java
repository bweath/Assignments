/**
 * Represents the dealer of the game
 * @author Ben Weatherley
 * @version 1.0 (4th May 2018)
 */
package uk.ac.aber.dcs.cs12320.cards.game;
import java.util.ArrayList;

 class Dealer {

	private final ArrayList<Card> piles = new ArrayList<>();
	private final Deck deck;
	private final int distance;
	private final boolean isAdjacent;
	private int index = 0;
/**
 * Constructor for the dealer class
 * 
 * Creates the deck and handles piles
 * @param rules the ruleset that defines how the deck is created
 */
	
    public Dealer(RuleSet rules){
        this.deck = new Deck(rules.getNumOfDecks(), rules.getIsShuffled(), rules.isIncJoker());
        this.distance = (rules.getAmalgamateDistance() + 1);
        this.isAdjacent = (rules.isAmalgamateAdjacent());
    }

     /**
      * Takes a card from the top of the current pile, and returns it (used to update the GUI)
      *
      * @return card on the top of the pile to update the GUI
      */
    public String drawCard() {
            Card temp;
            piles.add(deck.getCurrentCard());
            temp = piles.get(index++);
            return temp.getCardFile();
    }

     /**
      * method to reshuffle the deck
      */
    public void reshuffle(){
        deck.shuffle();
    }

     /**
      * displays the deck in a human readable format
      *
      * @return the deck
      */
    public String displayDeck(){
        return deck.toString();
    }

     /**
      * displays the piles in a human readable format
      *
      * @return the piles
      */
    public String displayPiles(){
        return piles.toString();
    }

     /**
      * Builds a new ArrayList of card files to update the GUI
      *
      * @return ArrayList containing the card files of all cards in the pile
      */
    public ArrayList<String> cardString(){
        ArrayList<String> cardNames;
        cardNames = new ArrayList<>();
        for (Card card : piles){
           cardNames.add(card.getCardFile());
        }
        return cardNames;
    }

    /**
     * the method to combine two piles using two user entered integer values, this is private as no outside class should call this method as
     * it will be called inside this class after necesary checks have been done
     *
     * @param a the integer value of the first card in the pile to amalgamate(should always be smaller than b)
     * @param b the integer value of the first card in the pile to amalgamate (should always be larger than a)
     */
    private void amalgamate(int a, int b){
        //we assume as is always the smaller integer - checks will be done before the ints are passed into the method
        //we also assume that this method is only called in the correct situations, again checks will have been done
        if (b < a) {
            Card tempCard;
            a = a - 1;
            b = b - 1;
            //set our temporary card to the value of the card at position a
            tempCard = piles.get(a);
            piles.remove(a); //remove the card at position a from our pile
            piles.add(b, tempCard);//add the temporary card to the pile
            piles.remove(b+1); //remove the old card from our pile
            index--;

            //this dosent actually update the GUI so we still need to do that in the game class
        }
        else{
            System.err.println("Invalid data fed into private method amalgamate in the dealer class");
            System.exit(1);
        }
    }

    /**
     * Method to check the two cards we are almagamating are legal (same suit/value or a joker)
     * @param a one of the two cards to amalgamate
     * @param b one of the two cards to amalgamate
     */
    private boolean checkAmalgamate(Card a, Card b, boolean print){
        /*first check - if one of a or b is a joker, and the other a playing card or a joker card the
        amalgamtion is legal as a Joker can be combined with anything (in my rules)  */

        if ((a instanceof JokerCard && (b instanceof PlayingCard || b instanceof JokerCard)) ||
                (a instanceof PlayingCard && b instanceof JokerCard)){
            return true;
        }
        else if(a instanceof PlayingCard & b instanceof PlayingCard) {
            if (a.equals(b))
                return true;
            else {
                if(print) {
                    System.out.println("The cards do not have the same suit or value.");
                }
                return false;
            }
        }
        else {
            return false;
        }
    }

    /**
     * Method to handle amalgamating the last pile onto the previous one
     *
     */
    public void amalgamateAdjacent() {
        //set a temporary card a and b to equal the latest two cards in the pile
        if (piles.size() < 2) {
            System.out.println("There is less than one card!");
        } else {
            Card _a = piles.get(piles.size() - 1);
            Card _b = piles.get(piles.size() - 2);
            //check they are legal
            if (checkAmalgamate(_a, _b, true)) {
                //if they are then amalgamate them
                amalgamate(piles.size(), piles.size() - 1);
            }
        }
    }

    /**
     * Method to handle amalgamating the last pile with the pile X piles over, where X is the amalgamteDistance in the
     * rule set
     */
    public void amalgamateDistance() {
        if (piles.size() < distance + 1) {
            System.out.println("There are not enough cards for that! You must have at least " + (distance + 1) + " cards!");
        } else {
            Card _a = piles.get(piles.size() - 1);
            Card _b = piles.get(piles.size() - 1 - distance);
            //check they are legal
            if (checkAmalgamate(_a, _b, true)) {
                //if they are then amalgamate them
                amalgamate(piles.size(), piles.size() - distance);
            }
        }
    }


    private boolean checkLegalDistance(int a, int b) {
        //checking to make sure the integers are legal based on the rule set
            if ((isAdjacent) && ((a - b) == 1) || ((a - b) == distance)) {
                return true;
            } else if (!(isAdjacent) && ((a - b)) == 1) {
                System.out.println("You cannot amalgamate adjacent cards with your ruleset.");
                return false;
            } else {
                System.out.println("Please enter two valid piles.");
                return false;
            }
    }

     /**
      * Method to handle amalgamating any piles in the center of the card table by using two user inputs
      * Because of this it needs to check if the piles are a legal distance apart
      * Values passed into this must have a being greater than b
      * @param a pile number of card a
      * @param b pile number of card b
      */
    public void amalgamateMiddle(int a, int b){
        //first check if the cards are the right distance apart
        if (checkLegalDistance(a,b)){
            //if they are then next check if the cards are of the same suit and class
            Card _c = piles.get(a -1);
            Card _d = piles.get(b -1);
            if (checkAmalgamate(_c, _d, true)){
                //if they are then amalgamate them
                amalgamate(a, b);
            }
        }
    }

    /**
     * How many cards are left in the deck?
     *
     * @return the number of cards left in the deck
     */
    public int getCardsRemaining(){
        return deck.getCardsRemaining();
    }

     /**
      * Checks every possible combination of moves and makes the one closest to the start of the piles
      * I think that is what the assignment brief meant by "furthest", anyway
      *
      * @return True if no moves left(to break from play for me many), false otherwise
      */
    public boolean playForMeOnce(){
        //setting up the variables we will use to check every combination in our arraylist
        boolean _madeMove = false;
        int _basePile = 1;

        do{
            int _adjacentPile = _basePile + 1;
            int _distantPile = _basePile + distance;
            //check that we havent run out of cards to compare for the distant piles yet
            if (_distantPile <= piles.size()) {
                Card _a = piles.get(_basePile - 1);
                Card _b = piles.get(_distantPile - 1);
                //check if the piles combine and that we have not yet made a move
                if (checkAmalgamate(_a, _b, false)) {
                    //amalgamate the piles and set made move to true
                    amalgamate(_distantPile, _basePile);
                    _madeMove = true;
                }
            }
                else if ((!isAdjacent) && (_distantPile >= piles.size()) && (deck.getCardsRemaining() > 0)){
                    drawCard();
                    _madeMove =true;
                }
                else if((!isAdjacent) && (_distantPile >= piles.size()) && (deck.getCardsRemaining() == 0)) {
                System.out.println("No moves left");
                return true;
            }
            if(this.isAdjacent) {//if adjacent amalgamation is true, look at possible combinations for distant and adjacent
                if (_adjacentPile <= piles.size()) { //if the value of adjacent pile is less than or equal to the size of the pile
                    Card _a = piles.get(_basePile - 1);
                    Card _b = piles.get(_adjacentPile - 1);

                    //check if the piles combine and that we have not yet made a move
                    if (checkAmalgamate(_a, _b, false) && (!_madeMove)) {
                        amalgamate(_adjacentPile, _basePile);
                        _madeMove = true;
                    }
                } else if (_adjacentPile >= piles.size() && (deck.getCardsRemaining() > 0)) {
                        drawCard();
                        _madeMove = true;
                } else if (_adjacentPile >= piles.size() && (deck.getCardsRemaining() == 0)) {
                        System.out.println("No moves left");
                        return true;
                }
            }


            _basePile++;

            //if we get to here and a move has not been made, draw a card

        } while (!_madeMove);
        return false;
    }

     /**
      * how many piles are there?
      *
      * @return the number of piles
      */
    public int getPileSize(){
        return piles.size();
    }


}

