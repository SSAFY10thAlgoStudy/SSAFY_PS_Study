import java.util.*;
import java.io.*;

public class Main {

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder sb = new StringBuilder();
		StringTokenizer st;

		int N;
		int[][] arr;

		N = Integer.parseInt(br.readLine());
		arr = new int[N][N];

		for (int i = 0; i < N; i++) {
			st = new StringTokenizer(br.readLine());
			for (int j = 0; j < N; j++) {
				arr[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		////////////////////////////////////////////////////////

		int answer = 0;

		for (int height = 1; height <= 100; height++) {

			boolean[][] visited = new boolean[N][N];
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					if (arr[i][j] <= height)
						visited[i][j] = true;
				}
			}

			int count = 0;

			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					if (!visited[i][j]) {
						dfs(arr, visited, i, j);
						count++;
					}
				}
			}

			answer = Math.max(answer, count);

		}

		System.out.println(answer);

	}

	public static void dfs(int[][] arr, boolean[][] visited, int i, int j) {
		visited[i][j] = true;
		if (i > 0) {
			if (!visited[i - 1][j])
				dfs(arr, visited, i - 1, j);
		}
		if (i < arr.length - 1) {
			if (!visited[i+1][j])
				dfs(arr,visited,i+1,j);
		}
		if(j>0) {
			if(!visited[i][j-1])
				dfs(arr,visited,i,j-1);
		}
		if(j<arr.length-1) {
			if(!visited[i][j+1])
				dfs(arr,visited,i,j+1);
		}
	}

}
