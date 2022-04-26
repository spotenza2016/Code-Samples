/* On my honor, I have neither given nor received unauthorized aid on this assignment. */

//Standard Libaries and using namespace std
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include<vector>
#include<cmath>
using namespace std;

//Function to convert unsigned binary string to decimal
int binaryToDecimal(string binary) {
    //Variables to increment
    int decimalTotal = 0;
    int exponent = 0;

    //Starting at the least significant bit
    for (int i = binary.length() - 1; i >= 0; i--) {
        //Add the proper amount to the total
        decimalTotal += stoi(binary.substr(i, 1)) * pow(2, exponent++);
    }

    //Return the total
    return decimalTotal;
}

//Function to convert signed binary string to decimal
int signedBinaryToDecimal(string binary) {
    //If the number is positive, can be converted like unsigned
    if (binary.at(0) == '0') {
        return binaryToDecimal(binary);
    }

    //Otherwise, need to turn to 1's complement by subtracting 1
    for (int i = binary.length() - 1; i >= 0; i--) {
        //Finds the first 1 bit, turning it to 0 for subtraction
        if (binary.at(i) == '1') {
            binary.at(i) = '0';
            break;
        }
        //If finds a 0 bit beforehand, turn it to 1 for carry.
        else {
            binary.at(i) = '1';
        }
    }

    //Invert every bit to turn from 1's complement
    for (int i = binary.length() - 1; i >= 0; i--) {
        //If finds a 1 bit, turn to 0 and vice versa
        if (binary.at(i) == '1') {
            binary.at(i) = '0';
        } else {
            binary.at(i) = '1';
        }
    }

    //Find the decimal of this binary, and return the negative of it
    return -1 * binaryToDecimal(binary);
}

