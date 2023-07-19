#pragma once
#include <iostream>
using namespace std;

class Movie
{
public:
	string movieName;
	int year;
	string genre;
	int id;

	Movie() {
		movieName = "";
		year = 0;
		genre = "";
		id = 0;
	}

	

public:
	void setMovieName(string name) {
		movieName = name;
	}

	void setYear(int y) {
		year = y;
	}

	void setGenre(string g) {
		genre = g;
	}

	void setID(int i) {
		id = i;
	}

	void display() {
		cout << "Movie name is " << movieName << endl;
		cout << "Year of movie " << movieName << " is " << year << endl;
		cout << "Movie genre is " << genre << endl;
		cout << "ID: " << id << endl;
	}
};

