import java.awt.Dimension;
import java.awt.Toolkit;

import javax.swing.JFrame;

import GameComponents.GameComponents;

/**
 * 
 * Creates a MainWindow class, responsible for initializing a new visualization
 * window.
 *
 * @example MainWindow MW = new MainWindow(); MW.display();
 * 
 */
public class MainWindow extends JFrame {
	private static final long serialVersionUID = 1L;
	public final int LARG_DEFAULT = 1000;
	public final int ALT_DEFAULT = 739;

	private GameComponents GC = new GameComponents();

	public MainWindow() {
		setTitle("Banco Imobiliário");
		Toolkit tk = Toolkit.getDefaultToolkit();
		Dimension screenSize = tk.getScreenSize();
		int sl = screenSize.width;
		int sa = screenSize.height;
		int x = sl / 2 - LARG_DEFAULT / 2;
		int y = sa / 2 - ALT_DEFAULT / 2;
		setBounds(x, y, LARG_DEFAULT, ALT_DEFAULT);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		getContentPane().add(GC);
	}

	public void display() {
		setVisible(true);
	}
}
