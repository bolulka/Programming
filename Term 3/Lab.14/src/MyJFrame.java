import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.w3c.dom.Document;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import java.awt.*;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Collection;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Scanner;
import java.util.TreeSet;

public class MyJFrame extends JFrame {

	private TreeSet<Student> studentSet;
	private DefaultListModel<String> listModel;
	private DefaultListModel<String> honourListModel;
	private JList<String> list;
	private JList<String> honourList;
	private JFileChooser fileChooser;

	public MyJFrame() {
		SwingUtilities.invokeLater(() -> {
			setVisible(true);
			setSize(700, 500);
			MyJFrame.this.setLocationRelativeTo(null);
			addComponentListener(new ComponentAdapter() {
				@Override
				public void componentHidden(ComponentEvent e) {
					System.exit(0);
				}
			});
		});
	}

	@Override
	public JRootPane createRootPane() {
		JRootPane pane = new JRootPane();
		JPanel panel = new JPanel();
		JPanel centralPanel = new JPanel();
		pane.setContentPane(panel);
		centralPanel.setLayout(new BorderLayout());
		panel.setLayout(new BorderLayout());
		listModel = new DefaultListModel<>();
		honourListModel = new DefaultListModel<>();
		list = new JList<>(listModel);
		honourList = new JList<>(honourListModel);
		JPanel buttonPanel = new JPanel();
		studentSet = new TreeSet<>(new MyComparator());
		fileChooser = new JFileChooser("E:\\EclipseWorkspace\\Lab13");
		JButton open = createOpenButton();
		buttonPanel.add(open);
		JButton edit = createEditButton();
		buttonPanel.add(edit);
		JButton addBtn = createAddButton();
		buttonPanel.add(addBtn);
		JButton saveToXML = createSaveToXmlButton();
		buttonPanel.add(saveToXML);
		JButton openTheXML = createOpenXMLButton();
		buttonPanel.add(openTheXML);
		panel.add(buttonPanel, BorderLayout.SOUTH);
		centralPanel.add(list, BorderLayout.NORTH);
		centralPanel.add(honourList, BorderLayout.SOUTH);
		panel.add(centralPanel);
		return pane;
	}

	private JButton createAddButton() {
		JButton add = new JButton("Add");
		add.addActionListener(e -> {
			Student st = new Student();
			new EditJDialog(this, "Add", st);
			studentSet.add(st);
			show(studentSet);
			showHonourStudents(studentSet);
		});
		return add;
	}

	private JButton createEditButton() {
		JButton edit = new JButton("Edit");
		edit.addActionListener(e -> {
			if (list.getSelectedIndex() >= 0) {
				Iterator<Student> iter = studentSet.iterator();
				for (int i = 0; i < list.getSelectedIndex(); i++) {
					iter.next();
				}
				new EditJDialog(this, "edit", iter.next());
				TreeSet<Student> temp = new TreeSet<>(new MyComparator());
				temp.addAll(studentSet);
				studentSet = new TreeSet<>(temp);
				show(studentSet);
				showHonourStudents(studentSet);
			}
		});
		return edit;
	}

	private JButton createOpenButton() {
		JButton open = new JButton("Open");
		open.addActionListener(e -> {
			fileChooser.setDialogTitle("�������� �����");
			fileChooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
			FileNameExtensionFilter filter = new FileNameExtensionFilter("Text files", "txt");
			fileChooser.setFileFilter(filter);
			int result = fileChooser.showOpenDialog(this);
			if (result == JFileChooser.APPROVE_OPTION)
				read(fileChooser.getSelectedFile());
			show(studentSet);
			showHonourStudents(studentSet);
		});
		return open;
	}

