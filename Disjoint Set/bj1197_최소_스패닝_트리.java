import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class bj1197_최소_스패닝_트리 {
	static int V, E;
	static int[] parents;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		V = Integer.parseInt(st.nextToken());
		E = Integer.parseInt(st.nextToken());
		parents = new int[V+1];
		for (int i = 0; i < V + 1; i++) {
			parents[i] = i;
		}
		PriorityQueue<int[]> pq = new PriorityQueue<>((a1, a2) -> {
		    if (a1[0] > a2[0]) {
		        return 1;
		    } else if (a1[0] < a2[0]) {
		        return -1; 
		    }
		    return 0; 
		});
		for (int i = 0; i < E; i++) {
			st = new StringTokenizer(br.readLine());
			int a = Integer.parseInt(st.nextToken());
			int b = Integer.parseInt(st.nextToken());
			int value = Integer.parseInt(st.nextToken());
			pq.add(new int[] {value, a, b});
		
		}
		
		int edge = 0;
		int answer = 0;
		while(!pq.isEmpty()) {
			int[] cur = pq.poll();
			int value = cur[0];
			int a = cur[1];
			int b = cur[2];
			if(edge == V-1) {
				break;
			}
			if(find(a) != find(b)) {
				union(a, b);
				answer += value;
				edge++;
			}
		}
		System.out.println(answer);
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