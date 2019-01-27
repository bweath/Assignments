/**
 * The Game of patience main class
 * @author Chris Loftus, Lynda Thomas and Ben Weatherley
 * @version 3.0
 */

package uk.ac.aber.dcs.cs12320.cards.game;
import java.io.*;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Scanner;
import javafx.application.Application;
import javafx.stage.Stage;
import uk.ac.aber.dcs.cs12320.cards.gui.javafx.CardTable;


public class Game extends Application {

    private CardTable cardTable;
    private Dealer dealer;
    private RuleSet rules;
    private Scanner scan;
    private boolean voidScore = false;
    private ArrayList<String> cardStrings;
    private ArrayList<Leaderboard> leaderboards;
    private int minScore;


    @Override
    public void start(Stage stage) {
        cardTable = new CardTable(stage);
        // The interaction with this game is from a command line
        // menu. We need to create a separate non-GUI thread
        // to run this in. DO NOT REMOVE THIS.
        Runnable commandLineTask = () -> {
            // REPLACE THE FOLLOWING EXAMPLE WITH YOUR CODE

            cardStrings = new ArrayList<>();
            cardTable.cardDisplay(cardStrings);
            initialise();
            runMenu();
            System.exit(1);
        };
        Thread commandLineThread = new Thread(commandLineTask);
        // This is how we start the thread.
        // This causes the run method to execute.
        commandLineThread.start();

    }


    /**
     * updates the gui by rebuilding the cardStrings ArrayList
     */
    private void updateGUI(){
        cardStrings = dealer.cardString();
        cardTable.cardDisplay(cardStrings);
    }

    /**
     * draws a card from the deck
     */
    private void drawCard() {
        if (dealer.getCardsRemaining() == 0) {
            System.out.println("There are no cards left in the deck!");
        } else {
            cardStrings.add(dealer.drawCard());
            cardTable.cardDisplay(cardStrings);
        }
    }


    /**
     * sets up the dealer, leaderboard and the rule set based of of user inputs
     */
    private void initialise(){
        int _response;
        leaderboards = new ArrayList<>();
        try {
            loadLeaderboard();
        } catch (FileNotFoundException e) {
            System.err.println("The file: leaderboard.txt does not exist.");
        } catch (IOException e) {
            System.err.println("An unexpected error occurred when trying to open the file leaderboard.txt");
            System.err.println(e.getMessage());
        }
        sortList();

        do {
            System.out.println("Please choose a rule set:");
            System.out.println("1 - Normal rules");
            System.out.println("2 - Include jokers");
            System.out.println("3 - Normal rules but deck starts unshuffled (prevents score saving)");
            System.out.println("4 - Custom rules");
            System.out.println("5 - display rules");
            System.out.println("What would you like to do:");
            scan = new Scanner(System.in);
            if (scan.hasNextInt()) { //checks to see if the scanner contains and int, if so, foodPerDay = scanner
                _response = scan.nextInt();
            } else {
                //only occurs when scanner didn't contain an int
                _response = -1;
            }
            switch (_response) {
                case 1:
                    rules = new NormalRule();
                    break;
                case 2:
                    rules = new JokerRule();
                    break;
                case 3:
                    rules = new UnshuffledRule();
                    break;
                case 4:
                    rules = new CustomRule();
                    break;
                case 5:
                    System.out.println(printRules());
                    break;
                case -1:
                    System.out.println("Please enter your value in numerical form(1,2,3,4,5).");
                    //reminds the user to enter an int, as this case should only be accessed when a user enters a non-integer value (or -1)
                    break;
                default:
                    System.out.println("Please enter a number between 1 and 5");
            }
        } while (_response > 4 || _response < 1);
        dealer = new Dealer(rules);
        System.out.println(rules.toString());
    }


    /**
     * Simple print menu method to display our menu to the user
     */
    private void printMenu(){
        System.out.println("1 - Print the pack out");
        System.out.println("2 - Reshuffle pack (prevents score saving)");
        System.out.println("3 - Draw a card");
        if (rules.isAmalgamateAdjacent()){
            System.out.println("4 - Make a move, move last pile onto previous one");
        }
        else {
            System.out.println("4 - Disabled - You cannot combine adjacent cards with these rules!");
        }
        System.out.println("5 - Make a move, move last pile back over " + rules.getAmalgamateDistance() + " piles");
        System.out.println("6 - Amalgamate piles in the middle (by giving their numbers)");
        System.out.println("7 - Print the displayed cards on the command line");
        System.out.println("8 - Play for me once");
        System.out.println("9 - Play for me many times");
        System.out.println("10 - Display top 10 scores");
        System.out.println("Q - Quit");

    }

