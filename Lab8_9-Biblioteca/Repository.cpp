#pragma once
#pragma warning (disable: 26823) // dereferencing null pointer
#pragma warning (disable: 26472) // don't use static_cast
#include "Repository.h"
#include <vector>
#include <algorithm>


int BookRepository::getSize() const noexcept {
	return static_cast<int>(this->booklist.size());
}

const Book& BookRepository::findBook(const string& ISBN) {
	/*for (const Book& _book : this->booklist) {
		if (_book.getISBN() == ISBN) {
			return _book;
		}
	}*/

	vector<Book>::iterator it = find_if(this->booklist.begin(), this->booklist.end(),
		[=](const Book& book) {
			return book.getISBN() == ISBN;
		});
	if (it != this->booklist.end())
		return (*it);
	else
		throw RepoException("Cartea cu ISBN-ul " + ISBN + " nu exista in lista!\n");
}

int BookRepository::getBookPosition(const Book& lookedUpBook) {
	vector<Book>::iterator it = find(this->booklist.begin(), this->booklist.end(), lookedUpBook);
	//IteratorVector<Book> it = this->booklist.find(this->booklist.begin(), this->booklist.end(), lookedUpBook);

	const int pos = static_cast<int>(distance(this->booklist.begin(), it));
	//const int pos = this->booklist.distance(this->booklist.begin(), it);

	if (it != this->booklist.end())
		return pos;
	else
		throw RepoException("Cartea cu titlul " + lookedUpBook.getTitle() + " si autorul " + lookedUpBook.getAuthor() + " aparuta in " 
			+ to_string(lookedUpBook.getYear()) + " nu exista in lista!\n");}


void BookRepository::addBook(const Book& book) {
	//if (exists(book)) {
	if(find_if(this->booklist.begin(), this->booklist.end(), [book](const Book& _book) noexcept {
		return book == _book;  }) != this->booklist.end() ) {
			throw RepoException("Cartea cu titlul " + book.getTitle() + " si autorul " + book.getAuthor() + 
				" aparuta in " + to_string(book.getYear()) + " exista deja in lista!\n");
	}

	this->booklist.push_back(book);
}

const vector<Book>& BookRepository::getAllBooks() const noexcept{
	/*vector<Book> all_books;
	for (const Book& book : this->booklist) {
		all_books.push_back(book);
	}

	return all_books;*/

	return this->booklist;
}

void BookRepository::deleteBook(const Book& bookToDelete) {
	try {
		const int pos_to_delete = getBookPosition(bookToDelete);
		this->booklist.erase(this->booklist.begin() + pos_to_delete);
	}
	catch (const RepoException& e) {
		throw RepoException(e);}

	/*vector<Book>::iterator it = find(this->booklist.begin(), this->booklist.end(), book_to_delete);
	if (it != this->booklist.end())
		this->booklist.erase(std::remove(this->booklist.begin(), this->booklist.end(), book_to_delete), this->booklist.end());
	else
		throw RepoException("Cartea cu titlul " + book_to_delete.get_title() + " si autorul " + book_to_delete.get_author() + " aparuta in "
			+ to_string(book_to_delete.get_year()) + " nu exista in lista!\n")*/;
}

void BookRepository::updateBook(const Book& updatedBook) {
	try {
		const int pos_to_update = getBookPosition(updatedBook);
		this->booklist.at(pos_to_update) = updatedBook;

	}
	catch (const RepoException& e) {
		throw RepoException(e);}
}