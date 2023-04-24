#pragma once
#include "Book.h"
#include "Exceptions.h"
#include "DynamicVectorTemplate.h"
#include "DoublyLinkedListTemplate.h"
#include <vector>
#include <algorithm>

using std::vector;
using std::find_if;


class BookRepository {
private:
	vector<Book> booklist;
	//DynamicVector<Book> booklist;
	//DoublyLinkedList<Book> booklist;

public:
	//Constructor default Repo
	BookRepository() = default;

	//Constructor Repo prin copiere, sters pentru a nu permite copierea
	BookRepository(const BookRepository& other) = delete;

	/*
	* Adauga o carte in lista
	* @param book - cartea care se adauga (Book)
	* @return -
	* @throws - RepoException daca o carte cu acelasi titlu, autor si an aparitie 
				exista deja in lista
	*/
	void addBook(const Book& book);

	/*
	* Returneaza o lista cu toate cartile
	* @return - lista cu carti (Booklist)
	*/
	const vector<Book>& getAllBooks() const noexcept;


	/*
	* Cauta o carte cu ISBN-ul dat
	* @param ISBN - string, cod unic de identificare a unei carti
	* @return - entitatea Book cu ISBN-ul cautat
	* @throws - RepoException daca nu exista nicio carte cu acel ISBN
	*/
	const Book& findBook(const string& ISBN);
	

	/*
	* Returneaza pozitia pe care se afla in lista o carte cautata
	* @param lookedUpBook - entitate Book cautata in lista
	* @return - int, pozitia in lista a cartii cautate
	* @throws - RepoException daca nu exista nicio carte identica cu cea data in lista
	*/
	int getBookPosition(const Book& lookedUpBook);


	/*
	* Sterge o carte data din lista
	* @param bookToDelete - entitate Book cautata in lista pentru a fi stearsa
	* @return -
	* @throws - RepoException daca nu exista cartea data in lista
	*/
	void deleteBook(const Book& bookToDelete);


	/*
	* Modifica genul si editura unei carti date
	* @param updatedBook - entitate Book cautata in lista pentru modificare
	* @return -
	* @throws - RepoException daca cartea data nu exista in lista
	*/
	void updateBook(const Book& updatedBook);


	/*
	* Returneaza numarul curent de carti din lista
	* @param -
	* @return - int, lungimea listei de carti (Booklist size)
	*/
	int getSize() const noexcept;


	//Destructor Repo
	~BookRepository() = default;
};
