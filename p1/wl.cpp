/*
 * Name: Austin Wilson
 * Date: 9/11/2019
 * Class: Database Management Systems CS564
 * Student ID: 907 426 2305
 * E-Mail: awilson34@wisc.edu
 *
 * This is the main driver class for the WordLocator program.
 * The program reads from cin and prints output to cout.
 * No bugs known.
 *
 */

#include "wl.h"

//Add a specific word to the data structure
int addData(string line, vector<string> &word_list) {
    word_list.push_back(line);
    return 0;
}

//Parse a line of input from the specified file. Clean the data based
//on whitespace and the given delimiters, as well as format all
//data to lowercase before storing it in the data structure.
int cleanData(string line, vector<string> &word_list) {

    int size_of_line = line.size();
    char str[size_of_line];
    char* input;

    strcpy(str, line.c_str());
    //separate based on non alphanumeric or apostrophe
    input = strtok(str, " ,.!?[]{}-_@+=`~#$%/^&*()<>:;|\\\t\n\r\"");
    while (input != NULL) {
        string temp = input;
        //clean data to lowercase
        transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        //Add to data structure
        addData(temp, word_list);
        input = strtok(NULL, " ,.!?[]{}-_@#`~+=/$%^&*()<>:;|/\\\t\n\r\"");
    }
    return 0;
}

//Given an inputstream and the word_list, get the next line of the file and
//clean the data that will ultimatley be stored in the word_list
int user_load(vector<string> &word_list, ifstream &input_file) {

    string line;

    //Check for valid file
    if (!input_file) {
        cout << "ERROR: Invalid command" << endl;
        return -1;
    }

    //Read file line by line
    while (getline(input_file, line)) {
        //clean the data that will be added to the data structure
        cleanData(line, word_list);
    }

    input_file.close();
    return 0;
}

//Grab a line of input from cin
int prompt_user(string prompt, string &data) {
    cout << prompt;
    getline(cin, data);
    return 0;
}

//Search the word_list for a specific word's occurrence
int user_locate(vector<string> word_list, string word, int num) {

    int seen = 0;
    int count = 1;

    //iterate word_list
    for (auto it = word_list.begin(); it != word_list.end(); it++, count++) {
        //increment if the word match
        if (*it == word) {
            seen++;
        }
        //If we have reached out occurrence limit, return that number of iterations
        if (seen == num) {
            return count;
        }
    }
    return 0;
}


//Main driver method and loop for the program
int main() {

    //Global variables for the program
    vector<string> word_list;
    string file_path;
    string data;
    string command;
    string command_2;
    string command_3;
    int load_command = 0;

    //Infinite user loop to prompt
    while (1) {

        //prompt user
        prompt_user(">", data);

        //Split user input into tokens
        istringstream stream(data);
        stream >> command >> command_2 >> command_3;
        transform(command.begin(), command.end(), command.begin(), ::tolower);

        //Load Command
        if (command == "load") {
            if (command_2.empty() || !command_3.empty()) {
                cout << "ERROR: Invalid command" << endl;
            }
            else {
                ifstream input_file(command_2);
                if (load_command && input_file) {
                    word_list.clear();
                    load_command = 0;
                }
                user_load(word_list, input_file);
                load_command = 1;
            }
        }

        //Locate Command
        else if (command == "locate") {
            if (command_2.empty() || command_3.empty()) {
                cout << "ERROR: Invalid command" << endl;
            }
            else {
                int num;
                char occur[command_3.size()];
                strcpy(occur, command_3.c_str());
                num = atoi(occur);
                if (num == 0) {
                    cout << "ERROR: Invalid command" << endl;
                }
                else {
                    int count;
                    transform(command_2.begin(), command_2.end(), command_2.begin(), ::tolower);
                    if ( (count = user_locate(word_list, command_2, num)) ) {
                        cout << count << endl;
                    }
                    else {
                        cout << "No matching entry" << endl;
                    }
                }
            }
        }

        //Clear word_list
        else if (command == "new") {
            if (command_2.empty() && command_3.empty()) {
                word_list.clear();
            }
            else {
                cout << "ERROR: Invalid command" << endl;
            }
        }

        //Exit Program
        else if(command == "end") {
            if (command_2.empty() && command_3.empty()) {
                return 0;
            }
            else {
                cout << "ERROR: Invalid command" << endl;
            }
        }
        else {
            cout << "ERROR: Invalid command" << endl;
        }

        command.clear();
        command_2.clear();
        command_3.clear();

    }
}
