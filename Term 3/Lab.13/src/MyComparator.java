import java.util.Comparator;

public class MyComparator implements Comparator<Student> {
	@Override
	public int compare(Student o1, Student o2) {
		return o1.getSurname().compareTo(o2.getSurname()) == 0 ? o1.getStudentID().compareTo(o2.getStudentID()): 
				o1.getSurname().compareTo(o2.getSurname()) ;
	}
}
