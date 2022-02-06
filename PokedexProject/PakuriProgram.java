//Imports the needed libraries.
import java.util.Scanner;

//Main Method Class.
public class PakuriProgram {
    //Main Method.
    public static void main(String[] args) {
        //Declares variables to tell the program to keep running certain while loops.
        boolean getting_capacity = true;
        boolean running_program = true;

        //Declares a variable to hold an input scanner to grab the user's inputs.
        Scanner input_scanner = new Scanner(System.in);

        //Declares a variable to hold the Pakudex and the capacity of that Pakudex.
        Pakudex pakudex;
        int capacity = 0;

        //Declares a variable to hold the currently selected menu option.
        int menu_selection;


        //Declares variables to hold a Pakuri string array, the species name, and a stats array.
        String[] pakudex_strings;
        String species;
        int[] stats;

        //Prints a welcome message.
        System.out.println("Welcome to Pakudex: Tracker Extraordinaire!");

        //Continues asking for the capacity until the user gives a valid capacity.
        while (getting_capacity) {
            //Try Block to find errors in the given capacity.
            try {
                //Asks for a capacity and stores it in the input scanner.
                System.out.print("Enter max capacity of the Pakudex: ");
                capacity = input_scanner.nextInt();
            }
            //Catch Block if the given capacity is not an int.
            catch (Exception exception) {
                //Clears the input scanner.
                input_scanner.next();

                //Prints an error message.
                System.out.println("Please enter a valid size.");

                //Continues to the next while loop iteration.
                continue;
            }

            //If the capacity stores correctly, checks if the capacity is higher than 0.
            if (capacity > 0) {
                //If so, tells the program to stop getting capacity.
                getting_capacity = false;
            }
            else {
                //Otherwise, prints an error message.
                System.out.println("Please enter a valid size.");
            }
        }

        //Creates a new Pakudex object of size according to capacity, stores it in a variable.
        pakudex = new Pakudex(capacity);

        //Tells the user the selected capacity.
        System.out.println("The Pakudex can hold " + capacity + " species of Pakuri.");

        //Continues printing a menu while the user runs the program.
        while (running_program) {
            //Prints the menu.
            System.out.println("\n" + "Pakudex Main Menu");
            System.out.println("-----------------");
            System.out.println("1. List Pakuri");
            System.out.println("2. Show Pakuri");
            System.out.println("3. Add Pakuri");
            System.out.println("4. Evolve Pakuri");
            System.out.println("5. Sort Pakuri");
            System.out.println("6. Exit" + "\n");

            //Try Block to make sure the given menu option is valid.
            try {
                //Asks for the user's desired menu option, storing it in a variable.
                System.out.print("What would you like to do? ");
                menu_selection = input_scanner.nextInt();
            }
            //Catch Block if the given menu option isn't an int.
            catch (Exception exception) {
                //Clears the scanner.
                input_scanner.next();

                //Prints an error message.
                System.out.println("Unrecognized menu selection!");

                //Continues to the next while loop iteration.
                continue;
            }

            //If the menu option stores correctly, picks what to do based on it.
            switch (menu_selection) {
                //If 1, lists the current Pakuri in the Pakudex.
                case 1:
                    //Grabs an array of the species in the Pakudex using Pakudex.getSpeciesArray().
                    pakudex_strings = pakudex.getSpeciesArray();

                    //If the array isn't null, prints the species names.
                    if (pakudex_strings != null) {
                        //Title.
                        System.out.println("Pakuri In Pakudex:");

                        //For every string, places them in a numbered list.
                        for (int i = 0; i < pakudex_strings.length; i++) {
                            System.out.println((i + 1) + ". " + pakudex_strings[i]);
                        }
                    }
                    //Otherwise, prints an error message.
                    else {
                        System.out.println("No Pakuri in Pakudex yet!");
                    }

                    break;

                //If 2, lists the stats of the desired Pakuri.
                case 2:
                    //Asks for the desired Pakuri, storing it in a variable.
                    System.out.print("Enter the name of the species to display: ");
                    species = input_scanner.next();

                    //Gets the stats of the species using Pakudex.getStats().
                    stats = pakudex.getStats(species);

                    //If the stats are not null, prints them out.
                    if (stats != null) {
                        System.out.println("Species: " + species);
                        System.out.println("Attack: " + stats[0]);
                        System.out.println("Defense: " + stats[1]);
                        System.out.println("Speed: " + stats[2]);
                    }
                    //Otherwise, gives an error message.
                    else {
                        System.out.println("Error: No such Pakuri!");
                    }

                    break;

                //If 3, adds the desired Pakuri.
                case 3:
                    //Checks if the Pakudex is filled using Pakudex.getSize() and Pakudex.getCapacity(), printing an error message if so.
                    if (pakudex.getSize() >= pakudex.getCapacity()) {
                        System.out.println("Error: Pakudex is full!");
                    }
                    //Otherwise, attempts to add the Pakuri.
                    else {
                        //Grabs the species name, storing it an a variable.
                        System.out.print("Enter the name of the species to add: ");
                        species = input_scanner.next();

                        //If added successfully using Pakudex.addPakuri(), prints a success message.
                        if (pakudex.addPakuri(species)) {
                            System.out.println("Pakuri species " + species + " successfully added!");
                        }
                        //Otherwise, this means the Pakudex already contains this species and therefore prints an error message.
                        else {
                            System.out.println("Error: Pakudex already contains this species!");
                        }
                    }

                    break;

                //If 4, attempts to evolve the Pakuri.
                case 4:
                    //Grabs the name of the Pakuri, storing it in a variable.
                    System.out.print("Enter the name of the species to evolve: ");
                    species = input_scanner.next();

                    //If the Pakuri evolves successfully using Pakudex.evolveSpecies(), prints a success message.
                    if (pakudex.evolveSpecies(species)) {
                        System.out.println(species + " has evolved!");
                    }
                    //Otherwise, this means there is no such Pakuri and therefore prints an error message.
                    else {
                        System.out.println("Error: No such Pakuri!");
                    }

                    break;

                //If 5, sorts the current list.
                case 5:
                    //Uses Pakudex.sortPakuri() to sort the current list, printing a confirmation message.
                    pakudex.sortPakuri();
                    System.out.println("Pakuri have been sorted!");

                    break;

                //If 6, changes the running program variable to tell the program to stop.
                case 6:
                    running_program = false;
                    break;

                //Otherwise, prints an error message.
                default:
                    System.out.println("Unrecognized menu selection!");
                    break;
            }
        }

        //Prints a goodbye message.
        System.out.println("Thanks for using Pakudex! Bye!");
    }
}
