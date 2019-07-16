package Dice;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;

/**
 * 
 * Creates the Dice class, which holds the images of all the dice sides.
 *
 */
public class Dice {
	public final int POS_BOTAO_X = 720;
	public final int POS_BOTAO_Y = 744;

	private BufferedImage dados[] = new BufferedImage[6];

	public Dice() {
		try {
			dados[0] = ImageIO.read(new File("src/Imagens-01/dados/die_face_1.png"));
			dados[1] = ImageIO.read(new File("src/Imagens-01/dados/die_face_2.png"));
			dados[2] = ImageIO.read(new File("src/Imagens-01/dados/die_face_3.png"));
			dados[3] = ImageIO.read(new File("src/Imagens-01/dados/die_face_4.png"));
			dados[4] = ImageIO.read(new File("src/Imagens-01/dados/die_face_5.png"));
			dados[5] = ImageIO.read(new File("src/Imagens-01/dados/die_face_6.png"));
		} catch (IOException e) {
			System.out.println(e.getMessage());
			System.exit(1);
		}
	}

	/**
	 * getDiceList gets an array of dice images.
	 * 
	 * @return an BufferedImages array.
	 */
	public BufferedImage[] getDiceList() {
		return dados;
	}
	
	/**
	 * notify gets one of the dice sides and returns it.
	 * 
	 * @param random	The dice side to be returned.
	 * @return			The dice side to be returned.
	 */
	public BufferedImage notify(int random) {
		return dados[random];
	}

}
