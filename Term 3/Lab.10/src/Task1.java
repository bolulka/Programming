import javax.swing.*;
import java.awt.event.*;

public class Task1 extends JFrame {

	JButton button;
	JLabel showStatus;

	public Task1() {

		SwingUtilities.invokeLater(() -> {
			setVisible(true);
			setResizable(false);
			Task1.this.setLocationRelativeTo(null);
			addComponentListener(new ComponentAdapter() {
				@Override
				public void componentHidden(ComponentEvent e) {
					System.exit(0);
				}
			});
		});
	}

	@Override
	protected JRootPane createRootPane() {
		JPanel panel = new JPanel();
		JRootPane pane = new JRootPane();
		setSize(700, 500);

		showStatus = new JLabel();
		showStatus.setSize(100, 20);
		pane.setContentPane(panel);
		panel.setLayout(null);
		button = createButton();
		panel.add(button);
		panel.add(showStatus);

		showStatus.setLocation(0, 440);
		button.setLocation(300, 200);

		button.addMouseMotionListener(new MouseAdapter() {
			@Override
			public void mouseMoved(MouseEvent e) {
				int x = button.getX() + e.getX();
				int y = button.getY() + e.getY();
				showStatus.setText("X: " + x + " Y:" + y);
			}

			@Override
			public void mouseDragged(MouseEvent e) {
				int x = button.getX() + e.getX();
				int y = button.getY() + e.getY();
				if (e.isControlDown()) {
					button.setLocation(x - 50, y- 25);
				}
				showStatus.setText("X: " + x + " Y: " + y);
			}
		});

		addMouseMotionListener(new MouseAdapter() {
			@Override
			public void mouseMoved(MouseEvent e) {
				showStatus.setText("X: " + e.getX() + " Y:" + e.getY());
			}

			@Override
			public void mouseDragged(MouseEvent e) {
				showStatus.setText("Õ: " + e.getX() + " Y: " + e.getY());
			}
		});

		addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				button.setLocation(e.getX() - 50, e.getY() - 50);
			}

		});

		return pane;
	}

	private JButton createButton() {
		JButton btn = new JButton("Welcome");

		btn.setSize(100, 50);
		btn.setFont(btn.getFont().deriveFont(2, 15));
		btn.addKeyListener(new KeyAdapter() {
			@Override
			public void keyTyped(KeyEvent e) {
				if (e.getKeyChar() == KeyEvent.VK_BACK_SPACE) {
					if (btn.getText().length() > 0)
						btn.setText(btn.getText().substring(0, btn.getText().length() - 1));
				} else
					btn.setText(btn.getText() + Character.toString(e.getKeyChar()));
			}

		});
		return btn;
	}

}