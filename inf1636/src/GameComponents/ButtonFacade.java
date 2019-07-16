package GameComponents;

import javax.swing.JButton;

public class ButtonFacade {
	
	public static void addButtons(GameComponents gc, JButton diceButton, JButton buyHotelButton, JButton buyHouseButton,JButton buyPropertyButton,
			JButton endGameButton, JButton saveGameButton, JButton sellPropertyButton, JButton debugButton)
	{
		gc.add(diceButton);
		gc.add(buyHotelButton);
		gc.add(buyHouseButton);
		gc.add(buyPropertyButton);
		gc.add(endGameButton);
		gc.add(saveGameButton);
		gc.add(sellPropertyButton);
		gc.add(debugButton);
	}
}
