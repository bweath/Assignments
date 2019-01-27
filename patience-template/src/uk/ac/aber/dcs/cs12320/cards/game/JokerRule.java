/**
 * Represents the Joker rule set - inherits from RuleSet
 * @author Ben Weatherley
 * @version 1.0 (25th April 2018)
 */
package uk.ac.aber.dcs.cs12320.cards.game;
 class JokerRule extends RuleSet{
     /**
      * Constructor for the JokerRule
      *
      * Sets up the normal ruleset so that one shuffled deck with jokers is used,
      * Distance between piles is set to 2, and amalgamating adjacent piles is allowed.
      */

    public JokerRule(){
        this.numOfDecks = 1;
        this.incJoker = true;
        this.isShuffled = true;
        this.amalgamateAdjacent = true;
        this.amalgamateDistance = 2;
        this.ruleName = "the joker rule set";
    }
}
