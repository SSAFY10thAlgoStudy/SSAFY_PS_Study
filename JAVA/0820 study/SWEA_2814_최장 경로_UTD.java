import java.io.*;
import java.util.*;
 
public class Solution {
	static int groupNum;
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder sb = new StringBuilder();
        StringTokenizer st;
 
        int T = Integer.parseInt(br.readLine());
        for (int i = 0; i < T; i++) {
        	st = new StringTokenizer(br.readLine());
            int N = Integer.parseInt(st.nextToken());
            int M = Integer.parseInt(st.nextToken());
            int[][] people = new int[N + 1][N + 1];
            groupNum = 0;
             
            for (int j = 0; j < M; j++) {
            	st = new StringTokenizer(br.readLine());
                int a = Integer.parseInt(st.nextToken());
                int b = Integer.parseInt(st.nextToken());
                people[a][b] = 1;
                people[b][a] = 1;
            }
             
            for (int m = 1; m <= N; m++) {
                // 각 정점을 시작으로 다시 방문체크하면서 경로 길이를 찾으므로 visited을 for문 돌릴 때마다 선언
           		boolean[] visited = new boolean[N + 1];
                visited[0] = true;
                visited[m] = true;
                dfs(people, visited, 1, m);

            }
            System.out.println("#" + (i + 1) + " " + groupNum);
        }
    }
     
    public static void dfs(int[][] people, boolean[] visited, int depth, int index){
        // 가장 긴 경로를 구하기 위해서 max 메서드 사용
    	groupNum = Math.max(groupNum, depth);
        for (int k = 1; k < people.length; k++) {
            if (people[index][k] == 1 && !visited[k]) {

                // index 정점과 연결된 다른 정점들을 각각 선택하냐 안하냐에 따라 경로 길이가 달라지기 때문에
                // 선택하냐 안하냐 2가지 경우를 따져야 한다.
                visited[k] = true;
                dfs(people, visited, depth +1, k);
                visited[k] = false;
            }
        }
    }
     
}