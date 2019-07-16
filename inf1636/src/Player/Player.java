package Player;

import javax.swing.JLabel;

/**
 * 
 * Player holds all info related to the players, such as money, is in prison or
 * is already out of the game.
 *
 */
public class Player {
	private float money = 2458;
	private boolean inPrison = false;
	private boolean isOut = false;
	private boolean prisonPass = false;
	private int turnsInPrison = 0;
	private int x;
	private int y;
	private int index;

	public Player() {
	}

	/**
	 * Money creates a new JLabel with the players money to be shown on screen.
	 * 
	 * @param players      Players array.
	 * @param playerNumber Number of the desired player to be shown on screen.
	 * @return Money JLabel.
	 */
	public static JLabel Money(Player[] players, int playerNumber) {
		float money = players[playerNumber].getMoney();
		String moneyString = Float.toString(money);
		String text = String.format("Dinheiro: $ %s", moneyString);

		return new JLabel(text);
	}
	
	/**
	 * getMoney gets the amount of money a player has.
	 * 
	 * @return returns the amount of money a player has.
	 */
	public float getMoney() {
		return this.money;
	}
	
	/**
	 * setMoney sets a new money amount for the current player.
	 * 
	 * @param newSum	New sum of money to be set.
	 */
	public void setMoney(float newSum) {
		this.money = newSum;
	}
	
	/**
	 * inPrison returns the current player prison situation.
	 * 
	 * @return	True if player is in prison or false otherwise.
	 */
	public boolean inPrison() {
		return this.inPrison;
	}
	
	/**
	 * isOut returns if a player is out of the game or not.
	 * 
	 * @return	True if the player is out of the game or false otherwise.
	 */
	public boolean isOut() {
		return this.isOut;
	}
	
	/**
	 * hasPrisonPass verifies if the player has a "get out of prison" pass.
	 * 
	 * @return	True if the player has the pass or false otherwise.
	 */
	public boolean hasPrisonPass() {
		return this.prisonPass;
	}
	
	/**
	 * setinPrison sets if the player is in prison or not.
	 * 
	 * @param option true if the player is to be sent to prison or false otherwise.
	 */
	public void setinPrison(boolean option) {
		this.inPrison = option;
	}
	
	/**
	 * setOut sets a player as out of the game.
	 * 
	 * @param option if the player is out (True) or in (False).
	 */
	public void setOut(boolean option) {
		this.isOut = option;
	}
	
	/**
	 * setPrisonPass sets if the current player has or not a "get out of prison" pass.
	 * 
	 * @param option if the player has (true) or not (false) the pass.
	 */
	public void setPrisonPass(boolean option) {
		this.prisonPass = option;
	}
	
	/**
	 * getTurnsInPrison gets the number of turns a player has been in prison.
	 * 
	 * @return the number of turns a player has been in prison.
	 */
	public int getTurnsInPrison() {
		return this.turnsInPrison;
	}
	
	/**
	 * incrementTurnsInPrison adds one turn in prison to the current player.
	 */
	public void incrementTurnsInPrison() {
		this.turnsInPrison++;
	}
	
	/**
	 * setTurnsInPrison sets the number of turns in prison for the current player.
	 * 
	 * @param turns to be set for the current player.
	 */
	public void setTurnsInPrison(int turns) {
		this.turnsInPrison = turns;
	}
	
	/**
	 * setXPosition sets the X position of the current player.
	 * 
	 * @param newX new X coordinate to be set.
	 */
	public void setXPosition(int newX) {
		this.x = newX;
	}
	
	/**
	 * setYPosition sets the Y position of the current player.
	 * 
	 * @param newY new Y coordinate to be set.
	 */
	public void setYPosition(int newY) {
		this.y = newY;
	}
	
	/**
	 * getXPosition gets the current player's X position.
	 * 
	 * @return the player's X position.
	 */
	public int getXPosition() {
		return this.x;
	}
	
	/**
	 * getYPosition gets the current player's Y position.
	 * 
	 * @return the player's Y position.
	 */
	public int getYPosition() {
		return this.y;
	}
	
	/**
	 * getIndex gets the current player's index.
	 * 
	 * @return player's index.
	 */
	public int getIndex() {
		return this.index;
	}
	
	/**
	 * setIndex sets a new index for the current player.
	 * 
	 * @param newIndex to be set.
	 */
	public void setIndex(int newIndex) {
		this.index = newIndex;
	}
}
