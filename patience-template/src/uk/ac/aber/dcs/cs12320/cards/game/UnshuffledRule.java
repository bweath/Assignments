/**
 * Represents the unshuffled rule set - inherits from RuleSet
 * @author Ben Weatherley
 * @version 1.0 (25th April 2018)
 */
package uk.ac.aber.dcs.cs12320.cards.game;

  class UnshuffledRule extends RuleSet {
    /**
     * Constructor for the UnshuffledRule
     *
     * Sets up the unshuffled rule set so that one unshuffled deck with no jokers is used,
     * Distance between piles is set to 2, and amalgamating adjacent piles is allowed.
     */

    public UnshuffledRule(){
        this.numOfDecks = 1;
        this.incJoker = false;
        this.isShuffled = false;
        this.amalgamateAdjacent = true;
        this.amalgamateDistance = 2;
        this.ruleName = "the unshuffled rule set";

    }

}
