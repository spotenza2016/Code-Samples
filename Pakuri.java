//Class to hold information of every Pakuri.
public class Pakuri {
    //Declares variables to hold the species name, attack, and defense of every Pakuri.
    private String species;
    private int attack;
    private int defense;
    private int speed;

    //Constructor that gives default attack, defense, and speed based on given name.
    public Pakuri(String species) {
        //Sets the species name to the given name.
        this.species = species;

        //Calculates the stats based on the number of characters in the name.
        attack = (this.species.length() * 7) + 9;
        defense = (this.species.length() * 5) + 17;
        speed = (this.species.length() * 6) + 13;
    }

    //Accessor method to give the species name.
    public String getSpecies() {
        return species;
    }

    //Accessor method to give the attack statistic.
    public int getAttack() {
        return attack;
    }

    //Accessor method to give the defense statistic.
    public int getDefense() {
        return defense;
    }

    //Accessor method to give the speed statistic.
    public int getSpeed() {
        return speed;
    }

    //Mutator method to change the attack statistic.
    public void setAttack(int newAttack) {
        attack = newAttack;
    }

    //Method to evolve the Pakuri, multiplying the stats by 2, 4, and 3 respectively.
    public void evolve() {
        attack *= 2;
        defense *= 4;
        speed *= 3;
    }
}