    /**
     * runs the games menu
     */
    private void runMenu(){
        String response;
        do {
            printMenu();
            System.out.println();
            System.out.println("What would you like to do:");
            scan = new Scanner(System.in);
            response = scan.nextLine().toUpperCase();
            switch (response) {
                case "1":
                    System.out.println(dealer.displayDeck());
                    break;
                case "2":
                    reshuffleDeck();
                    break;
                case "3":
                    drawCard();
                    break;
                case "4":
                    amalgamateAdjacent();
                    break;
                case "5":
                    amalgamateDistance();
                    break;
                case "6":
                    amalgamateMiddle();
                    break;
                case "7":
                    displayPiles();
                    break;
                case "8":
                    playForMeOnce();
                    break;
                case "9":
                    playForMeMany();
                    break;
                case "10":
                    System.out.println(sortList());
                    System.out.println("The score to beat is: " + minScore + "!");
                    break;
                case "Q":
                    quit();
                    break;
                default:
                    System.out.println("Try again");
            }
        } while (!response.equals("Q"));
    }

    /**
     * reshuffles the deck and prevents saving your score
     * (to prevent continuously reshuffling the deck for the perfect draw)
     */
    private void reshuffleDeck(){
        dealer.reshuffle();
        System.out.println("Deck has been reshuffled");
        voidScore = true;
    }


    /**
     * Prints the current piles on the card table in text form
     */
    private void displayPiles(){
        System.out.println("Piles currently on the table:");
        System.out.println(dealer.displayPiles());
        //delete this next line later
        System.out.println(cardStrings);
    }


    /**
     * simple method to amalgamate the two most recent piles
     * checks to make sure adjacent amalgamation is allowed in the current rule set
     */
    private void amalgamateAdjacent(){
        if (rules.isAmalgamateAdjacent()) {
            dealer.amalgamateAdjacent();
            updateGUI();
        }
        else {
            System.out.println("You cannot do this with your ruleset.");
        }
    }


    /**
     * simple method to amalgamate the latest pile over a distance - used in the menu
     */
    private void amalgamateDistance(){
        dealer.amalgamateDistance();
        updateGUI();
    }


    /**
     * Method to gather user input for amalgamation
     */
    private int getUserPile() {
        int _x = 0;
        Scanner _in = new Scanner(System.in);
        do { //some code to make sure the user enters an int
            if (_in.hasNextInt()) { //checks to see if the scanner contains an int
                _x = _in.nextInt();
                if(_x > cardStrings.size() || _x < 1){
                    System.out.println("Sorry, that pile does not exist");
                }
            }
            else { //only occurs when scanner didn't contain an int, so reminds user to enter an int, not a string
                System.out.println("Please enter an integer value");
                _in.next();
            }
        }
        while (_x > cardStrings.size() || _x < 1); //checks to make sure the value corresponds to a pile
        return _x;
    }


    /**
     * Method to amalgamate piles in the middle of the card table
     */
   private void amalgamateMiddle() {
       if (cardStrings.size() < (rules.getAmalgamateDistance() + 2)) {
           System.out.println("You have not drawn enough cards to do that!");
       } else {
           System.out.println("Please enter the first piles number: ");
           int _a = getUserPile();
           System.out.println("Please enter the second piles number: ");
           int _b = getUserPile();

           if (_a == _b) {
               System.out.println("You cannot amalgamate a pile with itself.");
           } else if (_a > _b) {
               dealer.amalgamateMiddle(_a, _b);
           } else {
               dealer.amalgamateMiddle(_b, _a);
           }
           updateGUI();
       }
   }

    /**
     * method to make the game do one move by itself
     */
   private void playForMeOnce(){
        voidScore = true;
        dealer.playForMeOnce();
        updateGUI();
   }


    /**
     * Loops the play for me once function, resulting in the game making x amount of moves for you
     * ends automatically if the game runs out of moves
     */
    private void playForMeMany(){
        int _x = 0;
       Scanner _in = new Scanner(System.in);
       System.out.println("How many moves do you want to take?");
       do { //some code to make sure the user enters an int
           if (_in.hasNextInt()) { //checks to see if the scanner contains an int
               _x = _in.nextInt();
               if(_x > 1000 || _x < 1){
                   System.out.println("Sorry, please enter a number between 1 and 1000");
               }
           }
           else { //only occurs when scanner didn't contain an int, so reminds user to enter an int, not a string
               System.out.println("Please enter an integer value");
               _in.next();
           }
       }
       while (_x > 1000 || _x < 1); //checks to make sure the value corresponds to a pile
        boolean stop;
        for(int _y = _x; _y > 0; _y --){
            voidScore = true;
            stop = dealer.playForMeOnce();
            updateGUI();
            try
            {
                Thread.sleep(150);
            }
            catch(InterruptedException ex)
            {
                Thread.currentThread().interrupt();
            }

            if (stop){
                break;
            }
        }
   }

