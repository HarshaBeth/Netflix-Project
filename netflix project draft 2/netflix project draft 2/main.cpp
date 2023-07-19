#include <fstream>
#include <string>
#include<iostream>
#include "Movie.h"
using namespace std;

//Create a struct called Node which contains an object called movieData and next pointer that points to the next node
struct Node {
    Movie movieData;
    Node* next;
};

Node* head = NULL;

                //(movie name, year, genre, ID)
void addNewNode(string name, int y, string g, int i) {
    Node* newNode = new Node();

    Node* tail = head;

    //set data for new node
    newNode->movieData.setMovieName(name);
    newNode->movieData.setYear(y);
    newNode->movieData.setGenre(g);
    newNode->movieData.setID(i);

    newNode->next = NULL;

    //enters new node in head if head is null
    if (head == NULL) {
        head = newNode;
    }
    else {
        //finds the last element and makes the next of it equal to our new node
        while (tail->next != NULL) {
            tail = tail->next;
        }

        tail->next = newNode;
    }

    
}

void displayInfo() {

    Node* temp = head;

    //if head is empty it will print out null
    if (head == NULL) {
        cout << "NULL" << endl;
    }
    else {
        //this will go through all the nodes in our list and print out its information
        while (temp != NULL) {
            
            temp->movieData.display();
            cout << endl;
            temp = temp->next;
        }
    }
    
}

void addNodeSpecificLocation(string name, int y, string g, int i, string prevMovie) {
    Node* newNode = new Node();

    Node* prevMovieNode = head;

    //if head is null it prints out list is empty
    if (head == NULL) {
        cout << "List is empty..." << endl;
        
    }
    else {
        //set data for new node
        newNode->movieData.setMovieName(name);
        newNode->movieData.setYear(y);
        newNode->movieData.setGenre(g);
        newNode->movieData.setID(i);

        //runs through the entire list and makes sure 
        while (prevMovieNode->movieData.movieName != prevMovie) {
            prevMovieNode = prevMovieNode->next;

            if (prevMovieNode == NULL && prevMovieNode->movieData.movieName != prevMovie) {
                cout << "The movie was not found. The new movie will be added to the end..." << endl;
                newNode->next = NULL;
                prevMovieNode->next = newNode;
                break;
            }
        }

        newNode->next = prevMovieNode->next;
        prevMovieNode->next = newNode;
    }


}

void findMoviebyID(int i) {
    Node* current = head;

    while (current != NULL && current->movieData.id != i) {
        current = current->next;
    }

    if (current != NULL) {
         current->movieData.display();
    }
    else {
        cout << " - does not exist - " << endl;
    }
}

void deleteByID(int i) {
    Node* current = head;

    if (head == NULL) {
        cout << "The list is empty" << endl;
    } 
    else {
        //if the node with the desired ID is the head this will make the next  
        //element the head and delete the node with desired ID
        if (current == head && current->movieData.id == i) {
            Node* temp = head;

            head = temp->next;

            delete temp;

            cout << endl << "Node has been deleted..." << endl;
        }
        else {
            //this loop looks for the node with the desired ID
            while (current->movieData.id != i) { 

                current = current->next;

                //this checks if the movie is not in the entire list
                if (current == NULL) {
                    cout << "The movie is not there" << endl;
                    return;
                }
            }


            Node* temp = head;
            //this loop finds what is the node that comes before the desired node
            while (temp->next != current) {
                temp = temp->next;
            }

            //this will connect the previous node to the next node and
            //delete the node in between
            temp->next = current->next;
            delete current;

            cout << endl << "Node has been deleted..." << endl;
        }
    }

}