//Function that decodes a given line of binary, returning the assembly line and parsed data
pair<string, vector<int>> decodeARM (const string& line) {
    //Holds the assembly line and parsed data
    pair<string, vector<int>> result;

    //Get the 3 first bits indicating the type
    string type = line.substr(0, 3);

    //If category 1
    if (type == "001") {
        //Get the appropriate length binaries and convert to decimal, treating the offset as signed
        int opCode = binaryToDecimal(line.substr(3, 5));
        int src1 = binaryToDecimal(line.substr(8, 5));
        int offset = signedBinaryToDecimal(line.substr(13, 19));

        //Push back the data for easy retrieval
        result.second.push_back(opCode);
        result.second.push_back(src1);
        result.second.push_back(offset);

        //Declare string variables
        string opCodeStr, src1Str, offsetStr;

        //If the opCode == 10000
        if (opCode == 16) {
            opCodeStr = "CBZ";
        }
        //If the opCode == 10001
        else if (opCode == 17) {
            opCodeStr = "CBNZ";
        }

        //Check if the registers are the zero register, changing how it is displayed in the assembly line
        if (src1 == 31) {
            src1Str = "ZR";
        } else {
            src1Str = to_string(src1);
        }

        //Turn the offset to a string
        offsetStr = to_string(offset);

        //Store the assembly line
        result.first = opCodeStr + " X" + src1Str + ", #" + offsetStr;
    }
    //If category 2
    else if (type == "010") {
        //Get the appropriate length binaries and convert to decimal, treating the immediate according to opCode
        int opCode = binaryToDecimal(line.substr(3, 7));
        int dest = binaryToDecimal(line.substr(10, 5));
        int src1 = binaryToDecimal(line.substr(15, 5));
        int immediate;

        //Push back the data for easy retrieval
        result.second.push_back(opCode);
        result.second.push_back(dest);
        result.second.push_back(src1);

        //Declare string variables
        string opCodeStr, destStr, src1Str, immediateStr;

        //If opCode == 1000000, treat as unsigned
        if (opCode == 64) {
            opCodeStr = "ORRI";
            immediate = binaryToDecimal(line.substr(20, 12));
        }
        //If opCode == 1000001, treat as unsigned
        else if (opCode == 65) {
            opCodeStr = "EORI";
            immediate = binaryToDecimal(line.substr(20, 12));
        }
        //If opCode == 1000010, treat as signed
        else if (opCode == 66) {
            opCodeStr = "ADDI";
            immediate = signedBinaryToDecimal(line.substr(20, 12));
        }
        //If opCode == 1000011, treat as signed
        else if (opCode == 67) {
            opCodeStr = "SUBI";
            immediate = signedBinaryToDecimal(line.substr(20, 12));
        }
        //If opCode == 1000100, treat as unsigned
        else if (opCode == 68) {
            opCodeStr = "ANDI";
            immediate = binaryToDecimal(line.substr(20, 12));
        }

        //Push back the converted immediate
        result.second.push_back(immediate);

        //Check if the registers are the zero register, changing how it is displayed in the assembly line
        if (dest == 31) {
            destStr = "ZR";
        } else {
            destStr = to_string(dest);
        }
        if (src1 == 31) {
            src1Str = "ZR";
        } else {
            src1Str = to_string(src1);
        }

        //Convert the immediate to a string
        immediateStr = to_string(immediate);

        //Store the assembly line
        result.first = opCodeStr + " X" + destStr + ", X" + src1Str + ", #" + immediateStr;
    }
    //If category 3
    else if (type == "011") {
        //Get the appropriate length binaries and convert to decimal
        int opCode = binaryToDecimal(line.substr(3, 8));
        int dest = binaryToDecimal(line.substr(11, 5));
        int src1 = binaryToDecimal(line.substr(16, 5));
        int src2 = binaryToDecimal(line.substr(21, 5));

        //Push back the data for easy retrieval
        result.second.push_back(opCode);
        result.second.push_back(dest);
        result.second.push_back(src1);
        result.second.push_back(src2);

        //Declare string variables
        string opCodeStr, destStr, src1Str, src2Str;

        //If opCode == 10100000
        if (opCode == 160) {
            opCodeStr = "EOR";
        }
        //If opCode == 10100010
        else if (opCode == 162) {
            opCodeStr = "ADD";
        }
        //If opCode == 10100011
        else if (opCode == 163) {
            opCodeStr = "SUB";
        }
        //If opCode == 10100100
        else if (opCode == 164) {
            opCodeStr = "AND";
        }
        //If opCode == 10100101
        else if (opCode == 165) {
            opCodeStr = "ORR";
        }
        //If opCode == 10100110
        else if (opCode == 166) {
            opCodeStr = "LSR";
        }
        //If opCode == 10100111
        else if (opCode == 167) {
            opCodeStr = "LSL";
        }

        //Check if the registers are the zero register, changing how it is displayed in the assembly line
        if (dest == 31) {
            destStr = "ZR";
        } else {
            destStr = to_string(dest);
        }
        if (src1 == 31) {
            src1Str = "ZR";
        } else {
            src1Str = to_string(src1);
        }
        if (src2 == 31) {
            src2Str = "ZR";
        } else {
            src2Str = to_string(src2);
        }

        //Store the assembly line
        result.first = opCodeStr + " X" + destStr + ", X" + src1Str + ", X" + src2Str;
    }
    //If category 4
    else if (type == "100") {
        //Get the appropriate length binaries and convert to decimal, treating the immediate as signed
        int opCode = binaryToDecimal(line.substr(3, 8));
        int srcdst = binaryToDecimal(line.substr(11, 5));
        int src1 = binaryToDecimal(line.substr(16, 5));
        int immediate = signedBinaryToDecimal(line.substr(21, 11));

        //Push back the data for easy retrieval
        result.second.push_back(opCode);
        result.second.push_back(srcdst);
        result.second.push_back(src1);
        result.second.push_back(immediate);

        //Declare string variables
        string opCodeStr, srcdstStr, src1Str, immediateStr;

        //If opCode == 10100110
        if (opCode == 170) {
            opCodeStr = "LDUR";
        }
        //If opCode == 10100111
        else if (opCode == 171) {
            opCodeStr = "STUR";
        }

        //Check if the registers are the zero register, changing how it is displayed in the assembly line
        if (srcdst == 31) {
            srcdstStr = "ZR";
        } else {
            srcdstStr = to_string(srcdst);
        }
        if (src1 == 31) {
            src1Str = "ZR";
        } else {
            src1Str = to_string(src1);
        }

        //Convert the immediate to a string
        immediateStr = to_string(immediate);

        //Store the assembly line
        result.first = opCodeStr + " X" + srcdstStr + ", [X" + src1Str + ", #" + immediateStr + "]";
    }
    //Dummy instruction
    else if (type == "101") {
        result.first = "DUMMY";
        result.second.push_back(-1);
    }

    //Return the stored assembly line and data
    return result;
}

