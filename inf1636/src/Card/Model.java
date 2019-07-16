package Card;

import java.awt.image.BufferedImage;


/**
 * Creates the Model class to hold all the information relative to a property.
 * Model property = new Model(type, price, ownerId, housesBuilt, housePrice,
 * hotelsBuilt, hotelPrice, hipoteca, rentNoHouses, rentOneHouse, rentTwoHouses,
 * rentThreeHouses, rentFourHouses, rentOneHotel, propertyName, cardJLabel)
 * 
 * @examples Model property = new Model(0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 *           0,"Ponto de Partida", null) Model property = new Model(1, 220, -1,
 *           0, 150, 0, 150, 110, 18, 90, 250, 700, 875, 1050, "Av. 9 de julho",
 *           cardLabels[7])
 * 
 * @typeExamples: 0 - "Ponto de Partida", "Parada Livre" 1 - "Streets" 2 -
 *                "Companies" 3 - "Lucky Space 'Sorte ou Revés' - "?"" 4 - "Get
 *                / Lose money - "$" and "$$"" 5 - "Jail"
 * 
 */
public class Model {
	private int index;
	private int type;
	private float price;
	private int owner;
	private int houses;
	private float housePrice;
	private int hotels;
	private float hotelPrice;
	private float hipoteca;
	private float rent[] = new float[6];
	private String name;
	private BufferedImage card;

	public Model(int index, int type, float price, int owner, int houses, float housePrice, int hotels, float hotelPrice,
			float hipoteca, float noHouses, float oneHouse, float twoHouses, float threeHouses, float fourHouses,
			float oneHotel, String name, BufferedImage card) {
		this.index = index;
		this.type = type;
		this.price = price;
		this.owner = owner;
		this.houses = houses;
		this.housePrice = housePrice;
		this.hotels = hotels;
		this.hotelPrice = hotelPrice;
		this.hipoteca = hipoteca;
		this.rent[0] = noHouses;
		this.rent[1] = oneHouse;
		this.rent[2] = twoHouses;
		this.rent[3] = threeHouses;
		this.rent[4] = fourHouses;
		this.rent[5] = oneHotel;
		this.name = name;
		this.card = card;
	}

	public Model() {

	}
	
	/**
	 * getIndex gets propery's index
	 * 
	 * @return the property's index;
	 */
	public int getIndex() {
		return this.index;
	}
	
	/**
	 * getType gets the property type.
	 * 
	 * @return the property type.
	 */
	public int getType() {
		return this.type;
	}
	
	/**
	 * getPrice gets the property's price.
	 * 
	 * @return the property's price.
	 */
	public float getPrice() {
		return this.price;
	}
	
	/**
	 * getOwner gets the property's owner.
	 * 
	 * @return the property's owner.
	 */
	public int getOwner() {
		return this.owner;
	}
	
	/**
	 * getHouses gets the number of houses in the current property.
	 * 
	 * @return the number of houses in the current property.
	 */
	public int getHouses() {
		return this.houses;
	}
	
	/**
	 * getHousePrice gets house price in the current property.
	 * 
	 * @return the house price in the current property.
	 */
	public float getHousePrice() {
		return this.housePrice;
	}
	
	/**
	 * getHotels gets the number of hotels in the current property.
	 * 
	 * @return the number of hotels in the current property.
	 */
	public int getHotels() {
		return this.hotels;
	}
	
	/**
	 * getHotelPrice gets the hotel price in the current property.
	 * 
	 * @return the hotel price in the current property.
	 */
	public float getHotelPrice() {
		return this.hotelPrice;
	}
	
	/**
	 * getHipoteca gets the price of hipoteca.
	 * 
	 * @return the hipoteca price.
	 */
	public float getHipoteca() {
		return this.hipoteca;
	}
	
	/**
	 * getRent gets the rent according to the number of built houses / hotels.
	 * 
	 * @param option	1 - no houses, 2 - one house, 3 - two houses ...
	 * @return	the rent to be payed.
	 */
	public float getRent(int option) {
		return this.rent[option];
	}
	
	/**
	 * getName gets a property's name.
	 * 
	 * @return a property's name.
	 */
	public String getName() {
		return this.name;
	}
	
	/**
	 * getImage gets a card's image.
	 * 
	 * @return the cards buffered image.
	 */
	public BufferedImage getImage() {
		return this.card;
	}
	
	/**
	 * setOwner sets a new owner to the current property.
	 * 
	 * @param newOwner to be set.
	 */
	public void setOwner(int newOwner) {
		this.owner = newOwner;
	}
	
	/**
	 * incrementHouses increments the number of houses of the current property by 1.
	 */
	public void incrementHouses() {
		this.houses++;
	}
	
	/**
	 * incrementHotels increments the number of hotels of the current property by 1.
	 */
	public void incrementHotels() {
		this.hotels++;
	}
	
	/**
	 * setHouses sets a new number of houses in the property.
	 * 
	 * @param numberOfHouses to be set.
	 */
	public void setHouses(int numberOfHouses) {
		this.houses = numberOfHouses;
	}
	
	/**
	 * setHotels sets a new number of hotels in the property.
	 * 
	 * @param numberOfHotels to be set.
	 */
	public void setHotels(int numberOfHotels) {
		this.hotels = numberOfHotels;
	}
}
