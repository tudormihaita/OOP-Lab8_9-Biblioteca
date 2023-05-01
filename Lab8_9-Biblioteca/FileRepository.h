#pragma once
#include "Repository.h"
#include <string>

using std::string;


class FileBookRepository : public BookRepository {
private:
	//Numele fisierului in care vor fi stocate datele la pornirea aplicatiei, si care va fi adaptat in urma efectuarii operatiilor asupra memoriei
	string fileName;

	//Metode private, pentru incarcarea datelor in memorie din fisier si pentru stocarea datelor modificate dupa fiecare operatie
	void loadFromFile();
	void writeToFile();

public:
	//FileRepo Constructor
	FileBookRepository(string fileName) : BookRepository(), fileName{ fileName } {
		loadFromFile();
	}

	//Metoda de golire a continutului fisierului
	void clearFile();

	//Suprascriere metoda de adaugare
	void addBook(const Book& book) override {
		BookRepository::addBook(book);
		writeToFile();
	}

	//Suprascriere metoda de modificare
	void updateBook(const Book& updatedBook) override {
		BookRepository::updateBook(updatedBook);
		writeToFile();
	}

	//Suprascriere metoda de stergere
	void deleteBook(const Book& bookToDelete) override {
		BookRepository::deleteBook(bookToDelete);
		writeToFile();
	}

	//FileRepo Desctructor
	~FileBookRepository() = default;
};