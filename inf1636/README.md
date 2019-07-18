# Object Oriented Programming - Inf 1636 🕹

In this class me and my partner were given the task of creating a digital version of the popular game Monopoly (Banco Imobiliário in portuguese).

The main goal of creating a digital version of this game was to exercise the object oriented programming concepts seen in class, such as **classes**, **constructors**, **inheritance** and many others.

## Running the game

Simply double click `BancoImobiliário.jar` and the game should launch right away, if you have Java on your machine. If you don't already have Java, you can find instructions on how to install it [here](https://www.java.com/pt_BR/download/).

When the game launches, you'll be prompted to select a save file if you desire to. Otherwise, you can simply `cancel` and a new game will begin, as we can see from the image below:

<img src="Images/choose_save.png" allign="center"/>

When starting a new game, the next thing you need to do is choose how many players will play, as shown by the image below:

<img src="Images/choose_players.png" allign="center"/>

Finally, we get to the board:

<img src="Images/board.png" allign="center"/>

## Saving your game

If you want to save your current game, so you can get back to it later, simply click `Salvar o Jogo`.

After pressing the button, you'll be prompted to name your save, just keep in mind that the save file must be a `.txt`, so don't forget to add the extension! We can see an example of that in the image below:

<img src="Images/save_game.png" allign="center"/>

If the game saves successfully, you'll get a message such as that:

<img src="Images/confirm_save.png" allign="center"/>

The save file generated is in a JSON format and in plain text, which allows for anyone to alter the values. In order to know if the save file has been modified, the game signs all the information on it with it's private key, so when it's loaded there's a way to tell if someone might be cheating! 🧐

An example of a save file is as follows:

<img src="Images/save_file.png" allign="center"/>