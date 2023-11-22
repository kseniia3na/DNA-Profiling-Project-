/*
    Project 1 - DNA Profiling

    Kseniia Nastahunina

    DNA Profiling app is used to match DNA of a person to a given DNA. Takes commands and
    files from users input to process and match the longest sequences in the file with 
    DNA. Checks if any matches was found.
*/

#include "ourvector.h"
#include <iostream>
#include <fstream>

ourvector <string> fileData; //used to store data base's header (e.g name, AGATC, ect)
ourvector <string> processSTR; //used to store STR types to match

ourvector <string> fileDNA; //used to store DNA
ourvector <size_t> fileProcessDNA; //used to store processed DNA's longest sequences as size_t

ourvector <size_t> allSRTOcc; //used to store processed DNA's all occurences (CREATIVE COMPONENT OBJECT)

ourvector <ourvector <string> > dataBase; //2d vector used to store data base (names and numbers)

using namespace std;

/* The function that displays data base, dna and processed dna. Takes ourvector 2d dataBase vector,
fileDNA, fileProcessDNA vectors. For all the vectores the function check if it is not empty and then uses them to 
display the info.*/
void display( ourvector < ourvector <string> > dataBase, ourvector <string> fileDNA, ourvector <size_t> fileProcessDNA){
    if(dataBase.size() != 0){
        cout << "Database loaded:\n" << endl;
        for(size_t i = 0; i < dataBase.size(); i++){
            fileData = dataBase.at(i);
            for(size_t j = 0; j < fileData.size(); j++){

                cout << fileData.at(j) << " ";
            }
            cout << endl;
        }

    }
    else{
        cout << "\nNo Database loaded.\n" << endl;
    } 
    if(fileDNA.size() != 0){
        cout << "DNA loaded:\n" << endl;
        for(int i = 0; i < fileDNA.size(); i++){
        cout << fileDNA.at(i) << endl;
        }
    }
    else{
        cout << "\nNo DNA loaded.\n" << endl;
    }
    if(fileProcessDNA.size() != 0){
        cout << "DNA processed, STR counts:\n" << endl;   

        for(int i = 0; i < fileProcessDNA.size(); i++){
        cout << processSTR.at(i + 1) << ": " << fileProcessDNA.at(i) << endl;
        }
    }
    else{
        cout << "No DNA has been processed." << endl;
    }
}

/*This function is part of the creative component. It is used to display all of the occurances of STR in the DNA. The mathod is 
separatly form the other display function for testing purposes. The function takes dataBase, allSRTOcc, processSTR, fileDNA
as parametrs to check if the vectors are empty and display the STRs.*/
void displayOcc(ourvector < ourvector <string> > dataBase, ourvector <size_t> allSRTOcc, ourvector <string> processSTR, ourvector <string> fileDNA){
    if(allSRTOcc.size() != 0){
            cout << "DNA processed, all STR counts in D:\n" << endl;   

            for(int i = 0; i < allSRTOcc.size(); i++){
                cout << processSTR.at(i + 1) << ": " << allSRTOcc.at(i) << endl;
            }
         }
        if(dataBase.size() == 0){
            cout << "No database loaded." << endl;
        }
        else if(fileDNA.size() == 0){
            cout << "No DNA loaded." << endl;
        }
}
/*This function is part of the creative component. It is used to count ALL of the STR occurances in the inputed DNA.
As parameters it takes string source, which is the DNA from vector to be processed and str whitch is STR to find.*/
int countSTR(string source, string str){
    int count = 0;
    size_t pos = 0;
    while (pos < source.length()){
       size_t npos = source.find(str, pos);
       if(npos != -1){
        count++;
        pos = npos + str.length();
        string sub = source.substr(pos, source.length() - 1);

       }
       else{
        break;
       }
       
    }    
    return count;
}


/*This is recursion function that returns integer length of a sequence. If the STR that needs to be found continues
then the function calls itself again and adds one to the sequence streak. Used in the function below findSequence. For
parameters takes str that needs to find, sub which is substring in which to look and npos that is new position to 
look at.*/
int longSeq(string sub, string str, size_t npos){
    if(sub.find(str, npos) == npos){
       return 1 + longSeq(sub, str, npos + str.length());
    }
    else{
        return 0;
    }

}

/*This function that returns integer maximum length of a sequence. The function find the beging of a sequence and calles 
londSeq() function to find how long is the sequence. The function return the longest sequence it found. As parameters it
takes string source, which is the DNA from vector to be processed and str whitch is STR to find.*/

int findSequence(string source, string str){
    int maxCount = 0;
    size_t pos = 0;
    string newSub = source;
    while (pos < source.length()){
       pos = source.find(str, pos);
       if(pos != -1){
        int seqCount = 1 + longSeq(source, str, pos + str.length());
        if(seqCount > maxCount){
            maxCount = seqCount;
        }
        pos = pos + seqCount * str.length();
       }
    }    
    return maxCount;
}

