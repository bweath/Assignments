/**
 * Console to redirect standard input and output - taken from stackoverflow   https://stackoverflow.com/questions/13841884/redirecting-system-out-to-a-textarea-in-javafx?utm_medium=organic&utm_source=google_rich_qa&utm_campaign=google_rich_qa
 * @author Dreen
 * @version 1.0
 */


package uk.ac.aber.dcs.cs12320.cards.gui.javafx;
import java.io.IOException;
import java.io.OutputStream;
import javafx.scene.control.TextArea;


public class Console extends OutputStream {

        private TextArea    output;

        public Console(TextArea ta)
        {
            this.output = ta;
        }

        @Override
        public void write(int i) throws IOException
        {
            output.appendText(String.valueOf((char) i));
        }
}
