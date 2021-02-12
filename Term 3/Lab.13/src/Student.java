import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Objects;

 //Map<String, Integer>{};

public class Student {
	private String surname;
	private Map<String, Integer> progress = new HashMap<>();
	private String studentID;

	public Student() {}
	
	public Student(String surname, String studentID, int mark1, int mark2, int mark3) {
		this.surname = surname;
		this.studentID = studentID;
		Map<String, Integer> temp = new HashMap<>();
		temp.put("MA", mark1);
		temp.put("HA", mark2);
		temp.put("DMiML", mark3);
		this.progress = temp;
	}

	public String getSurname() {
		return surname;
	}

	public void setSurname(String surname) {
		this.surname = surname;
	}

	public Map<String, Integer> getProgress() {
		return progress;
	}

	@SuppressWarnings("null")
	public void setProgress(String subject1, int mark1 , String subject2, int mark2, String subject3, int mark3) {
		Map<String, Integer> temp = new HashMap<>();
		temp.put(subject1, mark1);
		temp.put(subject2, mark2);
		temp.put(subject3, mark3);
		this.progress = temp;
	}

	public String getStudentID() {
		return studentID;
	}

	public void setStudentID(String studentID) {
		this.studentID = studentID;
	}

	@Override
	public boolean equals(Object o) {
		if (this == o)
			return true;
		if (o == null || getClass() != o.getClass())
			return false;
		Student student = (Student) o;
		return Objects.equals(studentID, student.studentID) && Objects.equals(surname, student.surname);
	}

	@Override
	public int hashCode() {
		return Objects.hash(studentID, surname, progress);
	}

	@Override
	public String toString() {
		return "surname='" + surname + '\'' + ",student ID='" + studentID + '\'' + ",MA mark: " + progress.get("MA")
				+ '\'' + ",HA mark: " + progress.get("HA") + '\'' + ",DMiML mark: " + progress.get("DMiML") + '\'';
	}

}