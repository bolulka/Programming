package lab12;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.awt.event.KeyEvent;

public class MyFrame extends JFrame {
	JTabbedPane tabbedPane;

	public MyFrame() {
		SwingUtilities.invokeLater(() -> {
			setVisible(true);
			setSize(700, 500);
			MyFrame.this.setLocationRelativeTo(null);
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
		JRootPane pane = new JRootPane();
		JPanel panel = new JPanel();
		pane.setContentPane(panel);
		tabbedPane = new JTabbedPane();
		tabbedPane.addTab("Tab1", new Tab1());
		tabbedPane.addTab("Tab2", new Tab2());
		tabbedPane.addTab("Tab3", new Tab3());

		panel.add(tabbedPane);
		return pane;
	}
}