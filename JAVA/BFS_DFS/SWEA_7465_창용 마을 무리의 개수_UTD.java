import java.util.Scanner;
import java.util.Stack;

public class Solution {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int T = scanner.nextInt();
        for (int i = 0; i < T; i++) {

            // 입력값 받기
            int N = scanner.nextInt();
            int M = scanner.nextInt();

            // 인덱스와 사람 번호 맞추기 위해서 N+1로 만듦
            int[][] people = new int[N + 1][N + 1];
            int groupNum = 0;
            boolean[] visited = new boolean[N + 1];
            visited[0] = true;
            
            for (int j = 0; j < M; j++) {
                int a = scanner.nextInt();
                int b = scanner.nextInt();
                
                // 무방향 그래프이므로 서로 1로 체크
                people[a][b] = 1;
                people[b][a] = 1;
            }
            
            for (int m = 1; m <= N; m++) {

                // m번 사람 방문 표시 안했으면 
				if(!visited[m]) {

                    // m번 사람을 시작으로 무리를 이루기 때문에 groupNum++ 해줌
                    groupNum++;
                    visited[m] = true;

                    // 방문한 사람 번호를 넣어서 dfs 돌림
                    dfs(people, visited, m);
             	}	
        	}
       		System.out.println("#" + (i + 1) + " " + groupNum);
    	}
    }
    
    public static void dfs(int[][] people, boolean[] visited, int index){

        // 방문한 사람 번호를 기준으로 간선 연결된 사람 dfs 돌리기
        for (int k = 1; k < people.length; k++) {
            // 방문한 곳을 제외하고 방문하지 않은 사람 번호로 찾아보기
            // 동시에 index 번호인 사람과 연결된 사람이어야 함
            if (people[index][k] == 1 && !visited[k]) {
                visited[k] = true;
                dfs(people, visited, k);
            }
        }
    }
    
}