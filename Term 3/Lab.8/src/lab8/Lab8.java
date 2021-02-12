package lab8;

public class Lab8 {
	public static void main(String[] args) {

		Tree<Integer> tree1 = new Tree<>();
		tree1.add(15);
		tree1.add(8);
		tree1.add(3);
		tree1.add(10);
		tree1.add(24);
		tree1.add(48);
		tree1.add(35);
		tree1.add(21);
		tree1.add(1);
		tree1.add(17);
		tree1.add(0);
		tree1.add(4);
		tree1.add(14);
		tree1.goLeftRootRight();
		tree1.goRootLeftRight();
		tree1.gotLeftRightRoot();
		tree1.search(5);
		tree1.search(17);

		Tree<Person> tree2 = new Tree<>();
		Person p1 = new Person("James", 12);
		Person p2 = new Person("Jaremy", 17);
		Person p3 = new Person("Ann", 12);
		Person p4 = new Person("Paul", 25);
		Person p5 = new Person("Torry", 18);
		Person p6 = new Person("Kate", 15);
		Person p7 = new Person("Kate", 21);
		Person p8 = new Person("Julia", 19);

		tree2.add(p1);
		tree2.add(p2);
		tree2.add(p3);
		tree2.add(p4);
		tree2.add(p5);
		tree2.add(p6);
		tree2.add(p7);
		tree2.goLeftRootRight();
		tree2.goRootLeftRight();
		tree2.gotLeftRightRoot();
		tree2.search(p8);
		tree2.search(p4);

	}
}
