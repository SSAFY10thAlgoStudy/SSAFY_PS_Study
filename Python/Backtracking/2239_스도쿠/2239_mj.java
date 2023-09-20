import java.io.*;
import java.util.*;

public class Main {
	static int board[][] = new int[9][9];
	static List<int[]> blank = new LinkedList<int[]>();
	static int blankCnt;

	public static void main(String[] args) throws Exception {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

		for (int i = 0; i < 9; i++) {
			String[] t = in.readLine().split("");
			for (int j = 0; j < 9; j++) {
				board[i][j] = Integer.parseInt(t[j]);
				if (board[i][j] == 0)
					blank.add(new int[] { i, j });
			}
		}
		blankCnt = blank.size();

		Fill(0);

	}

	private static void Fill(int cnt) {
		if (cnt == blankCnt) {
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					System.out.print(board[i][j]);
				}
				System.out.println();
			}
			System.exit(0);
		}
		int[] tmp = blank.get(cnt);
		int i = tmp[0];
		int j = tmp[1];
		for (int f = 1; f <= 9; f++) {
			if (CheckRow(i, j, f) && CheckCol(i, j, f) && CheckSquare(i, j, f)) {
				board[i][j] = f;
				Fill(cnt + 1);
				board[i][j] = 0;
			}

		}
	}

	private static boolean CheckRow(int r, int c, int x) { // [r][c]와 같은 행에 x가 있는지 확인
		for (int i = 0; i < 9; i++) {
			if (i == c)
				continue;
			if (board[r][i] == x)
				return false;
		}
		return true;
	}

	private static boolean CheckCol(int r, int c, int x) { // [r][c]와 같은 열에 x가 있는지 확인
		for (int i = 0; i < 9; i++) {
			if (i == r)
				continue;
			if (board[i][c] == x)
				return false;
		}
		return true;
	}

	private static boolean CheckSquare(int r, int c, int x) { // [r][c]와 같은 사각형에 x가 있는지 확인
		int stdR = r / 3 * 3;
		int stdC = c / 3 * 3;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (i == stdR && j == stdC)
					continue;
				if (board[stdR + i][stdC + j] == x)
					return false;
			}
		}
		return true;
	}

}
