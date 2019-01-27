/**
 * Represents a leaderboard object - used to save and load players scores
 * @author Ben Weatherley
 * @version 1.0 (25th April 2018)
 */
package uk.ac.aber.dcs.cs12320.cards.game;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Scanner;


  class Leaderboard {
    private String name;
    private int score;

    /**
     * default constructor for leaderboard
     */
    public Leaderboard(){
        this.name ="";
        this.score = 100;
    }

    /**
     * Constructor for the leaderboard
     *
     * @param name The players name
     * @param score The players score
     */
    public Leaderboard(String name, int score ){
        this.name = name;
        this.score = score;
    }

    /**
     * Saves info from the leaderboard to file
     *
     * @param pw the PrintWriter
     */
    public void save(PrintWriter pw) {
        pw.println(name + ":" + score);
    }

    /**
     * Loads info of the leaderboard from a file
     *
     * @param infile Scanner to read file
     */
    public void load(Scanner infile){
        /* Use the delimiter pattern so that we don't have to clear end of line
        characters after doing a nextInt or nextBoolean*/
        infile.useDelimiter(":|\r?\n|\r");
        name = infile.next();
        score = infile.nextInt();
        }

      /**
       *Prints the leaderboard in a human frindly form
       *
       * @return the leaderboard in a human friendly form
       */
      @Override
      public String toString() {
          return (this.name + " scored " + this.score);
      }


      /**
       * gets the score
       * @return the score
       */
      public int getScore() {
          return score;
      }


  }



