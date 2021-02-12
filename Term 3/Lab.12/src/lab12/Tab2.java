package lab12;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

public class Tab2 extends JPanel {
	private final int T = 5;
	private final int SIZE = 80;
	private String oldLabel;
	private Color oldColor;

	public Tab2() {

		MouseAdapter mouseAdapter = new MouseAdapter() {

			@Override
			public void mouseEntered(MouseEvent e) {
				oldColor = ((JButton) e.getSource()).getBackground();
				oldLabel = ((JButton) e.getSource()).getText();
				Color invertedColor = new Color(255 - oldColor.getRed(), 255 - oldColor.getGreen(),
						255 - oldColor.getBlue());
				((JButton) e.getSource()).setBackground(invertedColor);
				((JButton) e.getSource()).setForeground(invertedColor);
			}

			@Override
			public void mouseExited(MouseEvent e) {
				((JButton) e.getSource()).setBackground(oldColor);
				((JButton) e.getSource()).setForeground(Color.BLACK);
			}

			@Override
			public void mousePressed(MouseEvent e) {
				oldLabel = ((JButton) e.getSource()).getText();
				((JButton) e.getSource()).setText("Clicked!");
			}

			@Override
			public void mouseReleased(MouseEvent e) {
				((JButton) e.getSource()).setText(oldLabel);
				((JButton) e.getSource()).setForeground(Color.BLACK);
			}
		};

		JPanel panel = new JPanel();
		panel.setLayout(new GridLayout(T, T));

		int x = 0;
		for (int i = 0; i < T; ++i) {
			for (int j = 0; j < T; ++j) {
				JButton button = new JButton(Integer.toString(++x));

				int r = (int) Math.round(255 * Math.sin(x * Math.PI / T / T / 2));
				int g = 255 - (int) Math.round(255 * Math.sin(x * Math.PI / T / T));
				int b = (int) Math.round(255 * Math.cos(x * Math.PI / T / T - Math.PI / 2));
				Color color = new Color(r, g, b);

				button.setBackground(color);
				button.addMouseListener(mouseAdapter);
				button.setPreferredSize(new Dimension(SIZE,SIZE));
				panel.add(button);
			}
		}
		
		this.add(panel);
	}
}
