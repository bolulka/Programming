package lab12;

import javax.swing.*;
import java.awt.*;

public class Tab3 extends JPanel {
    public Tab3(){
        setLayout(new GridLayout(4,1));
        ButtonGroup radioGroup = new ButtonGroup();
        ImageIcon pic1 = new ImageIcon("images/1pic.jpg");
        ImageIcon pic2 = new ImageIcon("images/2pic.jpg");
        ImageIcon pic3 = new ImageIcon("images/3pic.jpg");
        ImageIcon pic4 = new ImageIcon("images/4pic.jpg");
        for(int i = 0; i < 4; i++){
            JRadioButton btn = new JRadioButton(pic1);
            btn.setPressedIcon(pic2);
            btn.setRolloverIcon(pic3);
            btn.setSelectedIcon(pic4);
            radioGroup.add(btn);
            add(btn);
        }
    }
}