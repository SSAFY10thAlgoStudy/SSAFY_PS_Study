import java.util.Scanner;
public class Main {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		String N = sc.nextLine();
		int checking=0;
		for(int i =0;i<N.length();i++) {
			boolean ok = true;
			while(ok) {
				checking++;
				String check = String.valueOf(checking);
				for(int j =0;j<check.length();j++) {
					if(N.charAt(i) == check.charAt(j)) {
						ok = false;
						break;
					}
				}
			}
		}
		System.out.println(checking);
	}

}