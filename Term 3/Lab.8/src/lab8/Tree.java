package lab8;

public class Tree<T extends Comparable> {
	private Node<T> root;

	public Tree() {
		this.root = null;
	}

	public class Node<T extends Comparable> {
		private T value;
		private Node<T> left, right;

		public Node() {
			this.value = null;
			this.left = null;
			this.right = null;
		}

		public Node(T value) {
			this.value = value;
			this.left = null;
			this.right = null;
		}
	}

	public void add(T value) {
		root = add(root, value);
		System.out.println(value + " successfully added");
	}

	private Node add(Node<T> node, T value) throws IllegalArgumentException {
		if (node == null)
			node = new Node<>(value);
		else if (value.compareTo(node.value) < 0)
			node.left = add(node.left, value);
		else if (value.compareTo(node.value) > 0)
			node.right = add(node.right, value);
		else
			System.out.println("Your tree already has had this value!");
		return node;
	}

	public boolean search(T value) {
		return search(root, value, true) != null;
	}

	private Node search(Node<T> node, T value, Boolean print) {
		if (value.compareTo(node.value) < 0)
			if (node.left != null)
				if (value.compareTo(node.left.value) == 0)
					return node;
				else
					return search(node.left, value, print);
			else {
				System.out.println("There is no " + value + " in tree");
				return null;
			}
		else if (value.compareTo(node.value) > 0)
			if (node.right != null)
				if (!print && value.compareTo(node.right.value) == 0)
					return node;
				else
					return search(node.right, value, print);
			else {
				System.out.println("There is no " + value + " in tree");
				return null;
			}
		else {
			if (print) {
				System.out.println(value + " was found");
			}
			return node;
		}

	}

	public void goLeftRootRight() {
		System.out.print("LeftRootRight: ");
		goLeftRootRight(root);
		System.out.println();
	}

	private void goLeftRootRight(Node<T> node) {
		if (node != null) {
			goLeftRootRight(node.left);
			System.out.print(node.value + " ");
			goLeftRootRight(node.right);
		}
	}

	public void goRootLeftRight() {
		System.out.print("RootLeftRight: ");
		goRootLeftRight(root);
		System.out.println();
	}

	private void goRootLeftRight(Node<T> node) {
		if (node != null) {
			System.out.print(node.value + " ");
			goRootLeftRight(node.left);
			goRootLeftRight(node.right);
		}
	}

	public void gotLeftRightRoot() {
		System.out.print("LeftRightRoot: ");
		goLeftRightRoot(root);
		System.out.println();
	}

	private void goLeftRightRoot(Node<T> node) {
		if (node != null) {
			goLeftRightRoot(node.left);
			goLeftRightRoot(node.right);
			System.out.print(node.value + " ");
		}
	}

}