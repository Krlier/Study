package GameState;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.security.KeyPair;
import java.security.KeyPairGenerator;
import java.security.NoSuchAlgorithmException;
import java.security.PrivateKey;
import java.security.PublicKey;
import java.security.SecureRandom;
import java.security.Signature;
import java.util.Base64;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Queue;

import javax.swing.JFileChooser;
import javax.swing.JOptionPane;
import javax.swing.filechooser.FileNameExtensionFilter;

import org.json.JSONException;
import org.json.JSONObject;

import Card.Model;
import PinFactory.PinFactory;
import Player.Player;

public class GameState {
	static KeyPair pair = generateKeyPair();
	static String savedJSON = "";

	/**
	 * saveGame Saves the game into a text file.
	 * 
	 * @param players 			Players array.
	 * @param durl	
	 * @param numberOfPlayers	Number of players currently playing.
	 * @param properties		Map of the properties current state.
	 * @param currentPlayer		Index number of the player playing this turn.
	 */
	public static void saveGame(Player[] players, PinFactory pf, int numberOfPlayers, Map<Integer, Model> properties, int currentPlayer, Queue<Integer> lucky) {
		String JtextFieldLocal;
		Model property = new Model();

		JSONObject obj = new JSONObject();
		for (int i = 0; i < 6; i++) {
			try {
				if (players[i] == null)
					continue;
				
				// Writes into the JSON all the necessary information to continue a saved game.
				obj.put(String.format("%s_money", Integer.toString(players[i].getIndex())), players[i].getMoney());
				obj.put(String.format("%s_inPrison", Integer.toString(players[i].getIndex())), players[i].inPrison());
				obj.put(String.format("%s_hasPrisonPass", Integer.toString(players[i].getIndex())), players[i].hasPrisonPass());
				obj.put(String.format("%s_isOut", Integer.toString(players[i].getIndex())), players[i].isOut());
				obj.put(String.format("%s_index", Integer.toString(players[i].getIndex())), players[i].getIndex());
				obj.put(String.format("%s_lane", Integer.toString(players[i].getIndex())), pf.getPinLane(i));
				obj.put(String.format("%s_house", Integer.toString(players[i].getIndex())), pf.getPinHouse(i));

				obj.put(String.format("%s_x", Integer.toString(players[i].getIndex())), players[i].getXPosition());
				obj.put(String.format("%s_y", Integer.toString(players[i].getIndex())), players[i].getYPosition());

			} catch (JSONException e) {
				System.out.println("Error writting JSON!");
				e.printStackTrace();
			}
		}

		try {
			// Writes all the relevant property info to the JSON.
			for (int i = 0; i < 40; i++) {
				property = properties.get(i);
				if (property.getOwner() != -1)
					obj.put(String.format("%s_owner", Integer.toString(i)), property.getOwner());
				if (property.getHouses() != 0 || property.getHotels() != 0) {
					obj.put(String.format("%s_houses", Integer.toString(i)), property.getHouses());
					obj.put(String.format("%s_hotels", Integer.toString(i)), property.getHotels());
				}
			}
			obj.put("numberOfPlayers", numberOfPlayers);
			obj.put("currentPlayer", currentPlayer);
		} catch (JSONException e1) {
			System.out.println("Error writting JSON!");
			e1.printStackTrace();
		}
		
		int n = lucky.size();
		for ( int i = 0; i < n; i++ ) {
			try {
				obj.put(String.format("%d_luck", i), lucky.remove());
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		

		// Get's the user chosen file.
		JFileChooser file = new JFileChooser();
		FileNameExtensionFilter filter = new FileNameExtensionFilter("TEXT FILES", "txt", "text");
		file.setFileFilter(filter);
		file.setFileSelectionMode(JFileChooser.FILES_ONLY);
		int i = file.showSaveDialog(null);
		if (i == 1) {
			JtextFieldLocal = "save.txt";
		} else {
			File arquivo = file.getSelectedFile();
			JtextFieldLocal = arquivo.getPath();
		}

		try {
			// Signs the resulting JSON with a private key to know if the save file has been tampered with.
			String signature = sign(obj.toString(), pair.getPrivate());
			savedJSON = obj.toString();
			obj.put("signature", signature);
		} catch (Exception e1) {
			System.out.println("Error signing JSON string!");
			e1.printStackTrace();
		}

		try {
			FileWriter saveFile = new FileWriter(JtextFieldLocal);
			saveFile.write(obj.toString());
			saveFile.flush();
			saveFile.close();
		} catch (IOException e) {
			System.out.println("Error saving the game!");
			e.printStackTrace();
		}

		JOptionPane.showMessageDialog(null, "Jogo salvo com sucesso!", "Jogo Salvo!", JOptionPane.PLAIN_MESSAGE);
	}

	/**
	 * loadGame Loads a previously saved game.
	 * 
	 * @param players 			Players array.
	 * @param durl				Holds house number and lane number.
	 * @param numberOfPlayers	
	 * @param properties		Map of the properties current state.
	 * 
	 * @return
	 */
	public static boolean loadGame(Player[] players, PinFactory pf, int[] numberOfPlayers, Map<Integer, Model> properties, Queue<Integer> lucky) {
		String JtextFieldLocal;
		String jsonString = null;
		JSONObject json = null;
		int playerIndex;
		Model property = new Model();
		boolean l = true;

		// Gets the saved file (must be a text file)
		JFileChooser file = new JFileChooser();
		FileNameExtensionFilter filter = new FileNameExtensionFilter("TEXT FILES", "txt", "text");
		file.setFileFilter(filter);
		file.setFileSelectionMode(JFileChooser.FILES_ONLY);
		int i = file.showOpenDialog(null);
		if (i == 1) {
			JtextFieldLocal = "";
		} else {
			File arquivo = file.getSelectedFile();
			JtextFieldLocal = arquivo.getPath();
		}

		try {
			// Reads the saved file's JSON.
			BufferedReader br = new BufferedReader(new FileReader(JtextFieldLocal));
			jsonString = br.readLine();
			br.close();
			json = new JSONObject(jsonString);
		} catch (Exception e) {
			System.out.println("Could not load save file!");
			return false;
		}

		try {
			// Verifies signature with public key.
			// Note: Only the same game-client will be able to save / load a save file without the message below showing up.
			String signature = (String) json.get("signature");
			boolean check = verify(savedJSON, signature, pair.getPublic());
			if (!check) {
				int option = JOptionPane.showConfirmDialog(null,
						"<html>O arquivo de jogo carregado pode ter sido alterado ou não foi gerado por este client!<br />Deseja Continuar?</html>");
				if (option != 0) {
					System.exit(0);
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		}

		// Loads all the relevant game information back to the game.
		for (int k = 0; k < 6; k++) {
			players[k] = new Player();
			try {
				playerIndex = json.getInt(String.format("%s_index", Integer.toString(k)));
				players[playerIndex].setMoney((float) json.getDouble(String.format("%s_money", Integer.toString(playerIndex))));
				players[playerIndex].setinPrison(json.getBoolean(String.format("%s_inPrison", Integer.toString(playerIndex))));
				players[playerIndex].setPrisonPass(json.getBoolean(String.format("%s_hasPrisonPass", Integer.toString(playerIndex))));
				players[playerIndex].setOut(json.getBoolean(String.format("%s_isOut", Integer.toString(playerIndex))));
				players[playerIndex].setXPosition(json.getInt(String.format("%s_x", Integer.toString(playerIndex))));
				players[playerIndex].setYPosition(json.getInt(String.format("%s_y", Integer.toString(playerIndex))));
				
				pf.setPinLane(playerIndex, json.getInt(String.format("%s_lane", Integer.toString(playerIndex))));
				pf.setPinHouse(playerIndex, json.getInt(String.format("%s_house", Integer.toString(playerIndex))));

				;
			} catch (JSONException e) {

			} catch (Exception e) {
				System.out.println("Could not read player and pin positions from save file!");
				e.printStackTrace();
				return false;
			}
		}

		for (int j = 0; j < 40; j++) {
			property = properties.get(j);
			try {
				property.setOwner(json.getInt(String.format("%s_owner", Integer.toString(j))));
				property.setHouses(json.getInt(String.format("%s_houses", Integer.toString(j))));
				property.setHotels(json.getInt(String.format("%s_hotels", Integer.toString(j))));

				properties.put(j, property);
			} catch (JSONException e) {

			} catch (Exception e) {
				System.out.println("Could not read properties from save file!");
				e.printStackTrace();
				return false;
			}
		}
		
		int cardNumber = 0;
		while(l) {
			try {
				int test = json.getInt(String.format("%s_luck", Integer.toString(cardNumber)));
				lucky.add(test);
			} catch (JSONException e) {
				l = false;
			} catch (Exception e) {
				e.printStackTrace();
				return false;
			}
			cardNumber++;
		}

		try {
			numberOfPlayers[0] = json.getInt("numberOfPlayers");
			numberOfPlayers[1] = json.getInt("currentPlayer");
		} catch (Exception e) {
			System.out.println("Could not get number of players from save file!");
			e.printStackTrace();
			return false;
		}

		return true;
	}

	/**
	 * generateKeyPair Generates a pair of private and public keys.
	 * 
	 * @return KeyPair
	 */
	private static KeyPair generateKeyPair() {
		KeyPairGenerator g = null;
		try {
			g = KeyPairGenerator.getInstance("RSA");
		} catch (NoSuchAlgorithmException e) {
			e.printStackTrace();
		}

		g.initialize(2048, new SecureRandom());
		KeyPair pair = g.generateKeyPair();

		return pair;
	}

	/**
	 * sign Signs a string with a private key.
	 * 
	 * @param s				The string to be signed.
	 * @param privateKey	The private key that's going to be used.
	 * @return				The signed string.
	 * @throws Exception	Wasn't able to sign the given string.
	 */
	private static String sign(String s, PrivateKey privateKey) throws Exception {
		Signature privateSignature = Signature.getInstance("SHA256withRSA");
		privateSignature.initSign(privateKey);
		privateSignature.update(s.getBytes());

		byte[] signature = privateSignature.sign();

		return Base64.getEncoder().encodeToString(signature);
	}

	/**
	 * 
	 * 
	 * @param s				The string to be signed.
	 * @param signature		The original string, before signing.
	 * @param publicKey		The public key used to decrypt the string.
	 * @return				True, if the signature matches the original string. False otherwise.
	 * @throws Exception	Wasn't able to verify the signature's authenticity.
	 */
	private static boolean verify(String s, String signature, PublicKey publicKey) throws Exception {
		Signature publicSignature = Signature.getInstance("SHA256withRSA");
		publicSignature.initVerify(publicKey);
		publicSignature.update(s.getBytes());

		byte[] signatureBytes = Base64.getDecoder().decode(signature);

		return publicSignature.verify(signatureBytes);
	}
	
	/**
	 * convertIntegers converts an integer array list into an integer array. 
	 * 
	 * @param integers	Integer array list.
	 * @return			Integer array.
	 */
	public static int[] convertIntegers(List<Integer> integers) {
	    int[] ret = new int[integers.size()];
	    Iterator<Integer> iterator = integers.iterator();
	    for (int i = 0; i < ret.length; i++)
	    {
	        ret[i] = iterator.next().intValue();
	    }
	    return ret;
	}
}
