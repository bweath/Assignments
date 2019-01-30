/**
 * Represents a set of rules for the game which all other rulesets must inherit
 * @author Ben Weatherley
 * @version 1.0 (4th May 2018)
 */
package uk.ac.aber.dcs.cs12320.cards.game;
 abstract class RuleSet {

    int numOfDecks;
    boolean isShuffled;
    boolean incJoker;
    int amalgamateDistance;
    boolean amalgamateAdjacent;
    String ruleName;


    public int getNumOfDecks() {
        return numOfDecks;
    }

    public boolean getIsShuffled() {
        return isShuffled;
    }

    public boolean isIncJoker() {
        return incJoker;
    }

    public int getAmalgamateDistance() {
        return amalgamateDistance;
    }

    public boolean isAmalgamateAdjacent() {
        return amalgamateAdjacent;
    }

    @Override
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("You have decided to play with ").append(ruleName).append(". This uses ").append(getNumOfDecks());
        if (getNumOfDecks() == 1){
            sb.append(" pack ");
        } else {
            sb.append(" packs ");
        }
        sb.append("of cards and does ");
        if (!incJoker){
            sb.append("not ");
        }
        sb.append("include jokers. \nYou can");
        if (!amalgamateAdjacent){
            sb.append("not");
        }
        sb.append(" combine adjacent piles, and the number of piles between piles to combine them is ")
                .append(amalgamateDistance).append(". Have fun!\n");

        return sb.toString();
    }
}
