package lab8;

public class Person implements Comparable<Person> {// добавляем возможность сравнивать объекты User

	private String name;
	private Integer age;

	public Person(String name, int age) {
		this.name = name;
		this.age = age;
	}

	@Override
	public int compareTo(Person o) {

		// int result = this.age.compareTo(o.age);
		int result = this.name.compareTo(o.name);

		if (result == 0) {
			// result = this.name.compareTo(o.name);
			result = this.age.compareTo(o.age);
		}
		return result;
	}

	@Override
	public String toString() {
		return name + " " + age + "y.o";
	}
}