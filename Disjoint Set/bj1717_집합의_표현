import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class bj1717_집합의_표현 {
	static int N, M;
	static int[] parents;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		StringBuilder sb = new StringBuilder();
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		parents = new int[N + 1];
		for (int i = 0; i < N + 1; i++) {
			parents[i] = i;
		}
		for (int i = 0; i < M; i++) {
			st = new StringTokenizer(br.readLine());
			int cmd = Integer.parseInt(st.nextToken());
			int a = Integer.parseInt(st.nextToken());
			int b = Integer.parseInt(st.nextToken());
			if (cmd == 0) {
				union(a, b);
			} else {
				if (find(a) != find(b)) {
					sb.append("NO").append("\n");
				} else {
					sb.append("YES").append("\n");
				}
			}
		}
		System.out.println(sb);
	}

	private static int find(int a) {
		if (parents[a] != a) {
			parents[a] = find(parents[a]);
		}
		return parents[a];
	}

	private static void union(int x, int y) {
		int fx = find(x);
		int fy = find(y);
		if (fx < fy) {
			parents[fy] = fx;
		} else {
			parents[fx] = fy;
		}

	}
}
