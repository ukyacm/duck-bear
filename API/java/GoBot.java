import java.io.IOException;
import java.util.Scanner;

public abstract class GoBot {
	
	public class Move {
		public int x, y, p;
		Move(int x, int y, int p) {
			this.x = x;
			this.y = y;
			this.p = p;
		}
	}
	
	public GoBot() {}
	
	private int pnum;
	private final int BSIZE = 9;
	private Scanner stdin = new Scanner(System.in);
	
	public void start() {
		try {
			sendMessage("HI!");
			String[] msg = getMessage().split(" ");
			if(msg[0].equals("INITIALIZE")) {
				pnum = Integer.parseInt(msg[1]);
			} else {
				throw new IOException("Bad msg, expected init. Got: \"" + msg[0] + "\"");
			}
			
			sendMessage("READY!");
			
			while(true) {
				msg = getMessage().split(" ");
				if(msg[0].equals("REQUEST_MOVE")) {
					int[][] boardState = parseBoardState(msg[1]);
					Move mv = onMyTurn(pnum,boardState);
					String rmsg = String.format("RESPONSE_MOVE %s %s %s", mv.x, mv.y, mv.p);
					sendMessage(rmsg);		
				} else if(msg[0].equals("ENDGAME")) {
					System.exit(0);
				} else {
					throw new IOException("bad msg, got \"" + msg[0] + "\"");
				}
			}
			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	private int[][] parseBoardState(String data) throws IOException {
		if(data.length() != BSIZE * BSIZE)
			throw new IOException("incomplete board state array data");
		
		int[][] grid = new int[BSIZE][BSIZE];
		int ptr = 0;
		for(int i = 0; i < BSIZE; i++) {
			for(int j = 0; j < BSIZE; j++) {
				String tmp = String.valueOf(data.charAt(ptr));
				grid[i][j] = Integer.parseInt(tmp);
				ptr++;
			}
		}
		return grid;
	}
	
	private void sendMessage(String msg) throws IOException {
		System.out.println(msg);
	}
	
	private String getMessage() {
		return stdin.nextLine();
	}
	
	// override this!
	public Move onMyTurn(int pnum, int[][] boardState) {
		return null;
	}
}
