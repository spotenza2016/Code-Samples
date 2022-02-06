#include <iostream>
#include <map>
#include <random>
#include <ctime>
#include <fstream>
using namespace std;

mt19937 random_mt;

int Random(int min, int max);
void RollDice(int numberOfRolls, int numberOfSides);

int Random(int min, int max)
{
    uniform_int_distribution<int> dist(min, max);
    return dist(random_mt);
}

void RollDice(unsigned int numberOfRolls, unsigned int numberOfSides) {
    map<int, int> results;

    for (unsigned int i = 1; i <= numberOfSides; i++) {
        results.emplace(i, 0);
    }

    for (unsigned int i = 0; i < numberOfRolls; i++) {
        results.at(Random(1, numberOfSides))++;
    }

    for (auto iter = results.begin(); iter != results.end(); iter++) {
        cout << iter->first << ": " << iter->second << endl;
    }
}

class State {
    string name;
    int capitaIncome;
    int population;
    int householdIncome;
    int numHouseholds;

public:
    State(string name, int capitaIncome, int population, int householdIncome, int numHouseholds);
    string GetName() const;
    int GetCapitaIncome() const;
    int GetPopulation() const;
    int GetHouseholdIncome() const;
    int GetNumHouseholds() const;
    void PrintInfo() const;
};

State::State(string name, int capitaIncome, int population, int householdIncome, int numHouseholds) {
    this->name = name;
    this->capitaIncome = capitaIncome;
    this->population = population;
    this->householdIncome = householdIncome;
    this->numHouseholds = numHouseholds;
}

string State::GetName() const {
    return name;
}

int State::GetCapitaIncome() const {
    return capitaIncome;
}

int State::GetPopulation() const {
    return population;
}

int State::GetHouseholdIncome() const {
    return householdIncome;
}

int State::GetNumHouseholds() const {
    return numHouseholds;
}

void State::PrintInfo() const {
    cout << "Population: " << GetPopulation() << endl;
    cout << "Per Capita Income: " << GetCapitaIncome() << endl;
    cout << "Median Household Income: " << GetHouseholdIncome() << endl;
    cout << "Number of Households: " << GetNumHouseholds() << endl;
}

int main()
{
    cout << "1. Random Numbers\n";
    cout << "2. State Info\n";

    int option;
    cin >> option;

    if (option == 1)
    {
        int randomSeed;
        cout << "Random seed value: ";
        cin >> randomSeed;
        random_mt.seed(randomSeed);


        cout << "Number of times to roll the die: ";
        unsigned int numRoll;
        cin >> numRoll;

        cout << "Number of sides on this die: ";
        unsigned int numSides;
        cin >> numSides;

        RollDice(numRoll, numSides);
    }
    else if (option == 2)
    {
        map<string, State> states;
        ifstream file("states.csv");
        string first;

        getline(file, first);

        while(getline(file, first, ',')) {
            string name;
            name = first;
            string capitalIncome;
            getline(file, capitalIncome, ',');
            string population;
            getline(file, population, ',');
            string householdIncome;
            getline(file, householdIncome, ',');
            string numHouseholds;
            getline(file, numHouseholds);

            State state(name, stoi(capitalIncome), stoi(population), stoi(householdIncome), stoi(numHouseholds));

            states.emplace(name, state);
        }


        cout << "1. Print all states" << endl;
        cout << "2. Search for a state" << endl;

        int secondOption;
        cin >> secondOption;
        auto iter = states.begin();
        if (secondOption == 1) {
            for (; iter != states.end(); iter++) {
                cout << iter->first << endl;
                iter->second.PrintInfo();
            }
        }
        else if (secondOption == 2) {
            string key;
            cin >> key;
            iter = states.find(key);
            if (iter != states.end()) {
                cout << iter->first << endl;
                iter->second.PrintInfo();
            }
            else {
                cout << "No match found for " << key << endl;
            }
        }
    }

    return 0;
}