	private JButton createOpenXMLButton() {
		JButton readXML = new JButton("OpenXML");
		readXML.addActionListener(e -> {
			try {
				fileChooser.setDialogTitle("�������� �����");
				fileChooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
				FileNameExtensionFilter filter = new FileNameExtensionFilter("XML files", "xml");
				fileChooser.setFileFilter(filter);
				int result = fileChooser.showOpenDialog(this);
				if (result == JFileChooser.APPROVE_OPTION) {
					DocumentBuilderFactory students = DocumentBuilderFactory.newInstance();
					DocumentBuilder builder = students.newDocumentBuilder();
					Document document = builder.parse(fileChooser.getSelectedFile());
					NodeList studentElements = document.getDocumentElement().getElementsByTagName("student");
					studentSet = new TreeSet<>(new MyComparator());
					for (int i = 0; i < studentElements.getLength(); i++) {
						Node product = studentElements.item(i);
						NamedNodeMap attributes = product.getAttributes();
						studentSet.add(new Student(attributes.getNamedItem("surname").getNodeValue(),
								attributes.getNamedItem("studentID").getNodeValue(),
								Integer.parseInt(attributes.getNamedItem("mark1").getNodeValue()),
								Integer.parseInt(attributes.getNamedItem("mark2").getNodeValue()),
								Integer.parseInt(attributes.getNamedItem("mark3").getNodeValue())));
					}
					show(studentSet);
					showHonourStudents(studentSet);
				}
			} catch (SAXException | ParserConfigurationException | IOException ex) {
				JOptionPane.showMessageDialog(this, "Problems with file", "Error!", JOptionPane.PLAIN_MESSAGE);
			}
		});
		return readXML;
	}

	private JButton createSaveToXmlButton() {
		JButton save = new JButton("SaveXML");
		save.addActionListener(e -> {
			saveToXml();
			JOptionPane.showMessageDialog(this, "Done", "", JOptionPane.PLAIN_MESSAGE);
		});
		return save;
	}

	private void show(Collection<Student> a) {
		if (a != null) {
			listModel.clear();
			Iterator<Student> iter = studentSet.iterator();
			while (iter.hasNext()) {
				listModel.addElement(iter.next().toString());
			}
		} else
			JOptionPane.showMessageDialog(this, "There are no elements!", "Error!", JOptionPane.PLAIN_MESSAGE);
	}

	private void showHonourStudents(Collection<Student> a) {
		if (a != null) {
			honourListModel.clear();
			Iterator<Student> iter = studentSet.iterator();
			while (iter.hasNext()) {
				Student tempSt = iter.next();
				Map<String, Integer> temp = new HashMap<String, Integer>(tempSt.getProgress());
				if (temp.get("MA") == 9 || temp.get("MA") == 10)
					if (temp.get("HA") == 9 || temp.get("HA") == 10)
						if (temp.get("DMiML") == 9 || temp.get("DMiML") == 10)

							honourListModel.addElement(tempSt.toString());

			}
		} else
			JOptionPane.showMessageDialog(this, "There are no elements!", "Error!", JOptionPane.PLAIN_MESSAGE);
	}

	private void read(File file) {
		try (Scanner sc = new Scanner(file)) {
			studentSet = new TreeSet<>(new MyComparator());
			while (sc.hasNext())
				studentSet.add(new Student(sc.next(), sc.next(), sc.nextInt(), sc.nextInt(), sc.nextInt()));
		} catch (FileNotFoundException err) {
			JOptionPane.showMessageDialog(this, err, "Error!", JOptionPane.PLAIN_MESSAGE);
		}
	}

	private void saveToXml() {
		try (FileWriter wr = new FileWriter("src/xmlFileNameSave.xml")) {
			wr.write("<?xml version=\"1.0\"?>" + "\n");
			wr.write("<students>" + "\n");
			Iterator<Student> iter = studentSet.iterator();
			while (iter.hasNext())
				wr.write(iter.next().toXML() + "\n");
			wr.write("</students>");
		} catch (IOException ignored) {
			JOptionPane.showMessageDialog(this, "Problems with file", "Error!", JOptionPane.PLAIN_MESSAGE);
		}
	}
}
