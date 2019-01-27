/**
 * Represents the standard rules of the game
 * @author Ben Weatherley
 * @version 1.0 (4th May 2018)
 */
package uk.ac.aber.dcs.cs12320.cards.game;
   class NormalRule extends RuleSet {


    /**
     * Constructor for the NormalRule
     *
     * Sets up the normal ruleset so that one shuffled deck with no jokers is used,
     * Distance between piles is set to 2, and amalgamating adjacent piles is allowed.
     */

    public NormalRule(){
        this.numOfDecks = 1;
        this.incJoker = false;
        this.isShuffled = true;
        this.amalgamateAdjacent = true;
        this.amalgamateDistance = 2;
        this.ruleName = "the normal rule set";

    }


}