    /**
     * Prints out a message informing the user how the game works
     *
     * @return The rules of the game
     */
    private String printRules(){
        return "The object of this game is to end up with as few piles of cards as possible. \n" +
                "By default you will be given one shuffled deck, that does not include jokers. \n" +
                "You then draw cards from the deck, and may combine piles of cards, if the cards are the same suit or value. (if you use \n" +
                "jokers they can be combined with any card - including another joker)." +
                "The distance piles must be from each other for you to combine them depends on the rule set you use. \n" +
                "By default piles must either be adjacent or have 2 other piles between them for you to be able to combine them. \n" +
                "You can customise all of these values by selecting a custom rule set.";
    }


    /**
     * Loads the leaderboard from a text file
     *
     * @throws IOException ignores any IO exceptions as they are dealt with a try and catch elsewhere
     */
    private void loadLeaderboard() throws IOException {
        try (FileReader fr = new FileReader("leaderboard.txt");
             BufferedReader br = new BufferedReader(fr);
             Scanner infile = new Scanner(br)) {
            /*Use the delimiter pattern so that we don't have to clear end of line
            characters after doing a nextInt or nextBoolean */
            infile.useDelimiter(":|\r?\n|\r");
            for (int i = 0; i < 10; i++) {
                Leaderboard temp = new Leaderboard();
                temp.load(infile);
                leaderboards.add(temp);
            }
        }
    }


    /**
     * Sorts our leaderboard by score
     *
     * @return sorted leaderboard
     */
    private ArrayList<Leaderboard> sortList(){
        Collections.sort(
                leaderboards,
                (player1, player2) -> player1.getScore()
                        - player2.getScore());
        Leaderboard _temp;
        _temp = leaderboards.get(9);
        minScore = _temp.getScore();
        return leaderboards;
    }


    /**
     * Saves the kennel information
     *
     * @throws IOException If some IO error occurs
     */
    private void save() throws IOException {
        // Again using try-with-resource so that I don't need to close the file explicitly
        try (FileWriter fw = new FileWriter("leaderboard.txt");
             BufferedWriter bw = new BufferedWriter(fw);
             PrintWriter outfile = new PrintWriter(bw);) {

            for (Leaderboard l : leaderboards) {
                l.save(outfile);
            }
        }
    }

    /**
     * Handles reading the users name and saving their score
     * @param _userScore
     */
    private void saveScore(int _userScore) {
        Scanner _in = new Scanner(System.in);
            System.out.println("You scored " + _userScore + "! Thats in the top 10!");
            leaderboards.remove(9);
            System.out.println("Please enter your name: ");
            String _name = scan.nextLine();
            Leaderboard user = new Leaderboard(_name, _userScore);
            leaderboards.add(user);
            try {
                save();
            } catch (IOException e) {
                System.err.println("Problem when trying to write to file: leaderboard");
            }
            System.out.println("The new leaderboard is: ");
            System.out.println(sortList());
    }

    /**
     * handles quiting the game
     * checks to see if the user has a new highscore and if so saves it
     */
    private void quit(){
        int _userScore = dealer.getPileSize();
        if(dealer.getCardsRemaining() ==0){
            if (!voidScore && (_userScore < minScore)) {
            saveScore(_userScore);
        }
        if(voidScore  && (_userScore < minScore)){
            System.out.println("As you voided your ability to save by using a function (reshuffle, playForMe, playForMeMany), you normally " +
                    "would not be allowed to save. \n However for the purpose of this assignment (testing/marking) that is not the case.");
            saveScore(_userScore);

        }
        if(_userScore >= minScore){

                System.out.println("You scored: " + _userScore + "!");
                System.out.println(minScore);
                System.out.println("Sorry you didnt score high enough to be on the leaderboards, better luck next time!");
            }
    }
    else {
            System.out.println("Quitting the game without saving as not all cards were drawn");
        }

    }

    // //////////////////////////////////////////////////////////////
    public static void main(String args[]) {
        //Game game = new Game();
        //game.playGame();
        Application.launch(args);
    }
}
