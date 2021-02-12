import javax.swing.*;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.Random;

public class Task2 extends JFrame {
	
    JLabel textField;
    JButton runBtn;
    JButton staticButton;
    Random rnd = new Random(System.currentTimeMillis());
    JLabel label;


    public Task2() {
        SwingUtilities.invokeLater(() -> {
            setVisible(true);
            setResizable(false);
            Task2.this.setLocationRelativeTo(null);
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
        //textField = new JLabel("Поставите 8 на экзамене автоматом ?");
        textField = new JLabel("ВАм нравится БГУ ?");
        staticButton = createStaticButton("Да");
        runBtn = createRunButton("Нет");
        pane.setContentPane(panel);
        panel.setLayout(null);
        panel.add(textField);
        panel.add(staticButton);
        panel.add(runBtn);

        textField.setBounds(280,150,300,40);
        textField.setFont(textField.getFont().deriveFont(0, 20));
        staticButton.setBounds(280,210,75,40);
        staticButton.setFont(staticButton.getFont().deriveFont(0, 20));
        runBtn.setBounds(400,210,75,40);
        runBtn.setFont(staticButton.getFont().deriveFont(0, 20));

        return pane;
    }

    private JButton createRunButton(String name) {
        JButton btn = new JButton(name);
        btn.setSize(75, 40);
        btn.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseEntered(MouseEvent e) {
                btn.setLocation(Math.abs(rnd.nextInt() % 600) + 50, Math.abs(rnd.nextInt() % 300) + 50);
            }
        });
        return btn;
    }

    private JButton createStaticButton(String name) {
        JButton btn = new JButton(name);
        btn.addActionListener(e -> {
            JOptionPane.showMessageDialog(this, /*" СПАСИБО! "*/" Мы и не сомневались ", "", JOptionPane.PLAIN_MESSAGE);
        });
        btn.setSize(75, 40);
        return btn;
    }

}
