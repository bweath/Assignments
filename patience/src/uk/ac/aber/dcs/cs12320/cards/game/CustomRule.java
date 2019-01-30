/**
 * Represents the Custom rule set - inherits from RuleSet
 * @author Ben Weatherley
 * @version 1.0 (25th April 2018)
 */

package uk.ac.aber.dcs.cs12320.cards.game;
import java.util.Scanner;

 class CustomRule extends RuleSet {
    public CustomRule (){
        readKeyboard();
        this.ruleName = "a custom rule set";
    }

    private void readKeyboard() {
        System.out.println("You have decided to create a custom rule set: ");
        this.numOfDecks = getUserDecks();
        System.out.println("Do you want your deck to be shuffled?\n You may shuffle it later but it will prevent score saving. (Y/N)");
        this.isShuffled = readBoolean();
        System.out.println("Do you want your deck to include Jokers? (Y/N)");
        this.incJoker = readBoolean();
        System.out.println("Do you want to allow amalgamating adjacent cards?\n This makes the game much more boring and prevents a perfect score (Y/N)");
        this.amalgamateAdjacent = readBoolean();
        this.amalgamateDistance = getUserDistance();


    }


    /**
     * Method to make sure the user enters a valid integer value for the number of decks
     *
     * @return The users input for the number of decks
     */
    private int getUserDecks(){
        Scanner _in = new Scanner(System.in);
        int _x = 0;
        System.out.println("How many packs of cards would you like to play with: ");
        do { //some code to make sure the user enters an int
            if (_in.hasNextInt()) { //checks to see if the scanner contains an int
                _x = _in.nextInt();
                if(_x > 10 || _x < 1){
                    System.out.println("You must have between 1 and 10 packs of cards");
                }
            }
            else { //only occurs when scanner didn't contain an int, so reminds user to enter an int, not a string
                System.out.println("Please enter an integer value");
                _in.next();
            }
        }
        while (_x > 10 || _x < 1);
        return _x;
    }


    /**
     * Method to make sure the user enters a valid integer value for the amalgamation distance
     *
     * @return The users input for amalgamation distance
     */
    private int getUserDistance(){
        Scanner _in = new Scanner(System.in);
        int _x = 0;
        System.out.println("How many piles must be between two piles for amalgamation?(1-5)");
        do {
            if (_in.hasNextInt()) {
                _x = _in.nextInt();
                if(_x > 5 || _x < 1){
                    System.out.println("The distance must be between 1 and 5");
                }
            }
            else { //only occurs when scanner didn't contain an int, so reminds user to enter an int, not a string
                System.out.println("Please enter an integer value");
                _in.next();
            }
        }
        while (_x > 10 || _x < 1);
        return _x;
    }

    /**
     * Reads user input in form of Y/N and converts to bool
     *
     * @return the users input converted to boolean Y - true, N - false
     */
    private boolean readBoolean() {
        Scanner in = new Scanner(System.in);
        String input;
        do {
            input = in.nextLine().toUpperCase();
            if (!input.equals("Y") && !input.equals("N")) {
                System.err.println("Please enter a valid value (Y/N)");
            }
        }
        while (!input.equals("Y") && !input.equals("N"));
        if (input.equals("Y")) {
            return true;
        } else return false;
    }
}
