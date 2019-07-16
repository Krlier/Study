package Card;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import javax.imageio.ImageIO;
import javax.swing.JLabel;

/**
 * Creates the Properties class to hold a map for the current properties.
 * 
 * @examples private Properties p = new Properties();
 * 
 *           Properties.propertyInfo(p.properties.get(houseNumber));
 * 
 */
public class Properties {
	public Map<Integer, Model> properties = new HashMap<Integer, Model>();

	private BufferedImage cards[] = new BufferedImage[28];

	/**
	 * Properties() loads all cards and fills properties with their values.
	 */
	public Properties() {
		loadCards();
		fillProperties();
	}

	/**
	 * propertyInfo displays property information on game screen.
	 * 
	 * @param m Property model to be shown.
	 * 
	 * @return A JLabel to be added to the game screen.
	 */
	public static JLabel propertyInfo(Model m) {
		String owner = "Sem dono";
		if (m.getOwner() == 0) {
			owner = "<font color=\"red\">Vermelho</font>";
		} else if (m.getOwner() == 1) {
			owner = "<font color=\"blue\">Azul</font>";
		} else if (m.getOwner() == 2) {
			owner = "<font color=\"orange\">Laranja</font>";
		} else if (m.getOwner() == 3) {
			owner = "<font color=\"yellow\">Amarelo</font>";
		} else if (m.getOwner() == 4) {
			owner = "<font color=\"purple\">Roxo</font>";
		} else if (m.getOwner() == 5) {
			owner = "<font color=\"grey\">Cinza</font>";
		}
		String info = String.format(
				"<html>Nome: %s <br/>Preço: $ %.2f <br/>Dono: %s <br/>Casas: %d <br/>Hoteis: %d <br/></html>", m.getName(),
				m.getPrice(), owner, m.getHouses(), m.getHotels());

		return new JLabel(info);
	}

	/**
	 * propertyCard returns a property's JLabel card
	 * 
	 * @param m Property model.
	 * 
	 * @return A JLabel to be added to the game screen.
	 */
	public static BufferedImage propertyCard(Model m) {
		return m.getImage();
	}

	/**
	 * loadCards loads all card images.
	 */
	private void loadCards() {
		try {
			cards[0] =  ImageIO.read(new File("src/Imagens-01/territorios/Leblon.png"));
			cards[1] =  ImageIO.read(new File("src/Imagens-01/territorios/Av. Presidente Vargas.png"));
			cards[2] =  ImageIO.read(new File("src/Imagens-01/territorios/Av. Nossa S. de Copacabana.png"));
			cards[3] =  ImageIO.read(new File("src/Imagens-01/companhias/company1.png"));
			cards[4] =  ImageIO.read(new File("src/Imagens-01/territorios/Av. Brigadero Faria Lima.png"));
			cards[5] =  ImageIO.read(new File("src/Imagens-01/companhias/company2.png"));
			cards[6] =  ImageIO.read(new File("src/Imagens-01/territorios/Av. Rebouças.png"));
			cards[7] =  ImageIO.read(new File("src/Imagens-01/territorios/Av. 9 de Julho.png"));
			cards[8] =  ImageIO.read(new File("src/Imagens-01/territorios/Av. Europa.png"));
			cards[9] =  ImageIO.read(new File("src/Imagens-01/territorios/Rua Augusta.png"));
			cards[10] = ImageIO.read(new File("src/Imagens-01/territorios/Av. Pacaembú.png"));
			cards[11] =ImageIO.read(new File("src/Imagens-01/companhias/company3.png"));
			cards[12] =ImageIO.read(new File("src/Imagens-01/territorios/Interlagos.png"));
			cards[13] =ImageIO.read(new File("src/Imagens-01/territorios/Morumbi.png"));
			cards[14] =ImageIO.read(new File("src/Imagens-01/territorios/Flamengo.png"));
			cards[15] =ImageIO.read(new File("src/Imagens-01/territorios/Botafogo.png"));
			cards[16] =ImageIO.read(new File("src/Imagens-01/companhias/company4.png"));
			cards[17] =ImageIO.read(new File("src/Imagens-01/territorios/Av. Brasil.png"));
			cards[18] =ImageIO.read(new File("src/Imagens-01/territorios/Av. Paulista.png"));
			cards[19] =ImageIO.read(new File("src/Imagens-01/territorios/Jardim Europa.png"));
			cards[20] =ImageIO.read(new File("src/Imagens-01/territorios/Copacabana.png"));
			cards[21] =ImageIO.read(new File("src/Imagens-01/companhias/company5.png"));
			cards[22] =ImageIO.read(new File("src/Imagens-01/territorios/Av. Vieira Souto.png"));
			cards[23] =ImageIO.read(new File("src/Imagens-01/territorios/Av. Atlântica.png"));
			cards[24] =ImageIO.read(new File("src/Imagens-01/companhias/company6.png"));
			cards[25] =ImageIO.read(new File("src/Imagens-01/territorios/Ipanema.png"));
			cards[26] =ImageIO.read(new File("src/Imagens-01/territorios/Jardim Paulista.png"));
			cards[27] =ImageIO.read(new File("src/Imagens-01/territorios/Brooklin.png"));

		} catch (IOException e) {
			System.out.println(e.getMessage());
			System.exit(1);
		}
	}

