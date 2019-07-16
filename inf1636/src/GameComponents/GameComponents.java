package GameComponents;

import java.awt.Graphics;
import java.awt.Image;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.ListIterator;
import java.util.Queue;

import javax.imageio.ImageIO;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;

import Card.Luck;
import Card.Model;
import Card.Properties;
import Dice.Dice;
import GameState.GameState;
import PinFactory.PinFactory;
import Player.Player;

/**
 * Creates and exhibits the GameComponents class, which is responsible for
 * generating the game board and all the other necessary components.
 * 
 * @example GameComponents GC = new GameComponents();
 * 
 */
public class GameComponents extends JPanel implements ActionListener {

	private static final long serialVersionUID = 3135596967773482418L;
	private BufferedImage tabuleiro;
	private JButton diceButton = diceButton();
	private JButton buyHouseButton = buyHouseButton();
	private JButton buyHotelButton = buyHotelButton();
	private JButton buyPropertyButton = buyPropertyButton();
	private JButton endGameButton = endGameButton();
	private JButton saveGameButton = saveGameButton();
	private JButton sellPropertyButton = sellPropertyButton();
	private JButton DebugMode = debugButton();
	private Dice dice1 = new Dice();
	private Dice dice2 = new Dice();
	private JLabel pInfo;
	private BufferedImage pCard;
	private JLabel playerMoney;
	private PinFactory pf = new PinFactory();
	private Player players[] = new Player[6];
	private Properties p = new Properties();
	private int numberOfPlayers;
	private int[] n = new int[2];
	private Queue<Integer> luckyCards = new LinkedList<>();
	private int house;
	private int lane;
	private int playerNumber;
	private int activePlayers;
	private float housePrice = 50;
	private float hotelPrice = 100;
	private int maxHouses = 4;
	private int maxHotels = 1;
	private Luck lucky;
	private int blockType;
	private int dice1Side = -1;
	private int dice2Side = -1;
	private int houseNumber = -1;
	private boolean check;
	private Rectangle r = new Rectangle();
	private boolean used;
	private BufferedImage tmp = null;
	private int debugDice1 = -1;
	private int debugDice2 = -1;
	@SuppressWarnings("rawtypes")
	JComboBox combo;
	
	private List<Dice> observed = new ArrayList<Dice>();
	private int []randomNums = new int[2];
	
	/**
	 * addObserved adds an observed dice.
	 */
	private void addObserved()
	{
		observed.add(dice1);
		observed.add(dice2);
	}
	
	/**
	 * update updates the dice image.
	 * 
	 * @param diceImage
	 */
	private void update(BufferedImage []diceImage)
	{
		ListIterator<Dice> li=observed.listIterator();
		
		int i = 0;
		while(li.hasNext())
		{
			diceImage[i] = li.next().notify(randomNums[i]-1);
			i++;
		}
	}

	public GameComponents() {
		addObserved();
		check = GameState.loadGame(players, pf, n, p.properties, luckyCards);
		if (check)
		{
			setPositions();
			lucky = Luck.getInstance(luckyCards);
		}
		
		else
		{
			lucky = Luck.getInstance();
		}
		
		try {
			tabuleiro = ImageIO.read(new File("src/Imagens-01/tabuleiro.png"));
			this.setLayout(null);
			ButtonFacade.addButtons(this, diceButton, buyHotelButton, buyHouseButton,
					buyPropertyButton, endGameButton, saveGameButton, sellPropertyButton, DebugMode);

			// adding pins to UI
			if (!check) {
				numberOfPlayers = pf.NumberOfPlayers();
			} else {
				numberOfPlayers = n[0];
			}
			activePlayers = numberOfPlayers;

		} catch (IOException e) {
			System.out.println(e.getMessage());
			System.exit(1);
		}
	}

	@Override
	protected void paintComponent(Graphics g) {
		super.paintComponent(g);
		g.drawImage(tabuleiro, 0, 0, this);
		
		if(dice1Side != -1 && dice2Side != -1)
		{
			BufferedImage []diceImage = new BufferedImage[2];
			
			update(diceImage);
			if(diceImage[0] != null && diceImage[1] != null)
			{
				g.drawImage(diceImage[0], 720, 40, 100, 100, this);
				g.drawImage(diceImage[1], 860, 40, 100, 100, this);
				
			}
		}
		
		if(houseNumber != -1)
		{
			BufferedImage card;
			card = getPropertyImage(houseNumber, blockType);
			if (card != null) {
				int w = card.getWidth();
				int h = card.getHeight();
				g.drawImage(card, 750, 360, w, h, this);				
			}
		}
			
		// Draw pins		
		Image pin;
		if ( !check ) {
			for (int i = 0; i < numberOfPlayers; i++) {
				if (!check) {
					players[i] = new Player();
					players[i].setIndex(i);
					pin = pf.getPinImage(i);
					if (i % 2 == 0) {
						g.drawImage(pin, 605, 605 + i * 12, 25, 38, this);
						players[i].setXPosition(605);
						players[i].setYPosition(605 + i * 12);
					} else {
						g.drawImage(pin, 605 + 24, 605 + (i - 1) * 12, 25, 38, this);
						players[i].setXPosition(605 + 24);
						players[i].setYPosition(605 + (i - 1) * 12);
					}
				}
			}
		}
		
		// Pins have already been drawn		
		check = true;
		
		// Draw pin indicator between dice		
		pin = pf.getPinImage(playerNumber);
		g.drawImage(pin, 825, 60, 25, 38, this);
		
		// Draw all pins
		for (int i = 0; i < numberOfPlayers; i++) {
			pin = pf.getPinImage(i);
			g.drawImage(pin, players[i].getXPosition(), players[i].getYPosition(), 25, 38, this);
		}
		
	}