void deleteAll() {
    
    Node* temp = head;

    if (head == NULL) {
        cout << "List is already empty..." << endl;
    }
    else {
        while (head != NULL) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
}

void isEmpty() {

    if (head == NULL) {
        cout << "The list is empty" << endl;
    }
    else {
        cout << "The list is not empty" << endl;
    }
}

void sort() {
    Node* i;
    Node* j;
    Movie temp;

    if (head == NULL || head->next == NULL) {
        cout << "There is nothing to sort in this list..." << endl;
    }
    else {
        for (i = head; i->next != NULL; i = i->next) {

            for (j = i->next; j != NULL; j = j->next) {
                // b > a (Capital letters will be placed towards the 0 in the list)
                if (i->movieData.movieName > j->movieData.movieName) {
                    temp = j->movieData;
                    j->movieData = i->movieData;
                    i->movieData = temp;
                }
            }

        }

        cout << "The list has been sorted..." << endl;
    }


}

void savetoTxtFile() {
    ofstream file("MoviesOutput.txt");
    
    
    Node* temp = head;

    if (head == NULL) {
        file << "NULL" << endl;
    }
    else {
        //add the movies data to the file
        while (temp != NULL) {
            file << "Movie name is " << temp->movieData.movieName << endl;
            file << "Year of movie " << temp->movieData.movieName << " is " << temp->movieData.year << endl;
            file << "Movie genre is " << temp->movieData.genre << endl;
            file << "ID: " << temp->movieData.id << endl;

            file << endl;

            temp = temp->next;
        }
    }   

    file.close();

}

void loadFromTxtFile() {
    int numOfNodes;
    int year, id;
    string name, genre;

    string line;

    //opens file
    ifstream file ("MoviesInput.txt");

    //gets the number of nodes from file (first line in file)
    getline(file, line);
    numOfNodes = stoi(line);
    

    //Adds the new nodes from the MoviesInput file
    while (numOfNodes--) {
        getline(file, line);
        name = line;
        getline(file, line);
        year = stoi(line);
        getline(file, line);
        genre = line;
        getline(file, line);
        id = stoi(line);
        addNewNode(name, year, genre, id);
    }

    cout << "Loaded data from the text file..." << endl;
    cout << endl;    

    //closes file
    file.close();
}

int main() {

    int choice = 0;
    bool cont = true;

    while (cont) {
        cout << "***Welcome to Netlix movie list***" << endl << endl;
        cout << "Choose what you would like to do: " << endl;
        cout << "1 - Add a new NODE" << endl;
        cout << "2 - Add a new NODE in a specific location" << endl;
        cout << "3 - Display all items in the list" << endl;
        cout << "4 - Find a NODE by its ID" << endl;
        cout << "5 - Delete a NODE by its ID" << endl;
        cout << "6 - Delete all items in the list" << endl;
        cout << "7 - Sort the list in alphabetical order" << endl;
        cout << "8 - Save to a txt file" << endl;
        cout << "9 - Load from a txt file" << endl;
        cout << "10 - Check if list is empty" << endl;
        cout << "11 - Exit" << endl;
        cin >> choice;

        cout << endl;

        if (choice == 1) {  // to add a new node
            string name;
            int year;
            string genre;
            int id;

            cout << endl;
            cout << "Enter name of movie: ";
            cin >> name;
            cout << "Enter year of movie: ";
            cin >> year;
            cout << "Enter genre of movie: ";
            cin >> genre;
            cout << "Enter movie ID: ";
            cin >> id;

            addNewNode(name, year, genre, id);
            cout << endl << "Node has been added..." << endl;
            cout << endl << endl;

        }
        else if (choice == 2) { //to add new node in a specific location in between the head and the end
            string name;
            int year;
            string genre;
            int id;
            string prevMovie;

            cout << endl;
            cout << "Enter name of movie: ";
            cin >> name;
            cout << "Enter year of movie: ";
            cin >> year;
            cout << "Enter genre of movie: ";
            cin >> genre;
            cout << "Enter movie ID: ";
            cin >> id;
            cout << "Enter the previous movie name: ";
            cin >> prevMovie;

            addNodeSpecificLocation(name, year, genre, id, prevMovie);
            cout << endl << "Node has been added...";
            cout << endl << endl;
        }
        else if (choice == 3) { //to display info
            cout << endl;
            displayInfo();

            cout << endl << endl;
        }
        else if (choice == 4) { //to find movie by ID
            int id;
            string movie;
            cout << "Enter movie ID to find the movie: ";
            cin >> id;

            cout << endl << "The movie with ID " << id << ": " << endl;
            findMoviebyID(id);

            cout << endl << endl;
        }
        else if (choice == 5) { //delete node by ID
            int i;
            cout << "Enter ID: ";
            cin >> i;
            deleteByID(i);

            cout << endl;
        }
        else if (choice == 6) { //delete all items in list
           
            deleteAll();
            cout << "All nodes have been deleted..." << endl << endl;


        }
        else if (choice == 7) {
            sort();

            cout << endl << endl;
        }
        else if (choice == 8) { //Save to a text file

            cout << "Data has been saved to the textfile." << endl << endl;
            savetoTxtFile();

        }
        else if (choice == 9) { //Load from a text file
            loadFromTxtFile();           
        }
        else if (choice == 10) {
            isEmpty();
            cout << endl;
        }
        else if (choice == 11) {          
            cont = false;
            cout << endl;
            cout << "You have exited the program..." << endl;         
        }
        else {
        cout << "Wrong input!!" << endl << endl;
            
        }
    }


	return 0;
}


