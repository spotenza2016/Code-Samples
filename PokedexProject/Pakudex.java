//Class to hold list of Pakuri.
public class Pakudex {
    //Declares a private variable to hold the list of Pakuri.
    private Pakuri[] pakudex;

    //Default constructor gives it 20 capacity.
    public Pakudex() {
        pakudex = new Pakuri[20];
    }

    //If a capacity is give, uses it to make the object.
    public Pakudex(int capacity) {
        pakudex = new Pakuri[capacity];
    }

    //Accessor method to give the number of slots in the Pakudex that are filled.
    public int getSize() {
        //Local variable to hold the current size.
        int size = 0;

        //For every element in the pakudex, checks if it is filled.
        for (int i = 0; i < pakudex.length; i++) {
            //If it is filled, adds 1 to the size.
            if (pakudex[i] != null) {
                size += 1;
            }
        }

        //Once is finishes counting, returns the size.
        return size;
    }

    //Accessor method to give the Pakudex length.
    public int getCapacity() {
        return pakudex.length;
    }

    //Accessor method to give an array of all the species names.
    public String[] getSpeciesArray() {
        //Local variable to hold the size using getSize().
        int size = getSize();

        //If at least one element is filled, returns a string array.
        if (size > 0) {
            //Declares a new string array using the size.
            String[] species = new String[size];

            //For every filled element in the Pakudex, adds it to the string array.
            for (int i = 0; i < getSize(); i++) {
                    species[i] = pakudex[i].getSpecies();
            }

            //Returns the string array.
            return species;
        }
        //Otherwise, returns null.
        else {
            return null;
        }
    }

    //Accessor method to give the stats of a given Pakuri.
    public int[] getStats(String species) {
        //Declares a int array to hold the stats.
        int[] stats = new int[3];

        //For every filled element, if it is the given Pakuri gets its stats.
        for (int i = 0; i < getSize(); i++) {
                //If the species name matches, puts the Attack, Defense, and Speed in the int array using the Accessor methods.
                if (pakudex[i].getSpecies().equals(species)) {
                    stats[0] = pakudex[i].getAttack();
                    stats[1] = pakudex[i].getDefense();
                    stats[2] = pakudex[i].getSpeed();

                    //Returns the int array.
                    return stats;
            }
        }

        //If there were no matches, return null.
        return null;
    }

    //Method to sort the list alphabetically.
    public void sortPakuri() {
        //Declares a variable to hold the currently being sorted element.
        Pakuri current_pakuri;

        //i represents the element currently being sorted, starting with the second.
        for (int i = 1; i < getSize(); i++) {
            //Stores the current element in the variable.
            current_pakuri = pakudex[i];

            //j represents the number of previous elements to compare to.
            for (int j = 0; j < i; j++) {
                //Using String.compareToIgnoreCase(), checks if the sorted element is lexicographically earlier than the current j element.
                    //Learned how to do this at https://docs.oracle.com/javase/7/docs/api/java/lang/String.html.
                if (current_pakuri.getSpecies().compareToIgnoreCase(pakudex[j].getSpecies()) <= 0) {
                    //If so, k represents each element in between the sorted element and j, moving them to the right to make room for the sorted elements new spot.
                    for (int k = i; k > j; k--) {
                        pakudex[k] = pakudex[k - 1];
                    }

                    //Places the sorted element in its new spot.
                    pakudex[j] = current_pakuri;

                    //Breaks from the j for loop, continuing onto the next sorted element.
                    break;
                }
            }
        }
    }

    //Mutator method to add Pakuri.
    public boolean addPakuri (String species) {
        //Uses getSize() and getCapacity() to get the size and capacity.
        int size = getSize();
        int capacity = getCapacity();

        //If the Pakudex isn't filled and the species has no stats using getStats() (meaning it exists in the array), creates a new Pakuri with the given species name.
        if (size < capacity && getStats(species) == null) {
            //Uses the size to add the Pakuri at the appropriate element.
            pakudex[size] = new Pakuri(species);

            //Returns true showing it added successfully.
            return true;
        }
        //Otherwise, returns false showing that it is either at capacity of it is already in the array.
        else {
            return false;
        }
    }

    //Method to evolve a Pakuri.
    public boolean evolveSpecies(String species) {
        //For every filled element, checks if it is the desired Pakuri.
        for (int i = 0; i < getSize(); i++) {
            //If it is the desired Pakuri, uses Pakuri.evolve() to evolve it.
            if (pakudex[i].getSpecies().equals(species)) {
                pakudex[i].evolve();

                //Returns true as a confirmation message.
                return true;
            }
        }

        //If no matches were returned, returns false showing the Pakuri is not in the Pakudex.
        return false;
    }
}
