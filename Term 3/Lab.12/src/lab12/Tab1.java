package lab12;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Tab1 extends JPanel {

	private DefaultListModel leftListModel = new DefaultListModel();
	private DefaultListModel rightListModel = new DefaultListModel();

	private String[] array1 = { "Q", "W", "E", "R", "T", "Y", "U" };
	private String[] array2 = { "A", "S", "D", "F", "G", "H", "J", "H" };

	JList<String> leftList = new JList<>();
	JList<String> rightList = new JList<>();

	public Tab1() {
		setLayout(new BorderLayout());
		JPanel mainPanel = new JPanel(new BorderLayout());
		JPanel centralPanel = new JPanel(new BorderLayout());
		JButton toLeftListButton = new JButton(new ImageIcon("images/left.jpg"));
		JButton toRightListButton = new JButton(new ImageIcon("images/right.jpg"));

		leftListModel = createListModel(leftListModel, array1);
		rightListModel = createListModel(rightListModel, array2);

		leftList.setModel(leftListModel);
		leftList.setPreferredSize(new Dimension(150, 400));
		rightList.setModel(rightListModel);
		rightList.setPreferredSize(new Dimension(150, 400));

		toLeftListButton.setPreferredSize(new Dimension(100, 60));
		toRightListButton.setPreferredSize(new Dimension(100, 60));
		centralPanel.add(toRightListButton, BorderLayout.NORTH);
		centralPanel.add(toLeftListButton, BorderLayout.SOUTH);

		mainPanel.add(leftList, BorderLayout.WEST);
		mainPanel.add(rightList, BorderLayout.EAST);
		mainPanel.add(centralPanel, BorderLayout.CENTER);

		toLeftListButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent actionEvent) {
				moveLines(rightList.getSelectedIndices(), rightListModel, leftListModel);
			}
		});
		toRightListButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent actionEvent) {
				moveLines(leftList.getSelectedIndices(), leftListModel, rightListModel);
			}
		});

		this.add(mainPanel, BorderLayout.CENTER);
		setVisible(true);

	}

	private void moveLines(int[] indicies, DefaultListModel depart, DefaultListModel dest) {
		for (int i = 0; i < indicies.length; ++i) {
			dest.addElement(depart.elementAt(indicies[i]));
		}

		for (int i = indicies.length - 1; i >= 0; --i) {
			depart.remove(indicies[i]);
		}
	}

	private DefaultListModel createListModel(DefaultListModel listModel, String[] args) {
		listModel = new DefaultListModel();
		for (String el : args) {
			listModel.addElement(el);
		}
		return listModel;

	}
}