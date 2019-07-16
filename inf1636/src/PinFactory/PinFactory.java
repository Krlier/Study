package PinFactory;

import java.awt.Image;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.JOptionPane;

/**
 * 
 * PinFactory fabricates a new pin factory instance.
 *
 */
public class PinFactory {
	private Image pins[] = new Image[6];
	private int durl[][] = new int[6][2];
	private int pinIndex = 0; /* Pin number */
	private int startPosX[] = new int[6]; /* Pin starting X coordinate */
	private int startPosY[] = new int[6]; /* Pin starting Y coordinate */

	/**
	 * PinFactory loads pin images.
	 */
	public PinFactory() {
		try {
			pins[0] = ImageIO.read(new File("src/Imagens-01/pinos/pin0.png"));
			pins[1] = ImageIO.read(new File("src/Imagens-01/pinos/pin1.png"));
			pins[2] = ImageIO.read(new File("src/Imagens-01/pinos/pin2.png"));
			pins[3] = ImageIO.read(new File("src/Imagens-01/pinos/pin3.png"));
			pins[4] = ImageIO.read(new File("src/Imagens-01/pinos/pin4.png"));
			pins[5] = ImageIO.read(new File("src/Imagens-01/pinos/pin5.png"));
			for (int i = 0; i < 6; i++) {
				pins[i] = pins[i].getScaledInstance(25, 38, Image.SCALE_DEFAULT);
			}
		} catch (IOException e) {
			System.out.println(e.getMessage());
			System.exit(1);
		}
	}

	/**
	 * If an integer value is passed when initializing a new pin factory, only the
	 * pins starting positions are initialized.
	 * 
	 * @param k
	 */
	public PinFactory(int k) {
		for (int i = 0; i < 6; i++) {
			if (i % 2 == 0) {
				startPosX[i] = 605;
				startPosY[i] = 605 + i * 12;
			} else {
				startPosX[i] = 605 + 24;
				startPosY[i] = 605 + (i - 1) * 12;
			}
		}
	}

	/**
	 * NumberOfPlayers asks the user how many players will play.
	 * 
	 * @return number of players.
	 */
	public int NumberOfPlayers() {
		Object[] playerArray = { 2, 3, 4, 5, 6 };
		int players;
		try {
			players = (int) JOptionPane.showInputDialog(null, "Quantos Jogadores?", "Banco Imobiliário",
					JOptionPane.QUESTION_MESSAGE, null, playerArray, playerArray[0]);
		} catch (Exception e) {
			players = 2;
		}

		System.out.println(players);

		return players;
	}
	
	/**
	 * getPinImage gets a pin's image.
	 * 
	 * @param 	pinNumber Number of the desired pin.	
	 * @return 	pin's image
	 */
	public Image getPinImage(int pinNumber) {
		return this.pins[pinNumber];
	}
	
	/**
	 * getPinLane gets the pin's current lane.
	 * 
	 * @param 	pinNumber Number of the desired pin.
	 * @return	pin's lane number.
	 */
	public int getPinLane(int pinNumber) {
		return this.durl[pinNumber][0];
	}
	
	/**
	 * getPinHouse gets the pin's current house.
	 * 
	 * @param 	pinNumber Number of the desired pin.
	 * @return	pin's house number;
	 */
	public int getPinHouse(int pinNumber) {
		return this.durl[pinNumber][1];
	}
	
	/**
	 * setPinLane sets a new lane for the selected pin.
	 * 
	 * @param pinNumber	Number of the desired pin.
	 * @param newLane	New lane to be set.
	 */
	public void setPinLane(int pinNumber, int newLane) {
		this.durl[pinNumber][0] = newLane;
	}
	
	/**
	 * setPinHouse sets a new house for the selected pin;
	 * 
	 * @param pinNumber	Number of the desired pin.
	 * @param newHouse	to be set
	 */
	public void setPinHouse(int pinNumber, int newHouse) {
		this.durl[pinNumber][1] = newHouse;
	}
	
	/**
	 * getPinIndex gets a pin's index;
	 * 
	 * @return pin's index number.
	 */
	public int getPinIndex() {
		return this.pinIndex;
	}
	
	/**
	 * incrementPinIndex increments in 1 the pin's index.
	 */
	public void incrementPinIndex() {
		this.pinIndex++;
	}
	
	/**
	 * setPinIndex sets a new number for the pin's index.
	 * 
	 * @param index to be set.
	 */
	public void setPinIndex(int index) {
		this.pinIndex = index;
	}
	
	/**
	 * getStartingX gets a pin's starting X position.
	 *
	 * @param pinNumber	Number of the desired pin.
	 * @return an integer with the pin's starting X position.
	 */
	public int getStartingX(int pinNumber) {
		return this.startPosX[pinNumber];
	}
	
	/**
	 * getStartingY gets a pin's starting Y position.
	 *
	 * @param pinNumber	Number of the desired pin.
	 * @return an integer with the pin's starting XYposition.
	 */
	public int getStartingY(int pinNumber) {
		return this.startPosY[pinNumber];
	}

}
