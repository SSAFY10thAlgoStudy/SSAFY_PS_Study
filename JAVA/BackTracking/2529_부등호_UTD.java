//다른 사람 풀이 공부
//임시

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class Main {
	
	private static int n;
	private static boolean[] visit = new boolean[10];
	private static String[] sign;
	private static ArrayList<String> result = new ArrayList<String>();
	
	public static void main(String[] args) {
		
		Scanner sc = new Scanner(System.in);
		
		n = sc.nextInt();
		
		sign = new String[n];
		for (int i=0; i<n; i++) {
			sign[i] = sc.next();
		}
		
		for (int i=0; i<10; i++) {
			Arrays.fill(visit, false); //false로 초기화
			visit[i] = true; //방문처리
			cycle(i, 0, 0, i+""); //시작수, sign배열 index, 탐색 count, 출력할 문자
		}
		
		System.out.println(result.get(result.size()-1));
		System.out.println(result.get(0));
		
	}

	private static void cycle(int start, int idx, int cnt, String str) {
		
		if (cnt == n) {
			//result에 더하기
			result.add(str);
		} else {
			for (int i=0; i<10; i++) {
				if (!visit[i]) { //방문 안했을 때
					String temp = str + i; //문자생성
					if (sign[idx].equals("<")) {
						//"<".equals(sign[indx]) 가 null넘어감
						if (start > i) {
							//앞수가 뒤보다 크면 넘김
							continue;
						}
						
						visit[i] = true; //방문처리
						cycle(i, idx+1, cnt+1, temp); //재귀
						visit[i] = false; //미방문처리
						
					} else if (sign[idx].equals(">")) {
						if (start < i) {
							//앞수가 뒤보다 작으면 넘김
							continue;
						}
						
						visit[i] = true; //방문처리
						cycle(i, idx+1, cnt+1, temp); //재귀
						visit[i] = false; //미방문처리
					}
				}
			}
		}
		
	}

		

}