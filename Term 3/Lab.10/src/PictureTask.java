import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.Random;

public class PictureTask extends JFrame {
    JLabel textField;
    JButton runBtn;
    JButton staticButton;
    Random rnd = new Random(System.currentTimeMillis());
    JLabel label;


    public PictureTask() {
        SwingUtilities.invokeLater(() -> {
            setVisible(true);
            setResizable(false);
            PictureTask.this.setLocationRelativeTo(null);
        });
    }


    @Override
    protected JRootPane createRootPane() {
        JPanel panel = new JPanel();
        JRootPane pane = new JRootPane();
        setSize(700, 500);
        addComponentListener(new ComponentAdapter() {
            @Override
            public void componentHidden(ComponentEvent e) {
                System.exit(0);
            }
        });
        textField = new JLabel("Вы любите БГУ? ");
        textField.setFont(textField.getFont().deriveFont(3, 25));
        textField.setForeground(Color.ORANGE);
        BufferedImage image = null;
        BufferedImage mainImage = null;
        try {
            image = ImageIO.read(new File("E:\\eclipse-workspace\\Lab.10\\bulatov1love.jpg"));
            mainImage = ImageIO.read(new File("E:\\eclipse-workspace\\Lab.10\\unnamed.jpg"));
        } catch (IOException ex) {
            ex.printStackTrace();
        }
        label = new JLabel();
        label.setSize(300, 300);
        Image dimg = image.getScaledInstance(label.getWidth(), label.getHeight(), Image.SCALE_SMOOTH);
        ImageIcon imageIcon = new ImageIcon(dimg);
        label.setIcon(imageIcon);
        Image dimg2 = mainImage.getScaledInstance(700, 500, Image.SCALE_SMOOTH);
        JLabel lmainImage = new JLabel(new ImageIcon(dimg2));
        lmainImage.setSize(700, 500);
        textField.setSize(300, 30);
        staticButton = createStaticButton("yes", "");
        runBtn = createRunButton("no");
        pane.setContentPane(panel);
        panel.setLayout(null);
        panel.add(textField);
        panel.add(staticButton);
        panel.add(runBtn);
        panel.add(lmainImage);
        textField.setLocation(200, 100);
        staticButton.setLocation(200, 170);
        runBtn.setLocation(360, 170);

        return pane;
    }

    private JButton createRunButton(String name) {
        JButton btn = new JButton(name);
        btn.setSize(80, 30);
        btn.setBackground(Color.orange);
        btn.setForeground(Color.WHITE);
        btn.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseEntered(MouseEvent e) {
                btn.setLocation(Math.abs(rnd.nextInt() % 600) + 50, Math.abs(rnd.nextInt() % 300) + 50);
            }
        });
        return btn;
    }

    private JButton createStaticButton(String name, String message) {
        JButton btn = new JButton(name);
        btn.addActionListener(e -> {
            JOptionPane.showMessageDialog(this, label, "", JOptionPane.PLAIN_MESSAGE);
        });
        btn.setSize(80, 30);
        btn.setBackground(Color.orange);
        btn.setForeground(Color.WHITE);
        return btn;
    }

}