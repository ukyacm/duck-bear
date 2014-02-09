import java.util.Random;

public class ExampleBot extends GoBot {
	public ExampleBot() {}
	
	@Override
	public Move onMyTurn(int pnum, int[][] boardState) {
		Random random = new Random();
		
		int x, y;
		do {
			x = random.nextInt(9);
			y = random.nextInt(9);
		} while(boardState[x][y] != 0);
		
		return new Move(x,y,0);
	}
	
	public static void main(String[] args) {
		ExampleBot bot = new ExampleBot();
		bot.start();
	}
}
