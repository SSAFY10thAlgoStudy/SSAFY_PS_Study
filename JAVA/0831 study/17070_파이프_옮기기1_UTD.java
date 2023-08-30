import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {
    public static int n;
    public static int[][] map;
    public static int[][] count;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;
        n = Integer.parseInt(br.readLine());
        map = new int[n][n];
        count = new int[n][n];
        
        for (int i=0; i<n; i++) { // for문을 통해서 map에 입력값 받기
            st = new StringTokenizer(br.readLine());
            for (int j=0; j<n; j++)
                map[i][j] = Integer.parseInt(st.nextToken());
        }

        dfs(0,1,0); // 파이프는 가로 방향으로 돌리는 것부터 시작하기
        System.out.println(count[n-1][n-1]); // 가장 마지막 인덱스에 count 되어 있으므로 마지막 인덱스 출력
    }

    // rotate 가로:0, 대각선:1, 세로:2
    public static void dfs(int r, int c, int rotate) {
        if (r>=n || c>=n || map[r][c]==1) return; // 벽을 만나거나 배열 범위를 벗어나면 return
        
        if (rotate==0) { // 가로방향이라면 2가지 수행 : 가로, 대각선
            dfs(r,c+1,0); // 
            dfs(r+1,c+1,1);
        } else if (rotate==1) { // 대각선이라면 3가지 수행 : 가로, 대각선, 세로
            if (map[r-1][c]==1 || map[r][c-1]==1) return; //벽이 있다면 return
            dfs(r,c+1,0); 
            dfs(r+1,c+1,1);
            dfs(r+1,c,2);
        } else { // 나머지 세로 방향이라면: 대각선, 세로 수행
            dfs(r+1,c+1,1);
            dfs(r+1,c,2);
        }
        count[r][c]++; // return이 되지 않고 이동에 성공하면 +1 해줌
    }
}