	/**
	 * fillProperties initializes properties with their initial values.
	 */
	private void fillProperties() {
		properties.put(0, new Model(0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Ponto de Partida", null));
		properties.put(1, new Model(1, 1, 100, -1, 0, 50, 0, 50, 50, 6, 30, 90, 270, 400, 500, "Leblon", cards[0]));
		properties.put(2, new Model(2, 3, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Sorte - Revés", null));
		properties.put(3, new Model(3, 1, 60, -1, 0, 50, 0, 50, 30, 2, 10, 30, 90, 160, 250, "Av. Presidente Vargas", cards[1]));
		properties.put(4, new Model(4, 1, 60, -1, 0, 50, 0, 50, 30, 4, 20, 60, 180, 320, 450, "Av. Nossa Senhora de Copacabana", cards[2]));
		properties.put(5, new Model(5, 2, 200, -1, 0, 0, 0, 0, 100, 50, 0, 0, 0, 0, 0, "Companhia Ferroviária", cards[3]));
		properties.put(6, new Model(6, 1, 240, -1, 0, 150, 0, 150, 120, 20, 100, 300, 750, 925, 1100, "Av. Brigadeiro Faria Lima", cards[4]));
		properties.put(7, new Model(7, 2, 200, -1, 0, 0, 0, 0, 100, 50, 0, 0, 0, 0, 0, "Companhia de Viação", cards[5]));
		properties.put(8, new Model(8, 1, 220, -1, 0, 150, 0, 150, 110, 18, 90, 250, 700, 875, 1050, "Av. Rebouças", cards[6]));
		properties.put(9, new Model(9, 1, 220, -1, 0, 150, 0, 150, 110, 18, 90, 250, 700, 875, 1050, "Av. 9 de julho", cards[7]));
		properties.put(10, new Model(10, 5, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Prisão", null));
		properties.put(11, new Model(11, 1, 220, -1, 0, 100, 0, 100, 100, 16, 80, 220, 600, 800, 1000, "Av. Europa", cards[8]));
		properties.put(12, new Model(12, 3, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Sorte - Revés", null));
		properties.put(13, new Model(13, 1, 310, -1, 0, 100, 0, 100, 90, 14, 70, 200, 550, 750, 950, "Rua Augusta", cards[9]));
		properties.put(14, new Model(14, 1, 310, -1, 0, 100, 0, 100, 90, 14, 70, 200, 550, 750, 950, "Av. Pacaembú", cards[10]));
		properties.put(15, new Model(15, 2, 150, -1, 0, 0, 0, 0, 75, 40, 0, 0, 0, 0, 0, "Companhia de Taxi", cards[11]));
		properties.put(16, new Model(16, 3, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Sorte - Revés", null));
		properties.put(17, new Model(17, 1, 350, -1, 0, 200, 0, 200, 175, 35, 175, 500, 1100, 1300, 1500, "Interlagos", cards[12]));
		properties.put(18, new Model(18, 4, 200, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Lucros Ou Dividendos", null));
		properties.put(19, new Model(19, 1, 400, -1, 0, 200, 0, 200, 200, 50, 200, 600, 1400, 1700, 2000, "Morumbi", cards[13]));
		properties.put(20, new Model(20, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Parada Livre", null));
		properties.put(21, new Model(21, 1, 120, -1, 0, 50, 0, 50, 60, 8, 40, 100, 300, 450, 600, "Flamengo", cards[14]));
		properties.put(22, new Model(22, 3, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Sorte - Revés", null));
		properties.put(23, new Model(23, 1, 100, -1, 0, 50, 0, 50, 50, 6, 30, 90, 270, 400, 500, "Botafogo", cards[15]));
		properties.put(24, new Model(24, 4, -200, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Imposto de Renda", null));
		properties.put(25, new Model(25, 2, 150, -1, 0, 0, 0, 0, 75, 40, 0, 0, 0, 0, 0, "Companhia de Navegação", cards[16]));
		properties.put(26, new Model(26, 1, 160, -1, 0, 100, 0, 100, 80, 12, 60, 180, 500, 700, 900, "Av. Brasil", cards[17]));
		properties.put(27, new Model(27, 3, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Sorte - Revés", null));
		properties.put(28, new Model(28, 1, 140, -1, 0, 100, 0, 100, 70, 10, 50, 150, 450, 625, 750, "Av. Paulista", cards[18]));
		properties.put(29, new Model(29, 1, 140, -1, 0, 100, 0, 100, 70, 10, 50, 150, 450, 625, 750, "Jardim Europa", cards[19]));
		properties.put(30, new Model(30, 5, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Prisão", null));
		properties.put(31, new Model(31, 1, 260, -1, 0, 150, 0, 150, 130, 22, 110, 330, 800, 975, 1150, "Copacabana", cards[20]));
		properties.put(32, new Model(32, 2, 200, -1, 0, 0, 0, 0, 100, 50, 0, 0, 0, 0, 0, "Companhia de Aviação", cards[21]));
		properties.put(33, new Model(33, 1, 320, -1, 0, 200, 0, 200, 160, 28, 150, 450, 1000, 1200, 1400, "Av. Vieira Souto", cards[22]));
		properties.put(34, new Model(34, 1, 300, -1, 0, 200, 0, 200, 150, 26, 130, 390, 900, 1100, 1275, "Av. Atlântica", cards[23]));
		properties.put(35, new Model(35, 2, 200, -1, 0, 0, 0, 0, 100, 50, 0, 0, 0, 0, 0, "Companhia de Táxi Aéreo", cards[24]));
		properties.put(36, new Model(36, 1, 300, -1, 0, 200, 0, 200, 150, 26, 130, 390, 900, 1100, 1275, "Ipanema", cards[25]));
		properties.put(37, new Model(37, 3, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Sorte - Revés", null));
		properties.put(38, new Model(38, 1, 280, -1, 0, 150, 0, 150, 140, 24, 120, 360, 850, 1025, 1200, "Jardim Paulista",cards[26]));
		properties.put(39, new Model(39, 1, 260, -1, 0, 150, 0, 150, 130, 22, 110, 330, 800, 975, 1150, "Brooklin", cards[27]));
	}

}
