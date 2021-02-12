import javax.swing.*;
import java.awt.*;
import java.util.zip.DataFormatException;

public class EditJDialog extends JDialog {
	private JButton ok = new JButton("Ok");
	private JLabel labelName = new JLabel("  Surame:");
	private JLabel labelSubject1 = new JLabel("  MA:");
	private JLabel labelSubject2 = new JLabel("  HA:");
	private JLabel labelSubject3 = new JLabel("  DMiML:");
	private JLabel labelStudentID = new JLabel("  StudentID:");
	private JTextField inputName = new JTextField("", 5);
	private JTextField inputStudentID = new JTextField("", 5);
	private JTextField inputMark1 = new JTextField("mark", 5);
	private JTextField inputMark2 = new JTextField("mark", 5);
	private JTextField inputMark3 = new JTextField("mark", 5);
	private Student student;

	public EditJDialog(JFrame parent, String title, Student o) {
		super(parent, title, true);
		setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
		this.student = o;

		Container container = this.getContentPane();
		container.setLayout(new GridLayout(6, 2));

		container.add(labelName);
		inputName.setText(student.getSurname());
		container.add(inputName);

		container.add(labelStudentID);
		inputName.setText(student.getStudentID());
		container.add(inputStudentID);

		container.add(labelSubject1);
		container.add(inputMark1);

		container.add(labelSubject2);
		container.add(inputMark2);

		container.add(labelSubject3);
		container.add(inputMark3);

		createOkButton();
		container.add(ok);
		pack();
		setVisible(true);
	}

	private void createOkButton() {
		ok.addActionListener(e -> {
			try {
				if (inputName.getText().equals(""))
					throw new DataFormatException("Set name!");
				student.setSurname(inputName.getText());
				student.setStudentID(inputStudentID.getText());
				student.setProgress("MA", Integer.parseInt(inputMark1.getText()), "HA",
						Integer.parseInt(inputMark2.getText()), "DMiML", Integer.parseInt(inputMark3.getText()));
				setVisible(false);
			} catch (NumberFormatException err) {
				JOptionPane.showMessageDialog(this, err, "Error!", JOptionPane.PLAIN_MESSAGE);
			} catch (DataFormatException err) {
				JOptionPane.showMessageDialog(this, err.getMessage(), "Error!", JOptionPane.PLAIN_MESSAGE);
			}
		});
	}

}