/*Search function is used of the search command. The function is cheching the size of fileData which has STR form data file
with the size of file process DNA (they should match since they are supposed to have the same numbers of STR to look for.)
Prints errors if the sizes do not match or the vectors are empty. If the sizes are the same then the function is checking if 
the number inside the file are matching by converting vector of size_t type into string by using to_string function. If the 
match is found then prints the result, if no match is found print not found in data base. The function takes dataBase,
fileProcessDNA, fileDNA as paramets to find a match and check if the vectors aren't empty.*/
void search(ourvector < ourvector <string> > dataBase, ourvector <size_t> fileProcessDNA, ourvector <string> fileDNA){
    if(dataBase.size() != 0 && fileProcessDNA.size() != 0 && fileDNA.size() != 0){
            cout << "Searching database..." << endl;
            bool found = true;
            for(size_t i = 0; i < dataBase.size(); i++){
                fileData = dataBase.at(i);
                if((fileData.size() - 1) != fileProcessDNA.size()){
                    cout << "Error. Files do not match." << endl; //TO DO;
                    break;
                }
                found = true;
                for(size_t j = 0; j < fileData.size() - 1; j++){
                    if((fileData.at(j+1)) != to_string(fileProcessDNA.at(j))){
                        found = false;
                        break;
                    }
                }
                if(found){
                    cout << "Found in database!  DNA matches: " << fileData.at(0) << endl;
                    break;
                }
            }

            if(!found){
                cout << "Not found in database." << endl;
            }
        }
        if (dataBase.size() == 0) {
            cout << "\nNo Database loaded.\n" << endl;
        }
        else if (fileDNA.size() == 0){
            cout << "\nNo DNA loaded.\n" << endl;
        }
        else if (fileProcessDNA.size() == 0){
            cout << "No DNA processed." << endl;
        }
}

/*The function that checks user input takes command and file name as paraments.*/
void returnCommand(string command, string fileName){
    ifstream infile;                                            //used to look though file
    string line;                                                //used to take a line form a file

    if(command == "load_db"){ 
        cout << "Loading database..." << endl;
        infile.open(fileName.c_str()); //opens file
        
        if (!infile.is_open()) { //checks if the file as open
            cout << "Error: unable to open " "\'" << fileName << "\'" << endl;
        }
        if(dataBase.size() != 0){//checks if the data base is already exists
            dataBase.clear(); //erases previous enteries form the vector to insert the new enteries from user's input
        }
        if(infile.is_open()){
            string title; //used to take the first line form the file to store it in a separat vector
            getline(infile, title); //gets the first line in the file
            size_t pos = 0;
            while (pos < title.length()){
                size_t npos = title.find(',', pos); //finds "," between words in one line
                if(npos != -1){ //if found
                    processSTR.push_back(title.substr(pos,npos - pos)); //push every word separatly in the vector
                    pos = npos + 1; //changes the position to look for the next ","
                }
                else{
                    processSTR.push_back(title.substr(pos,title.length() - 1)); //pushes the last word to the vector
                    break;
                }
            }  
            while(getline(infile, line)){
                ourvector <string> vectorLine; //used to store line in th vector
                pos = 0; //sets position to 0 again for the next search
                while (pos < line.length()){
                    size_t npos = line.find(',', pos); //finds "," between words in one line
                    if(npos != -1){
                        vectorLine.push_back(line.substr(pos,npos - pos)); //push every word separatly in the vector
                        pos = npos + 1;
                    }
                    else{
                        vectorLine.push_back(line.substr(pos,line.length() - 1));
                        break;
                    }
                }  
                dataBase.push_back(vectorLine); // stores the line of a file to dataBase to create a 2d vector
                }
        }
    }
    else if(command == "display"){
        display(dataBase, fileDNA, fileProcessDNA); //calls the display function
        }
    else if(command == "load_dna"){
        cout << "Loading DNA..." << endl;
        infile.open(fileName.c_str()); //opens file anf read it char by char
        if (!infile.is_open()) { //checks is the file was open
            cout << "Error: unable to open " << "\'" << fileName << "\'" << endl;
        }
        if(fileDNA.size() != 0){ //checks if the vectormis empty
            fileDNA.clear(); //clears the vector
        }
        if(infile.is_open()){
            while(getline(infile, line)){ //reads file line by line
                fileDNA.push_back(line.c_str()); // adds file enteries to fileDNA;
            }
        }
    }
    else if(command == "process"){
        if(fileProcessDNA.size() != 0){//checks if the vector is empty
            fileProcessDNA.clear(); //clears if it is not
        }
        if(fileDNA.size() != 0){ //checks if there is any DNA to process
            cout << "Processing DNA..." << endl;
            for(size_t i = 1; i < processSTR.size(); i++){
                /*The line below calles the function that looks for sequences and pushes back the longest sequences
                for every STR it found in the DNA file*/
                fileProcessDNA.push_back(findSequence(fileDNA.at(0), processSTR.at(i)));
                allSRTOcc.push_back(countSTR(fileDNA.at(0), processSTR.at(i))); //used for creative component
                }
        }
        if(dataBase.size() == 0){ //checks if there any dataBase
            cout << "No database loaded." << endl;
        }
        else if(fileDNA.size() == 0){ //checks if there any dna to process
            cout << "No DNA loaded." << endl;
        }
    }
    else if(command == "search"){
        search(dataBase, fileProcessDNA, fileDNA); //calles the search function
    }
    else if(command == "#"){
        exit(0); //terminates the program
    }
    else if(command == "dis_occurances"){                           //used for creative component
        displayOcc(dataBase, allSRTOcc, processSTR,fileDNA); //calles the function to display all of STR occurances
    }
    else{
        cout << "Command does not exist. Try again." << endl; //if the input cannot be read
    }
}

int main() {

    cout << "Welcome to the DNA Profiling Application." << endl;

    string command, fileName;                            //used to take input from user

    while(command != "#"){                              //runs until user decides to exit the program
    cout << "Enter command or # to exit: ";             //asks for inout
    cin >> command;                                     //reads the command input form user
    if(command == "load_dna" || command == "load_db"){ //checks if there is any other input needed for thr inputted command
        cin >> fileName;                                //read file name
    }

    returnCommand(command, fileName);                   //calles funtion to give the user response
    }

    return 0;
    
}