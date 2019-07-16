package Card;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;

import javax.imageio.ImageIO;

public class Luck {
	private Queue<Integer> values = new LinkedList<>();
	private Queue<BufferedImage> cards = new LinkedList<>(); 
	private Queue<Integer> indexOrder = new LinkedList<>(); 
	
	//Singleton
	private static Luck singleton = null;
	
	private Luck() {
		loadCards();
		fillProperties();
		shuffleDeck();
	}
	
	
	private Luck(Queue<Integer> order)
	{
		fillProperties();
		int []arr = new int[31];
		int n = values.size();
		for(int i = 0; i < n; i++)
		{
			arr[i] = values.remove();
		}
		String srcImage = "src/Imagens-01/sorteReves/chance";
		n = order.size();
		for(int i = 0; i < n; i++)
		{
			try {
				int index = order.remove();
				BufferedImage c = ImageIO.read(new File( srcImage + index + ".png" ));
				cards.add(c);
				indexOrder.add(index);
				values.add(arr[index-1]);
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	
	public static Luck getInstance()
	{
		if(singleton == null)
			singleton = new Luck();
		
		return singleton;
	}
	
	public static Luck getInstance(Queue<Integer> order)
	{
		if(singleton == null)
			singleton = new Luck(order);
		
		return singleton;
	}
	
	public void shuffleDeck()
	{
		for(int i = 0; i < 1000; i++)
		{
			int random = (int)(30.0 * Math.random());
			Stack<BufferedImage> stackCard = new Stack<BufferedImage>();
			Stack<Integer> stackValues = new Stack<Integer>();
			Stack<Integer> stackIndexOrder = new Stack<Integer>();
			while(random >= 0)
			{
				stackCard.add(cards.remove());
				stackValues.add(values.remove());
				stackIndexOrder.add(indexOrder.remove());
				random--;
			}
			while(!stackCard.empty())
			{
				cards.add(stackCard.pop());
				values.add(stackValues.pop());
				indexOrder.add(stackIndexOrder.pop());
			}
		}
	}


	public BufferedImage propertyCard() {
		int tempVal = values.remove();
		BufferedImage c = cards.remove();
		int tempIndex = indexOrder.remove();
		
		cards.add(c);
		values.add(tempVal);
		indexOrder.add(tempIndex);
		return c;
	}

	private void loadCards() {
		String srcImage = "src/Imagens-01/sorteReves/chance";
		try {
			for(int i = 1; i < 31; i++)
			{
				BufferedImage c = ImageIO.read(new File( srcImage + i + ".png" ));
				cards.add(c);
				indexOrder.add(i);
			}
		} catch (IOException e) {
			System.out.println(e.getMessage());
			System.exit(1);
		}
	}

	private void fillProperties() {
		values.add(25);
		values.add(150);
		values.add(80);
		values.add(200);
		values.add(50);
		values.add(50);
		values.add(100);
		values.add(100);
		values.add(111); // saida livre da prisao
		values.add(201); // tem que ir até o ponto de partida
		values.add(555); // receber 50 de cada jogador
		values.add(45);
		values.add(100);
		values.add(100);
		values.add(20);
		values.add(-15);
		values.add(-25);
		values.add(-45);
		values.add(-30);
		values.add(-100);
		values.add(-100);
		values.add(-40);
		values.add(-111); // vá para a prisão
		values.add(-30);
		values.add(-50);
		values.add(-25);
		values.add(-30);
		values.add(-45);
		values.add(-50);
		values.add(-50);
	}
	
	public int getValue()
	{
		return values.element();
	}
	
	public Queue<Integer> getIndexOrder()
	{		
		return indexOrder;
	}
}