	/**
	 * diceButton() creates and returns a new dice roll button for the user
	 * interface.
	 * 
	 * @return A new JButton dice button.
	 */
	private JButton diceButton() {
		JButton d = new JButton("Joga o dado / Encerra vez");
		d.setBounds(720, 10, 250, 20);
		// creating mouse click event
		d.addActionListener(this);
		return d;
	}
	
	
	/**
	 * debugButton creates and returns a new debug button for the user interface.
	 * 
	 * @return A new JButton debug button.
	 */
	private JButton debugButton() { 
		JButton debug = new JButton("Debug Mode");
		 debug.setBounds(270, 300, 170, 20);
		 debug.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				JFrame debugBox = new JFrame("Debugging");
				debugBox.setLayout(null);
				JLabel label1 = new JLabel("Dado1: ");
				label1.setBounds(0, 0 , 100, 20);
				JLabel label2 = new JLabel("Dado2: ");
				label2.setBounds(0, 20 , 100, 20);
				JTextField v1 = new JTextField();
				JTextField v2 = new JTextField();
				JButton diceThrow = new JButton("Carregar Dados");
				diceThrow.setBounds(10, 60, 120, 20);
				v1.setBounds(55, 0, 100, 20);
				v2.setBounds(55, 20, 100, 20);
				debugBox.add(v1); debugBox.add(v2); 
				debugBox.add(diceThrow);
				debugBox.add(label1);debugBox.add(label2);
				debugBox.setVisible(true);
				debugBox.setBounds(700, 350 ,175, 120);
				
				diceThrow.addActionListener(new ActionListener()
				{
					@Override
					public void actionPerformed(ActionEvent e) 
					{
						String d1 = v1.getText();
						String d2 = v2.getText();
						
						if ( d1.equals("") || d2.equals("") ) {
							JOptionPane.showMessageDialog(null, "<html>Por favor insira valores nos dois campos dos dados!</html>", "Erro!", JOptionPane.WARNING_MESSAGE);
							return;
						}
						
						if ( Integer.valueOf(d1) > 6 || Integer.valueOf(d1) < 0 || Integer.valueOf(d2) > 6 || Integer.valueOf(d2) < 0) {
							JOptionPane.showMessageDialog(null, "<html>Valor incorreto!<br/>Insira valores maiores que 0 e menores que 7</html>", "Erro!", JOptionPane.WARNING_MESSAGE);
							return;
						}
						
						debugDice1 = Integer.valueOf(d1);
						debugDice2 = Integer.valueOf(d2);
						
						debugBox.dispose();
					}
				});
			}});
		  return debug;
	  }
	 

	/**
	 * buyHouseButton() creates and returns a new buy house button for the user
	 * interface.
	 * 
	 * 
	 * @return A new JButton buy house button.
	 */
	private JButton buyHouseButton() {
		JButton d = new JButton("Comprar Casa");
		d.setBounds(720, 180, 120, 20);
		d.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				int propertyKey = houseNumber;
				Model property = p.properties.get(propertyKey); // Gets property model
				if (property.getType() == 1) { // Check if you can build a house in this property type
					if (property.getOwner() == playerNumber) { // Check if the player owns this property
						if (property.getHouses() < maxHouses) { // Check if the max number of houses has been reached
							if (players[playerNumber].getMoney() >= housePrice) { // Check if player has enough money to
																				// build a house
								players[playerNumber].setMoney(players[playerNumber].getMoney() - 50);
								property.incrementHouses();
							} else {
								JOptionPane.showMessageDialog(null, "Você não possui dinheiro suficiente!", "Alerta",
										JOptionPane.INFORMATION_MESSAGE);
							}
						} else {
							JOptionPane.showMessageDialog(null,
									"Você não pode construir mais casas aqui, que tal um hotel?", "Alerta",
									JOptionPane.INFORMATION_MESSAGE);
						}
					} else {
						JOptionPane.showMessageDialog(null, "Você não é o dono dessa propriedade!", "Alerta",
								JOptionPane.INFORMATION_MESSAGE);
					}
				} else {
					JOptionPane.showMessageDialog(null, "Você não pode construir uma casa aqui!", "Alerta",
							JOptionPane.INFORMATION_MESSAGE);
				}
				p.properties.put(propertyKey, property);
				showPlayerMoney(playerNumber);
				showPropertyInfo(houseNumber);
			}
		});

		return d;
	}

	/**
	 * buyHotelButton() creates and returns a new buy hotel button for the user
	 * interface.
	 * 
	 * @return new JButton buy hotel button.
	 */
	private JButton buyHotelButton() {
		JButton d = new JButton("Comprar Hotel");
		d.setBounds(850, 180, 120, 20);
		d.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				int propertyKey = houseNumber;
				Model property = p.properties.get(propertyKey); // Gets property model
				if (property.getType() == 1) { // Check if you can build in this property type
					if (property.getOwner() == playerNumber) { // Check if the player owns this property
						if (property.getHouses() == maxHouses) { // Check if there are enough houses to build an hotel
							if (property.getHotels() < maxHotels) { // Check if there aren't max hotels
								if (players[playerNumber].getMoney() >= hotelPrice) { // Check if the player has enough money
																					// to build an hotel
									players[playerNumber].setMoney(players[playerNumber].getMoney() - hotelPrice);
									property.incrementHotels();
									property.setHouses(0);
								} else {
									JOptionPane.showMessageDialog(null, "Você não possui dinheiro suficiente!",
											"Alerta", JOptionPane.INFORMATION_MESSAGE);
								}
							} else {
								JOptionPane.showMessageDialog(null, "Você não pode construir mais hoteis!", "Alerta",
										JOptionPane.INFORMATION_MESSAGE);
							}
						} else {
							JOptionPane.showMessageDialog(null,
									"Você precisa construir mais casas antes de construir um hotel!", "Alerta",
									JOptionPane.INFORMATION_MESSAGE);
						}
					} else {
						JOptionPane.showMessageDialog(null, "Você não é o dono dessa propriedade!", "Alerta",
								JOptionPane.INFORMATION_MESSAGE);
					}
				} else {
					JOptionPane.showMessageDialog(null, "Você não pode construir um hotel aqui!", "Alerta",
							JOptionPane.INFORMATION_MESSAGE);
				}
				p.properties.put(propertyKey, property);
				showPlayerMoney(playerNumber);
				showPropertyInfo(houseNumber);
			}
		});

		return d;
	}

	/**
	 * buyPropertyButton() creates and returns a new buy property button for the
	 * user interface.
	 * 
	 * @return new JButton buy property button.
	 */
	private JButton buyPropertyButton() {
		JButton d = new JButton("Comprar Lote");
		d.setBounds(720, 205, 120, 20);
		d.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				int propertyKey = houseNumber;
				Model property = p.properties.get(propertyKey);
				if (property.getType() == 1 || property.getType() == 2) {
					if (property.getOwner() == -1) {
						if (players[playerNumber].getMoney() >= property.getPrice()) {
							property.setOwner(playerNumber);
							players[playerNumber].setMoney(players[playerNumber].getMoney() - property.getPrice());
						} else {
							JOptionPane.showMessageDialog(null, "Você não possui dinheiro suficiente!", "Alerta", JOptionPane.INFORMATION_MESSAGE);
						}
					} else {
						JOptionPane.showMessageDialog(null, "Essa propriedade já possui dono!", "Alerta", JOptionPane.INFORMATION_MESSAGE);
					}
				} else {
					JOptionPane.showMessageDialog(null, "Você não pode comprar essa propriedade!", "Alerta", JOptionPane.INFORMATION_MESSAGE);
				}
				p.properties.put(propertyKey, property);
				showPlayerMoney(playerNumber);
				showPropertyInfo(houseNumber);
			}
		});

		return d;
	}

	/**
	 * sellPropertyButton() creates and returns a new sell property button for the
	 * user interface.
	 * 
	 * @return new JButton sell property button.
	 */
	private JButton sellPropertyButton() {
		JButton d = new JButton("Vender Lote");
		d.setBounds(850, 205, 120, 20);
		d.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				int propertyKey = houseNumber;
				float revenue = 0;
				Model property = p.properties.get(propertyKey);
				if ( property.getOwner() == players[playerNumber].getIndex() ) {
					if ( property.getHouses() > 0 ) {
						revenue = revenue + property.getHousePrice() * property.getHouses();
					}
					if ( property.getHotels() > 0 ) {
						revenue = revenue + property.getHotelPrice() * property.getHotels();
					}
					revenue = revenue + property.getPrice();
					revenue = (float) (revenue * 0.9);
					
					property.setOwner(-1);
					property.setHouses(0);
					property.setHotels(0);
					
					players[playerNumber].setMoney(players[playerNumber].getMoney() + revenue);
					String text = String.format("<html>Você acaba de receber $%.2f pela venda!</html>", revenue);
					JOptionPane.showMessageDialog(null, text, "Venda", JOptionPane.INFORMATION_MESSAGE);
				} else {
					JOptionPane.showMessageDialog(null, "Você não é dono dessa propriedade!", "Alerta", JOptionPane.INFORMATION_MESSAGE);
				}
				
				p.properties.put(propertyKey, property);
				showPlayerMoney(playerNumber);
				showPropertyInfo(houseNumber);
				checkBankrupcy();
			}
		});
		
		return d;
	}
	
	/**
	 * endGameButton() creates and returns a new end game button for the user
	 * interface.
	 * 
	 * @return new JButton end game button.
	 */
	private JButton endGameButton() {
		JButton d = new JButton("Encerrar o jogo");
		d.setBounds(760, 675, 170, 20);
		d.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				int richestPlayer = 0;
				float richestPlayerMoney = -1;
				String winner;
				for (int i = 0; i < numberOfPlayers; i++) {
					if (players[i].getMoney()> richestPlayerMoney) {
						richestPlayer = i;
						richestPlayerMoney = players[i].getMoney();
					}
				}
				if (richestPlayer == 0) {
					winner = "<font color=\"red\">Vermelho</font>";
				} else if (richestPlayer == 1) {
					winner = "<font color=\"blue\">Azul</font>";
				} else if (richestPlayer == 2) {
					winner = "<font color=\"orange\">Laranja</font>";
				} else if (richestPlayer == 3) {
					winner = "<font color=\"yellow\">Amarelo</font>";
				} else if (richestPlayer == 4) {
					winner = "<font color=\"purple\">Roxo</font>";
				} else {
					winner = "<font color=\"grey\">Cinza</font>";
				}

				String text = String.format("<html>O vencedor é o: %s</html>", winner);
				JOptionPane.showMessageDialog(null, text, "Parabéns!", JOptionPane.PLAIN_MESSAGE);
				System.exit(0);
			}
		});
		return d;
	}

	/**
	 * saveGameButton() creates and returns a new save game button for the user
	 * interface.
	 * 
	 * @return new JButton save game button.
	 */
	private JButton saveGameButton() {
		JButton d = new JButton("Salvar o jogo");
		d.setBounds(760, 650, 170, 20);
		d.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				GameState.saveGame(players, pf, numberOfPlayers, p.properties, pf.getPinIndex(), lucky.getIndexOrder());
			}
		});

		return d;
	}

	/**
	 * showPlayerOwnedProperties() creates and returns a new combo box for the user
	 * interface with the player's owned properties.
	 * 
	 * @return new JComboBox to exhibit the current player's properties.
	 */
	@SuppressWarnings("rawtypes")
	private JComboBox showPlayerOwnedProperties() {
		ArrayList<String> pNames = new ArrayList<String>();
		ArrayList<Model> pModel = new ArrayList<Model>();
		
		// Adds the house the player has landed in this turn to the combo box.
		if(p.properties.get(houseNumber) == null)
			System.out.println("break");
		pNames.add(p.properties.get(houseNumber).getName());
		pModel.add(p.properties.get(houseNumber));
		for (int i = 0; i < 40; i++) {	// Search for player owned properties.
			if (pf.getPinIndex() == p.properties.get(i).getOwner() && p.properties.get(i).getIndex() != houseNumber) {
				pNames.add(p.properties.get(i).getName());
				pModel.add(p.properties.get(i));
			}
		}
		
		// Create new comboBox.
		@SuppressWarnings("unchecked")
		JComboBox<String> combo = new JComboBox(pNames.toArray());
		
		// Creates a new Action Listener to capture the selected player property.
		combo.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				
				// Set's houseNumber globally, so it may be drawn.
				houseNumber = pModel.get(combo.getSelectedIndex()).getIndex();
				blockType = pModel.get(combo.getSelectedIndex()).getType();
				showPropertyInfo(houseNumber);
				
				revalidate();
				repaint();
				
		    }
		});
		
		combo.setBounds(760, 205, 220, 100);
		revalidate();
		repaint();
		
		return combo;
	}
	
	/**
	 * actionPerformed of the dice button.
	 */
	@Override
	public void actionPerformed(ActionEvent e) {
		used = false;
		
		
		String playerInPrison;
		
		for(int i = 0; i < 2; i++)
			randomNums[i] = (int) (Math.random() * 6 + 1);
		
		int random = randomNums[0] + randomNums[1];
		dice1Side = randomNums[0] - 1;
		dice2Side = randomNums[1] - 1;
		
		if(debugDice1 != -1 && debugDice2 != -1)
		{
			dice1Side = debugDice1 -1;
			dice2Side = debugDice2 -1;
			
			random = debugDice1 + debugDice2;
		}
		
		randomNums[0] = dice1Side + 1;
		randomNums[1] = dice2Side + 1;
		
		/*
		 * pinIndex[0] -> Holds which lane the pin is: bottom, left, top or right
		/* pinIndex[1] -> Holds in which house the pin is at */

		// Sets index back to first player after one round
		if (pf.getPinIndex() > (numberOfPlayers - 1))
			pf.setPinIndex(0);

		playerNumber = pf.getPinIndex();
		houseNumber = (pf.getPinLane(pf.getPinIndex()) * 10) + pf.getPinHouse(pf.getPinIndex());
		if (players[playerNumber].inPrison()) { // Check if player is arrested
			System.out.println(players[playerNumber].getTurnsInPrison());
			if (randomNums[0] != randomNums[1] && players[playerNumber].hasPrisonPass() != true && players[playerNumber].getTurnsInPrison() < 3) { // Player didn't roll the same number on both dice

				if (playerNumber == 0) {
					playerInPrison = "<font color=\"red\">Vermelho</font>";
				} else if (playerNumber == 1) {
					playerInPrison = "<font color=\"blue\">Azul</font>";
				} else if (playerNumber == 2) {
					playerInPrison = "<font color=\"orange\">Laranja</font>";
				} else if (playerNumber == 3) {
					playerInPrison = "<font color=\"yellow\">Amarelo</font>";
				} else if (playerNumber == 4) {
					playerInPrison = "<font color=\"purple\">Roxo</font>";
				} else {
					playerInPrison = "<font color=\"grey\">Cinza</font>";
				}
				
				revalidate();
				repaint();
				
				String text = String.format("<html>%s perdeu a vez, continua preso.</html>", playerInPrison);
				JOptionPane.showMessageDialog(null, text, "Prisão", JOptionPane.INFORMATION_MESSAGE);
				
				players[playerNumber].incrementTurnsInPrison();
				pf.incrementPinIndex();
				return;
			}
			else {
				if (players[playerNumber].getTurnsInPrison() >= 3)
					players[playerNumber].setMoney(players[playerNumber].getMoney() - 50);
				players[playerNumber].setinPrison(false);
				players[playerNumber].setTurnsInPrison(0);
			}
		}

		/* Checks which lane the pin is at */
		if (pf.getPinLane(pf.getPinIndex()) == 0) /* Pin is on the left lane */
		{
			/* test calculates whether the pin will change lanes in this dice roll or not */
			int test = random + pf.getPinHouse(pf.getPinIndex()) - 10;
			if (test < 0) { /* The pin will not change lanes in this dice roll */
				walkLeft(pf.getPinIndex(), pf.getPinHouse(pf.getPinIndex()), random);
				pf.setPinHouse(pf.getPinIndex(), (pf.getPinHouse(pf.getPinIndex()) + random));
			}
			if (test >= 0 && test < 10) /* The pin will change 1 lane in this dice roll */
			{
				walkUp(pf.getPinIndex(), -1, test);
				pf.setPinLane(pf.getPinIndex(), 1); /* Change the pin's lane to left */
				pf.setPinHouse(pf.getPinIndex(), test);
			}
			if (test >= 10) { /* The pin will change 2 lanes in this dice roll */
				walkRight(pf.getPinIndex(), -1, test - 10);
				pf.setPinLane(pf.getPinIndex(), 2);
				pf.setPinHouse(pf.getPinIndex(), test - 10);
			}
			house = pf.getPinHouse(pf.getPinIndex());
			lane = pf.getPinLane(pf.getPinIndex());
			playerNumber = pf.getPinIndex();
		} else if (pf.getPinLane(pf.getPinIndex()) == 1) /* Pin is on the left lane */
		{
			int test = random + pf.getPinHouse(pf.getPinIndex()) - 10;
			if (test < 0) {
				walkUp(pf.getPinIndex(), pf.getPinHouse(pf.getPinIndex()), random);
				pf.setPinHouse(pf.getPinIndex(), pf.getPinHouse(pf.getPinIndex()) + random);
			}
			if (test >= 0 && test < 10) {
				walkRight(pf.getPinIndex(), -1, test);
				pf.setPinLane(pf.getPinIndex(), 2);
				pf.setPinHouse(pf.getPinIndex(), test);
			}
			if (test >= 10) {
				walkDown(pf.getPinIndex(), -1, test - 10);
				pf.setPinLane(pf.getPinIndex(), 3);
				pf.setPinHouse(pf.getPinIndex(), test - 10);
			}
			house = pf.getPinHouse(pf.getPinIndex());
			lane = pf.getPinLane(pf.getPinIndex());
			playerNumber = pf.getPinIndex();
		} else if (pf.getPinLane(pf.getPinIndex()) == 2) /* Pin is on the top lane */
		{
			int test = random + pf.getPinHouse(pf.getPinIndex()) - 10;
			if (test < 0) {
				walkRight(pf.getPinIndex(), pf.getPinHouse(pf.getPinIndex()), random);
				pf.setPinHouse(pf.getPinIndex(), pf.getPinHouse(pf.getPinIndex()) + random);
			}
			if (test >= 0 && test < 10) {
				walkDown(pf.getPinIndex(), -1, test);
				pf.setPinLane(pf.getPinIndex(), 3);
				pf.setPinHouse(pf.getPinIndex(), test);
			}
			if (test >= 10) {
				walkLeft(pf.getPinIndex(), -1, test - 10);
				pf.setPinLane(pf.getPinIndex(), 0);
				pf.setPinHouse(pf.getPinIndex(), test - 10);
			}
			house = pf.getPinHouse(pf.getPinIndex());
			lane = pf.getPinLane(pf.getPinIndex());
			playerNumber = pf.getPinIndex();
		} else /* Pin is on the right lane */
		{
			int test = random + pf.getPinHouse(pf.getPinIndex()) - 10;
			if (test < 0) {
				walkDown(pf.getPinIndex(), pf.getPinHouse(pf.getPinIndex()), random);
				pf.setPinHouse(pf.getPinIndex(), pf.getPinHouse(pf.getPinIndex()) + random);
			}
			if (test >= 0 && test < 10) {
				walkLeft(pf.getPinIndex(), -1, test);
				pf.setPinLane(pf.getPinIndex(), 0);
				pf.setPinHouse(pf.getPinIndex(), test);
			}
			if (test >= 10) {
				walkUp(pf.getPinIndex(), -1, test - 10);
				pf.setPinLane(pf.getPinIndex(), 1);
				pf.setPinHouse(pf.getPinIndex(), test - 10);
			}
			house = pf.getPinHouse(pf.getPinIndex());
			lane = pf.getPinLane(pf.getPinIndex());
			playerNumber = pf.getPinIndex();
		}
		
		houseNumber = lane * 10 + house;
		if (houseNumber == 30) {
			go2Prison(playerNumber);
		}

		if (combo != null)
			remove(combo);
		combo = showPlayerOwnedProperties();
		add(combo);
		
		revalidate();
		repaint();

		// Checks who's the next viable player
		getNextPlayer();

		collectTax(playerNumber, random);
		showPlayerMoney(playerNumber);
		showPropertyInfo(lane * 10 + house); //check
		Model property = p.properties.get(houseNumber);

		if ( property == null )
			blockType = 0;
		else
			blockType = property.getType();

		revalidate();
		repaint();
		
		debugDice1 = -1;
		debugDice2 = -1;

	}

	/**
	 * walkLeft makes a pinLabel walk left on the board.
	 * 
	 * @param pin       Pin number of the current playing pin.
	 * @param sameLaner Whether or not the pin will change lanes, if sameLaner < 0,
	 *                  pin will not change lanes. If sameLaner > 0, pin will change
	 *                  lanes.
	 * @param distance  How many houses the pin will move in this round.
	 * 
	 */
	private void walkLeft(int pin, int sameLaner, int distance) {
		PinFactory pf = new PinFactory(0);

//		sameLaner tells the function if the pin will move or stay on the same lane
		if (sameLaner > 0) {
			r.x = pf.getStartingX(pin) - (56 * distance) - (sameLaner * 56);
			r.y = pf.getStartingY(pin);
		} else {
			r.x = pf.getStartingX(pin) - (56 * distance);
			r.y = pf.getStartingY(pin);
		}
		players[pin].setXPosition(r.x);
		players[pin].setYPosition(r.y);
	}

	/**
	 * walkUp makes a pinLabel walk left on the board.
	 * 
	 * @param pin       Pin number of the current playing pin.
	 * @param sameLaner Whether or not the pin will change lanes, if sameLaner < 0,
	 *                  pin will not change lanes. If sameLaner > 0, pin will change
	 *                  lanes.
	 * @param distance  How many houses the pin will move in this round.
	 * 
	 */
	private void walkUp(int pin, int sameLaner, int distance) {
		PinFactory pf = new PinFactory(0);

//		sameLaner tells the function if the pin will move or stay on the same lane
		if (sameLaner > 0) {
			r.x = 10 + pin * 12;
			r.y = pf.getStartingY(0) - (58 * distance) - (58 * sameLaner);
		} else {
			r.x = 10 + pin * 12;
			r.y = pf.getStartingY(0) - (58 * distance);
		}
		players[pin].setXPosition(r.x);
		players[pin].setYPosition(r.y);
	}

	/**
	 * walkRight makes a pinLabel walk left on the board.
	 * 
	 * @param pin       Pin number of the current playing pin.
	 * @param sameLaner Whether or not the pin will change lanes, if sameLaner < 0,
	 *                  pin will not change lanes. If sameLaner > 0, pin will change
	 *                  lanes.
	 * @param distance  How many houses the pin will move in this round.
	 * 
	 */
	private void walkRight(int pin, int sameLaner, int distance) {
//		sameLaner tells the function if the pin will move or stay on the same lane
		if (sameLaner > 0) {
			r.x = 70 + (53 * distance) + (53 * sameLaner);
			r.y = 1 + pin * 12;
		} else {
			r.x = 70 + (53 * distance);
			r.y = 1 + pin * 12;
		}
		players[pin].setXPosition(r.x);
		players[pin].setYPosition(r.y);
	}

	/**
	 * walkDown makes a pinLabel walk left on the board.
	 * 
	 * @param pin       Pin number of the current playing pin.
	 * @param sameLaner Whether or not the pin will change lanes, if sameLaner < 0,
	 *                  pin will not change lanes. If sameLaner > 0, pin will change
	 *                  lanes.
	 * @param distance  How many houses the pin will move in this round.
	 * 
	 */
	private void walkDown(int pin, int sameLaner, int distance) {
		PinFactory pf = new PinFactory(0);

//		sameLaner tells the function if the pin will move but or on the same lane
		if (sameLaner > 0) {
			r.x = pf.getStartingX(0) + pin * 12;
			r.y = 30 + (58 * distance) + (58 * sameLaner);
		} else {
			r.x = pf.getStartingX(0) + pin * 12;
			r.y = 30 + (58 * distance);
		}
		players[pin].setXPosition(r.x);
		players[pin].setYPosition(r.y);
	}

	/**
	 * showPlayerMoney exhibits on screen the current player's amount of money.
	 * 
	 * @param playerNumber Pin number of the current player.
	 */
	private void showPlayerMoney(int playerNumber) {
		// Shows player current money
		if (playerMoney != null)
			remove(playerMoney);
		playerMoney = Player.Money(players, playerNumber);
		playerMoney.setBounds(790, 60, 200, 200);
		add(playerMoney);

		revalidate();
		repaint();
	}

	/**
	 * showPropertyInfo exhibits on screen information about a property.
	 * 
	 * @param houseNumber Number of the desired property to be shown.
	 */
	private void showPropertyInfo(int houseNumber) {
		// Shows property info
		if (pInfo != null)
			remove(pInfo);
		if (houseNumber > 39 || houseNumber < 0)
			houseNumber = 0;
		pInfo = Properties.propertyInfo(p.properties.get(houseNumber));
		pInfo.setBounds(775, 205, 500, 200);
		add(pInfo);

		revalidate();
		repaint();
	}
	
	/**
	 * getPropertyImage gets the house number's property card.
	 * 
	 * @param houseNumber Number of the desired property to be shown.
	 * @param property_type Type of the property. (1, 2, 3, 4 or 5)
	 * @return the property's buffered image.
	 */
	private BufferedImage getPropertyImage(int houseNumber, int property_type)
	{
		if (houseNumber > 39 || houseNumber < 0)
			houseNumber = 0;
		
		if ( property_type == 3 && !used ) {
			pCard = lucky.propertyCard();
			used = true;
			tmp = pCard;
		} else if ( property_type == 3 && used )
			pCard = tmp;
		else
			pCard = Properties.propertyCard(p.properties.get(houseNumber));
		
		if ( property_type == 0 )
			pCard = null;
		
		return pCard;		
	}

	/**
	 * collectTax Calculates and collect taxes when a player lands on an owned
	 * property.
	 * 
	 * @param playerNumber Pin number of the current player.
	 * @param diceRoll     Sum of the numbers rolled on the dice.
	 */
	private void collectTax(int playerNumber, int diceRoll) {
		int houseNumber = lane * 10 + house;
		Model property = p.properties.get(houseNumber);
		String taxPlayer = "";
		float tax = 0;
		float preTax = players[playerNumber].getMoney();

		if (houseNumber > 39 || houseNumber < 0) {
			houseNumber = 0;
			property = p.properties.get(houseNumber);
		}

		if (property.getType() == 1) { // Street property
			if (property.getOwner() != -1) {
				if (property.getHouses() > 0) {
					tax = property.getRent(property.getHouses());
				}
				if (property.getHotels() > 0) {
					tax = tax + property.getRent(5);
				}
				if ( property.getHouses() == 0 && property.getHotels() == 0 ) {
					tax = property.getRent(0);
				}
				players[playerNumber].setMoney(players[playerNumber].getMoney() - tax);
			}
		} else if (property.getType() == 2) { // Company property
			if (property.getOwner() != -1) {
				tax = property.getRent(0) * diceRoll;
				players[playerNumber].setMoney(players[playerNumber].getMoney() - tax);
			}
		} else if (property.getType() == 3) { // Sorte-ou-Revés property
			int val = lucky.getValue();
			if(val == 111)
			{
				players[playerNumber].setPrisonPass(true);
			}
			else if(val == 201)
			{
				players[playerNumber].setMoney(players[playerNumber].getMoney() + 200);
				//go2beggining()
			}
			else if(val == 555)
			{
				for(int i = 0; i < numberOfPlayers; i++)
				{
					if(i == playerNumber)
						continue;
					
					players[i].setMoney(players[i].getMoney() -50);
					players[playerNumber].setMoney(players[playerNumber].getMoney() + 50);
				}
			}
			else if(val == -111)
			{
				go2Prison(playerNumber);
				players[playerNumber].setinPrison(true);
			}
			else
			{
				tax = - val;
				players[playerNumber].setMoney( players[playerNumber].getMoney() - tax);
				tax = - tax;
			}
		} else if (property.getType() == 4) { // Get or Lose money - "$" and "$$"
			tax = property.getPrice();
			players[playerNumber].setMoney(players[playerNumber].getMoney() + tax);
		} else if (property.getType() == 0 && houseNumber == 0) { // Ponto de partida - get $: 200.00.
			tax = 200;
			players[playerNumber].setMoney(players[playerNumber].getMoney() + tax);
		} else // Jail
			return;
		
		// Player went bankrupt
		if (players[playerNumber].getMoney() < 0) {
			
			int numberOfProperties = 0;
			// Verify if the player has any properties to sell
			for ( int i = 0; i < 40; i++ ) {
				if( p.properties.get(i).getOwner() == players[playerNumber].getIndex()+1 ) { //Player owns a property
					numberOfProperties++;
				}	
			}
			
			if ( numberOfProperties > 0 ) {	// Player has properties to sell.
				if (tax < 0 )
					tax = tax * -1;
				String message = String.format("<html>Você está devendo $: %.2f!<br/>Venda suas propriedades até ter um saldo positivo.</html>", tax);
				JOptionPane.showMessageDialog(null, message, "Alerta", JOptionPane.WARNING_MESSAGE);
				
				if (property.getType() != 4) {  // Verifies if it isn't Get / Lose money - "$" and "$$" house, which has no owner.
					String receiveTaxPlayer = "";
					if (property.getOwner() == 0) {
						receiveTaxPlayer = "<font color=\"red\">Vermelho</font>";
					} else if (property.getOwner() == 1) {
						receiveTaxPlayer = "<font color=\"blue\">Azul</font>";
					} else if (property.getOwner() == 2) {
						receiveTaxPlayer = "<font color=\"orange\">Laranja</font>";
					} else if (property.getOwner() == 3) {
						receiveTaxPlayer = "<font color=\"yellow\">Amarelo</font>";
					} else if (property.getOwner() == 4) {
						receiveTaxPlayer = "<font color=\"purple\">Roxo</font>";
					} else if (property.getOwner() == 5) {
						receiveTaxPlayer = "<font color=\"grey\">Cinza</font>";
					}
					
					String text2 = String.format("<html>%s ganhou dinheiro essa rodada, total: $: %s.</html>", receiveTaxPlayer, Math.abs(preTax));
					JOptionPane.showMessageDialog(null, text2, "Tax", JOptionPane.INFORMATION_MESSAGE);
					players[property.getOwner()].setMoney(players[property.getOwner()].getMoney() + preTax);
				}
				
				return;
			}
			
			if (playerNumber == 0) {
				taxPlayer = "<font color=\"red\">Vermelho</font>";
			} else if (playerNumber == 1) {
				taxPlayer = "<font color=\"blue\">Azul</font>";
			} else if (playerNumber == 2) {
				taxPlayer = "<font color=\"orange\">Laranja</font>";
			} else if (playerNumber == 3) {
				taxPlayer = "<font color=\"yellow\">Amarelo</font>";
			} else if (playerNumber == 4) {
				taxPlayer = "<font color=\"purple\">Roxo</font>";
			} else if (playerNumber == 5) {
				taxPlayer = "<font color=\"grey\">Cinza</font>";
			}
			
			String text = String.format("<html>O jogador %s foi a falencia!</html>", taxPlayer);
			JOptionPane.showMessageDialog(null, text, "Alerta", JOptionPane.INFORMATION_MESSAGE);
			
			if (property.getType() != 4) {  // Verifies if it isn't Get / Lose money - "$" and "$$" house, which has no owner.
				String receiveTaxPlayer = "";
				if (property.getOwner() == 0) {
					receiveTaxPlayer = "<font color=\"red\">Vermelho</font>";
				} else if (property.getOwner() == 1) {
					receiveTaxPlayer = "<font color=\"blue\">Azul</font>";
				} else if (property.getOwner() == 2) {
					receiveTaxPlayer = "<font color=\"orange\">Laranja</font>";
				} else if (property.getOwner() == 3) {
					receiveTaxPlayer = "<font color=\"yellow\">Amarelo</font>";
				} else if (property.getOwner() == 4) {
					receiveTaxPlayer = "<font color=\"purple\">Roxo</font>";
				} else if (property.getOwner() == 5) {
					receiveTaxPlayer = "<font color=\"grey\">Cinza</font>";
				}
				
				String text2 = String.format("<html>%s ganhou dinheiro essa rodada, total: $: %s.</html>", receiveTaxPlayer, Math.abs(preTax));
				JOptionPane.showMessageDialog(null, text2, "Tax", JOptionPane.INFORMATION_MESSAGE);
				players[property.getOwner()].setMoney(players[property.getOwner()].getMoney() + preTax);
			}
			
			players[playerNumber].setOut(true);
			players[playerNumber].setXPosition(1000);
			players[playerNumber].setYPosition(1000);
			
			endGameCheck();
			
			revalidate();
			repaint();
				
			return;
		} else {
			if (property.getOwner() != -1) // Verifies if the property has an owner.
				players[property.getOwner()].setMoney(players[property.getOwner()].getMoney() + tax);
		}
		
		if ( tax > 0  || property.getOwner() != -1) { // Player actually received any money
			String receiveTaxPlayer = "";
			if (property.getOwner() == 0) {
				receiveTaxPlayer = "<font color=\"red\">Vermelho</font>";
			} else if (property.getOwner() == 1) {
				receiveTaxPlayer = "<font color=\"blue\">Azul</font>";
			} else if (property.getOwner() == 2) {
				receiveTaxPlayer = "<font color=\"orange\">Laranja</font>";
			} else if (property.getOwner() == 3) {
				receiveTaxPlayer = "<font color=\"yellow\">Amarelo</font>";
			} else if (property.getOwner() == 4) {
				receiveTaxPlayer = "<font color=\"purple\">Roxo</font>";
			} else if (property.getOwner() == 5){
				receiveTaxPlayer = "<font color=\"grey\">Cinza</font>";
			} else {
				if (playerNumber == 0) {
					receiveTaxPlayer = "<font color=\"red\">Vermelho</font>";
				} else if (playerNumber == 1) {
					receiveTaxPlayer = "<font color=\"blue\">Azul</font>";
				} else if (playerNumber == 2) {
					receiveTaxPlayer = "<font color=\"orange\">Laranja</font>";
				} else if (playerNumber == 3) {
					receiveTaxPlayer = "<font color=\"yellow\">Amarelo</font>";
				} else if (playerNumber == 4) {
					receiveTaxPlayer = "<font color=\"purple\">Roxo</font>";
				} else if (playerNumber == 5){
					receiveTaxPlayer = "<font color=\"grey\">Cinza</font>";
				}
			}
			
			String text = String.format("<html>%s ganhou dinheiro essa rodada, total: $: %s.</html>", receiveTaxPlayer, Math.abs(tax));
			JOptionPane.showMessageDialog(null, text, "Tax", JOptionPane.INFORMATION_MESSAGE);
		}
		
		endGameCheck();
		showPlayerMoney(playerNumber);
		showPropertyInfo(houseNumber);

		revalidate();
		repaint();
	}

	/**
	 * go2Prison sends the player to prison if he lands on "go to prison".
	 * 
	 * @param pin Pin number of the current player.
	 */
	private void go2Prison(int pin) {
		String pinString;
		
		//check if player has a get out of jail card
		if(players[pin].hasPrisonPass()) {
			players[pin].setPrisonPass(false);
			return;
		}
	
		r.x = 10 + pin * 12;
		r.y = 605 + pin * 12;

		players[pin].setinPrison(true);
		pf.setPinLane(pf.getPinIndex(), 1);
		pf.setPinHouse(pf.getPinIndex(), 0);
		
		players[pin].setXPosition(r.x);
		players[pin].setYPosition(r.y);

		if (pin == 0) {
			pinString = "<font color=\"red\">Vermelho</font>";
		} else if (pin == 1) {
			pinString = "<font color=\"blue\">Azul</font>";
		} else if (pin == 2) {
			pinString = "<font color=\"orange\">Laranja</font>";
		} else if (pin == 3) {
			pinString = "<font color=\"yellow\">Amarelo</font>";
		} else if (pin == 4) {
			pinString = "<font color=\"purple\">Roxo</font>";
		} else {
			pinString = "<font color=\"grey\">Cinza</font>";
		}

		revalidate();
		repaint();
		
		String text = String.format("<html>O %s caiu em \"Vá para a prisão\"!</html>", pinString);
		JOptionPane.showMessageDialog(null, text, "Prisão!", JOptionPane.PLAIN_MESSAGE);
	}

	/**
	 * endGameCheck Ends the game if there's only one player left in the game.
	 */
	private void endGameCheck() {
		String winnerString;
		int winnerInt = 0;
		if (players[playerNumber].isOut())
			activePlayers--;

		if (activePlayers == 1) { // There's only one player left, thus we ourselves have a winner!
			for (int i = 0; i < numberOfPlayers; i++) {
				if (!players[playerNumber].isOut()) {
					winnerInt = playerNumber;
					System.out.println(players[playerNumber].isOut());
				}
			}

			if (winnerInt == 0) {
				winnerString = "<font color=\"red\">Vermelho</font>";
			} else if (winnerInt == 1) {
				winnerString = "<font color=\"blue\">Azul</font>";
			} else if (winnerInt == 2) {
				winnerString = "<font color=\"orange\">Laranja</font>";
			} else if (winnerInt == 3) {
				winnerString = "<font color=\"yellow\">Amarelo</font>";
			} else if (winnerInt == 4) {
				winnerString = "<font color=\"purple\">Roxo</font>";
			} else {
				winnerString = "<font color=\"grey\">Cinza</font>";
			}

			String text = String.format("<html>O vencedor é o: %s</html>", winnerString);
			JOptionPane.showMessageDialog(null, text, "Parabéns!", JOptionPane.PLAIN_MESSAGE);
			System.exit(0);
		}
	}

	/**
	 * getNextPlayer gets the next available player.
	 */
	private void getNextPlayer() {
		int i = 0;
		int j = pf.getPinIndex();
		while (i >= 0) {
			if (j >= (numberOfPlayers - 1)) {
				j = -1;
			}
			if (!players[j + 1].isOut()) {
				pf.setPinIndex(j + 1);
				i = -1;
			} else {
				j++;
			}
		}
	}

	/*
	 * setPositions puts the pins on their respective positions when loading a saved game.
	 */
	private void setPositions() {
		for (int i = 0; i <= n[1]; i++)
			pf.incrementPinIndex();
		
		pf.setPinIndex(pf.getPinIndex()-1);

		revalidate();
		repaint();
	}

	/**
	 * checkBankrupcy checks if a player went bankrupt.
	 */
	private void checkBankrupcy() {
		int numberOfProperties = 0;
		String playerString;
		if ( players[playerNumber].getMoney() < 0 ) {
			for (int i = 0; i < 40; i++ ) {
				if( p.properties.get(i).getOwner() == players[playerNumber].getIndex() ) { //Player owns a property
					numberOfProperties++;
				}
			}
			if ( numberOfProperties > 0 ) {
				String text = String.format("<html>Você ainda deve $: %.2f!<br/>Venda mais propriedades</html>", players[playerNumber].getMoney());
				JOptionPane.showMessageDialog(null, text, "Alerta!", JOptionPane.WARNING_MESSAGE);
			} else { // Player went bankrupt.
				
				if (playerNumber == 0) {
					playerString = "<font color=\"red\">Vermelho</font>";
				} else if (playerNumber == 1) {
					playerString = "<font color=\"blue\">Azul</font>";
				} else if (playerNumber == 2) {
					playerString = "<font color=\"orange\">Laranja</font>";
				} else if (playerNumber == 3) {
					playerString = "<font color=\"yellow\">Amarelo</font>";
				} else if (playerNumber == 4) {
					playerString = "<font color=\"purple\">Roxo</font>";
				} else {
					playerString = "<font color=\"grey\">Cinza</font>";
				}
				
				String text = String.format("<html>O jogador %s foi a falencia!</html>", playerString);
				JOptionPane.showMessageDialog(null, text, "Alerta", JOptionPane.INFORMATION_MESSAGE);
				
				players[playerNumber].setOut(true);
				players[playerNumber].setXPosition(1000);
				players[playerNumber].setYPosition(1000);
				
				revalidate();
				repaint();
			}
		}
		endGameCheck();
	}
}
