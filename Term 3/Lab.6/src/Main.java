import java.util.StringTokenizer;

//".125.10.458khn.j.1j5.j45"
//"9852.853.k12.1h256.1jhf2"
public class Main {

	public static void main(String[] args) {
		System.out.println(args[0]);
		mainMethod(args[0]);
	}

	public static void mainMethod(String args) {
		StringTokenizer st = new StringTokenizer(args, ".");
		StringBuilder str = new StringBuilder();
		boolean checked = false;
		while (st.hasMoreTokens()) {
			StringBuilder builder = new StringBuilder(st.nextToken());
			int temp = 0;
			if (args.charAt(0) != '.' && !checked) {
				str.append(builder.substring(0, builder.length()) + ".");
				checked = true;
				builder = new StringBuilder(st.nextToken());
			}
			for (int i = 0; i < builder.length(); i++) {
				if (Character.isDigit(builder.charAt(i)))
					temp++;
				else {
					if (temp < 3) {
						if (!st.hasMoreTokens()) {
							str.append(builder.substring(0, builder.length()));
							break;
						} else
							str.append(builder.substring(0, builder.length()) + ".");
						break;
					} else {
						if (!st.hasMoreTokens()) {
							str.append(builder.substring(0, 2) + builder.substring(temp, builder.length()));
							break;
						} else
							str.append(builder.substring(0, 2) + builder.substring(temp, builder.length()) + ".");
						break;
					}
				}

				if (i == builder.length() - 1)
					str.append(builder.substring(0, 2) + ".");
			}

		}
		String answer;
		if (!checked)
			answer = "." + str.toString();
		else
			answer = str.toString();
		System.out.print(answer);
	}
}
