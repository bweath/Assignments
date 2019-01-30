/**
 * Displays the card images on a table (the Javafx stage)
 * @author Chris Loftus and Lynda Thomas
 * @version 2.0
 */
package uk.ac.aber.dcs.cs12320.cards.gui.javafx;

import javafx.application.Platform;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ScrollPane;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.*;
import javafx.scene.paint.Color;
import javafx.stage.Stage;
import uk.ac.aber.dcs.cs12320.cards.game.Game;



import javax.swing.*;
import java.awt.*;
import java.io.PrintStream;
import java.util.ArrayList;

public class CardTable {
    private final Stage stage;
    private String[] cards;
    private boolean done;

    public CardTable(Stage stage) {
        this.stage = stage;
        stage.setTitle("The Cards");
    }


    /**
     * Called when the user quits the game. It results
     * in the face-down pack of cards not being displayed.
     */
    public void allDone() {
        done = true;
    }

    /**
     * Displays all the face-up cards (just the top showing cards)
     * and if the game is not over then also displays the face-down deck.
     * @param c the list of face-up cards
     */
    public void cardDisplay(ArrayList<String> c) {

        /* We need to do this within the GUI thread. We assume
         that the method is called by a non-GUI thread */
        Platform.runLater(() -> {
            cards = new String[c.size()];
            cards = c.toArray(cards);

            //setting up the second row of the GUI
            BorderPane row2 = new BorderPane();

            //setting up the Scroll Pane
            ScrollPane sp = new ScrollPane();
            sp.setMinHeight(150);
            sp.setMaxHeight(150);

            //setting up the BorderPane
            BorderPane root = new BorderPane();
            Scene scene = new Scene(root, 800, 210);

            //setting up the Hbox cards will fill
            scene.setFill(Color.BLACK);
            HBox box = new HBox();

            //setting up the left half of the second row HBox
            HBox row2Left = new HBox();
            row2Left.setPadding(new Insets(10));
            row2Left.setSpacing(10);

            //setting up the right half of the second row HBox
            HBox row2Right = new HBox();
            row2Right.setPadding(new Insets(10));
            row2Right.setSpacing(10);

            //Setting up buttons
            Button btnDraw = new Button("Draw a card");
            Button btnCombine = new Button("Combine Piles");
            Button btnQuit = new Button("Quit");
            /*btnDraw.setMinSize(100,40);
            btnQuit.setMinSize(100,40);
            btnCombine.setMinSize(100,40);*/

            //adding console to the gui
            /*
            TextArea ta = new TextArea();
            //ta.setPrefSize(800,600);
            Console console = new Console(ta);
            PrintStream ps = new PrintStream(console, true);
            System.setOut(ps);
            System.setErr(ps);

            Pane pane = new Pane();
            */
            //Adding all the items to the BorderPane
            row2Left.getChildren().addAll(btnDraw, btnCombine);
            row2Right.getChildren().addAll(btnQuit);
            row2.setLeft(row2Left);
            row2.setRight(row2Right);
            root.setTop(sp);
            root.setCenter(row2);
            /*
            root.setBottom(pane);
            pane.getChildren().add(ta);
            */

            Image image = null;

            if (cards != null) {
                for (String card : cards) {
                    String file = "cards/" + card;
                    image = new Image(getClass().getClassLoader().getResource(file).toString(), true);
                    drawCards(box, image);
                }
            }

            if (!done) {
                // Draws the face-down top card of our pack of cards
                String file = "cards/b.gif";
                image = new Image(getClass().getClassLoader().getResource(file).toString(), true);
                drawCards(box, image);
            }

            sp.setContent(box);
            sp.setVbarPolicy(ScrollPane.ScrollBarPolicy.NEVER);
            scene.getStylesheets().add(CardTable.class.getResource("styling.css").toExternalForm());
            btnDraw.getStyleClass().add("btnDraw");
            btnCombine.getStyleClass().add("btnCombine");
            btnQuit.getStyleClass().add("btnQuit");
            stage.setScene(scene);
            stage.show();
        });
    }



    private void drawCards(HBox box, Image image) {
        ImageView iv;
        iv = new ImageView();
        // resizes the image to have width of 100 while preserving the ratio and using
        // higher quality filtering method; this ImageView is also cached to
        // improve performance
        iv.setImage(image);
        iv.setFitWidth(100);
        iv.setPreserveRatio(true);
        iv.setSmooth(true);
        iv.setCache(true);

        box.getChildren().add(iv);

    }
}