//Main method
int main(int argc, char* argv[]) {
    //Check if the number of arguments is correct
    if (argc != 2) {
        return -1;
    }

    //Get the file name, and open an input file stream and an output file stream
    string fileName = argv[1];
    ifstream input(fileName);
    ofstream disassembly("disassembly.txt");

    //Current line
    string currLine;

    //Current address
    int address = 64;

    //Where the dummy instruction is and if currently past it
    bool dummySection = false;
    int dummyAddress;

    //Stores the addresses instructions and corresponding assembly and parsed data
    map<int, pair<string, vector<int>>> instructionList;

    //While lines remain
    while (getline(input, currLine)) {
        //Instruction assembly line and instruction
        pair<string, vector<int>> instruction;

        //If not yet reached the dummy section
        if (!dummySection) {
            //Decode the instruction
            instruction = decodeARM(currLine);

            //Check if this is the dummy section
            if (instruction.first == "DUMMY") {
                dummySection = true;
                dummyAddress = address;
            }
        }
        //Otherwise, get the signed binary of the line and store it
        else {
            int data = signedBinaryToDecimal(currLine);
            instruction.first = to_string(data);
            instruction.second.push_back(data);
        }

        //Store the data
        instructionList[address] = instruction;

        //Write out the given line and it's corresponding address and assembly line
        disassembly << currLine + "\t" + to_string(address) + "\t" + instruction.first << endl;

        //Go to the next address
        address += 4;
    }
    //Open new output stream for the simulation
    ofstream simulation("simulation.txt");

    //Variables for cycle and address
    int cycle = 1;
    address = 64;

    //Vector of all 32 registers, default initialized to 32
    vector<int> registers;
    registers.resize(32);

    //While before or at the dummy address
    while (address <= dummyAddress) {
        //Calculate next address if no branch occurs
        int nextAddress = address + 4;

        //Get the parsed data and opCode
        vector<int> instructionData = instructionList[address].second;
        int opCode = instructionData.at(0);

        //Switches to the proper instruction corresponding to opCode (decimal equivalent as seen in decodeARM())
        switch (opCode) {
            //CBZ
            case 16: {
                //Get the data
                int src1 = instructionData.at(1);
                int offset = instructionData.at(2);

                //If 0, branch according to offset
                if (registers.at(src1) == 0) {
                    nextAddress = address + 4 * offset;
                }

                break;
            }

            //CBNZ
            case 17: {
                //Get the data
                int src1 = instructionData.at(1);
                int offset = instructionData.at(2);

                //If not 0, branch according to offset
                if (registers.at(src1) != 0) {
                    nextAddress = address + 4 * offset;
                }

                break;
            }

            //ORRI
            case 64: {
                //Get the data
                int dest = instructionData.at(1);
                int src1 = instructionData.at(2);
                int immediate = instructionData.at(3);

                //Set the proper register to src1 OR immediate
                registers.at(dest) = registers.at(src1) | immediate;

                break;
            }

            //EORI
            case 65: {
                //Get the data
                int dest = instructionData.at(1);
                int src1 = instructionData.at(2);
                int immediate = instructionData.at(3);

                //Set the proper register to src1 EOR immediate
                registers.at(dest) = registers.at(src1) ^ immediate;
                break;
            }

            //ADDI
            case 66: {
                //Get the data
                int dest = instructionData.at(1);
                int src1 = instructionData.at(2);
                int immediate = instructionData.at(3);

                //Set the proper register to src1 + immediate
                registers.at(dest) = registers.at(src1) + immediate;
                break;
            }

            //SUBI
            case 67: {
                //Get the data
                int dest = instructionData.at(1);
                int src1 = instructionData.at(2);
                int immediate = instructionData.at(3);

                //Set the proper register to src1 - immediate
                registers.at(dest) = registers.at(src1) - immediate;

                break;
            }

            //ANDI
            case 68: {
                //Get the data
                int dest = instructionData.at(1);
                int src1 = instructionData.at(2);
                int immediate = instructionData.at(3);

                //Set the proper register to src1 AND immediate
                registers.at(dest) = registers.at(src1) & immediate;

                break;
            }

            //EOR
            case 160: {
                //Get the data
                int dest = instructionData.at(1);
                int src1 = instructionData.at(2);
                int src2 = instructionData.at(3);

                //Set the proper register to src1 EOR src2
                registers.at(dest) = registers.at(src1) ^ registers.at(src2);

                break;
            }

            //ADD
            case 162: {
                //Get the data
                int dest = instructionData.at(1);
                int src1 = instructionData.at(2);
                int src2 = instructionData.at(3);

                //Set the proper register to src1 + src2
                registers.at(dest) = registers.at(src1) + registers.at(src2);
                break;
            }

            //SUB
            case 163: {
                //Get the data
                int dest = instructionData.at(1);
                int src1 = instructionData.at(2);
                int src2 = instructionData.at(3);

                //Set the proper register to src1 - src2
                registers.at(dest) = registers.at(src1) - registers.at(src2);

                break;
            }

            //AND
            case 164: {
                //Get the data
                int dest = instructionData.at(1);
                int src1 = instructionData.at(2);
                int src2 = instructionData.at(3);

                //Set the proper register to src1 AND src2
                registers.at(dest) = registers.at(src1) & registers.at(src2);

                break;
            }

            //ORR
            case 165: {
                //Get the data
                int dest = instructionData.at(1);
                int src1 = instructionData.at(2);
                int src2 = instructionData.at(3);

                //Set the proper register to src1 OR src2
                registers.at(dest) = registers.at(src1) | registers.at(src2);

                break;
            }

            //LSR
            case 166: {
                //Get the data
                int dest = instructionData.at(1);
                int src1 = instructionData.at(2);
                int src2 = instructionData.at(3);
                int shift = registers.at(src2);

                //Get only the least significant 5 bits by doing AND with 31 (11111)
                shift = shift & 31;

                //Set the proper register to src1 shifted right by src2
                registers.at(dest) = (unsigned int)registers.at(src1) >> shift;

                break;
            }

            //LSL
            case 167: {
                //Get the data
                int dest = instructionData.at(1);
                int src1 = instructionData.at(2);
                int src2 = instructionData.at(3);
                int shift = registers.at(src2);

                //Get only the least significant 5 bits by doing AND with 31 (11111)
                shift = shift & 31;

                //Set the proper register to src1 shifted left by src2
                registers.at(dest) = registers.at(src1) << shift;

                break;
            }

            //LDUR
            case 170: {
                //Get the data
                int srcdst = instructionData.at(1);
                int src1 = instructionData.at(2);
                int immediate = instructionData.at(3);

                //Get the memory location
                int location = registers.at(src1) + immediate;

                //Set the proper register to the data at that memory location
                registers.at(srcdst) = instructionList[location].second.at(0);

                break;
            }

            //STUR
            case 171: {
                //Get the data
                int srcdst = instructionData.at(1);
                int src1 = instructionData.at(2);
                int immediate = instructionData.at(3);

                //Get the memory location
                int location = registers.at(src1) + immediate;

                //Set the proper memory location's data to srcdst
                instructionList[location].first = to_string(registers.at(srcdst));
                instructionList[location].second.at(0) = registers.at(srcdst);
                break;
            }
        }

        //Since XZR can only be 0, if a change was done to it reverse it
        if (registers.at(31) != 0) {
            registers.at(31) = 0;
        }

        //Formatting for simulation
        simulation << "--------------------" << endl;
        simulation << "Cycle " << cycle++ << ":\t" << address << "\t" << instructionList[address].first << endl;
        simulation << endl;
        simulation << "Registers" << endl;
        //For each register
        for (int i = 0; i < 32; i++) {
            //If at the start of a line, add a label
            if (i == 0) {
                simulation << "X00:";
            } else if (i == 8) {
                simulation << "\nX08:";
            } else if (i == 16) {
                simulation << "\nX16:";
            } else if (i == 24) {
                simulation << "\nX24:";
            }

            //Write the register's data
            simulation << "\t" << registers.at(i);
        }

        //Formatting for Simulation
        simulation << endl << endl;
        simulation << "Data";

        //Counter Variable
        int counter = 0;

        //For every address after the dummy address (memory)
        for (auto iter = instructionList.find(dummyAddress + 4); iter != instructionList.end(); iter++) {
            //Get the address and value
            int memAddress = iter->first;
            string memValue = iter->second.first;

            //If at the start of a new line, add a label
            if (counter++ % 8 == 0) {
                simulation << endl << memAddress << ":";
            }

            //Write the memory location's value
            simulation << "\t" << memValue;
        }

        //Formatting for simulation
        simulation << endl << endl;

        //Set the address to the proper next address
        address = nextAddress;
    }

    return 0;
}
