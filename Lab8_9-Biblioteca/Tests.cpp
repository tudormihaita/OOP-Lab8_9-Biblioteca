#pragma once
#include <iostream>
#include <cassert>
#include <functional>
#include "Tests.h"
#include "Validator.h"
#include "Exceptions.h"
#include "Book.h"
#include "Wishlist.h"
#include "Repository.h"
#include "Service.h"


void Tests::runAllTests() {
	std::cout << "-------------------------------------------\n";
	std::cout << "Ruleaza teste domain...\n";
	runDomainTests();
	std::cout << "Teste domain trecute cu succes!\n";
	std::cout << "Ruleaza teste validator...\n";
	runValidationTests();
	std::cout << "Teste validator trecute cu succes!\n";
	std::cout << "Ruleaza teste repository...\n";
	runRepoTests();
	std::cout << "Teste repository trecute cu succes!\n";
	std::cout << "Ruleaza teste service si wishlist...\n";
	runServiceTests();
	runWishlistTests();
	std::cout << "Teste service trecute cu succes!\n";
	std::cout << "-------------------------------------------\n";
}

void Tests::runDomainTests() {
	Book book(9, "War and Peace", "Lev Tolstoi", "Nuvela istorica", "Humanitas", 1869);
	assert(book.getTitle() == "War and Peace");
	assert(book.getAuthor() == "Lev Tolstoi");
	assert(book.getGenre() == "Nuvela istorica");
	assert(book.getPublisher() == "Humanitas");
	assert(book.getYear() == 1869);
	assert(book.getId() == 9);
	assert(book.getISBN() == "9ROWL69");

	Book identical_book(9, "War and Peace", "Lev Tolstoi", "Fictiune", "Corint", 1869);
	assert(book == identical_book);

	Book copy_book = book;
	assert(copy_book.getTitle() == "War and Peace");
	assert(copy_book.getAuthor() == "Lev Tolstoi");
	assert(copy_book.getISBN() == book.getISBN());

	book.setYear(1871);
	assert(book.getYear() == 1871);
	
	book.setTitle("In Search of Lost Time");
	assert(book.getTitle() == "In Search of Lost Time");

	book.setAuthor("Marcel Proust");
	assert(book.getAuthor() == "Marcel Proust");

	book.setGenre("Fictiune");
	assert(book.getGenre() == "Fictiune");

	book.setPublisher("Art");
	assert(book.getPublisher() == "Art");
}

void Tests::runValidationTests() {
	Validator bookValidator;
	Book book(9, "War and Peace", "Lev Tolstoi", "Nuvela istorica", "Humanitas", 1869);
	//std::cout << book.get_ISBN() << "\n";

	bookValidator.validateBook(book);

	Book invalidBook(-2, "a","a!!~", "b", "c", 10);
	try {
		bookValidator.validateBook(invalidBook);
		assert(false);
	}
	catch (ValidationException& ve) {
		assert(ve.get_error_messages() == "Numar identificare carte invalid, introduceti un numar cuprins intre 0 si 99!\n"
			"Titlu invalid, introduceti un sir de caractere valid!\nNume autor invalid, introduceti un sir de caractere valid!\n"
			"Gen invalid, introduceti un sir de caractere valid!\nEditura invalida, introduceti un sir de caractere valid!\n"
			"An invalid, introduceti un numar valid!\n");
	}

}

void Tests::runRepoTests() {
	BookRepository bookRepository;
	assert(bookRepository.getSize() == 0);
	Book book1{ 9, "War and Peace", "Lev Tolstoi", "Nuvela istorica", "Corint", 1869 };
	bookRepository.addBook(book1);
	assert(bookRepository.getSize() == 1);

	Book book2{ 12, "In Search of Lost Time", "Marcel Proust", "Fictiune", "Nemira", 1913};
	bookRepository.addBook(book2);
	assert(bookRepository.getSize() == 2);

	Book identicalBook{ 17, "War and Peace", "Lev Tolstoi", "Biografie", "Art", 1869 };
	try {
		bookRepository.addBook(identicalBook);
		assert(false);
	}
	catch (RepoException& re) {
		assert(re.get_error_message() == "Cartea cu titlul War and Peace si autorul Lev Tolstoi aparuta in 1869 exista deja in lista!\n");
	}
	assert(bookRepository.getSize() == 2);

	vector<Book> booklist = bookRepository.getAllBooks();
	assert(booklist.size() == 2);

	string lookedUpISBN = book1.getISBN();
	Book lookedUpBook = bookRepository.findBook(lookedUpISBN);
	assert(lookedUpBook == book1);

	try {
		Book missingBook = bookRepository.findBook("2ROIL15");
		assert(false);
	}
	catch (RepoException& re) {
		assert(re.get_error_message() == "Cartea cu ISBN-ul 2ROIL15 nu exista in lista!\n");
	}

	bookRepository.deleteBook(book2);
	assert(bookRepository.getSize() == 1);

	try {
		bookRepository.deleteBook(book2);
		assert(false);
	}
	catch (RepoException& re) {
		assert(re.get_error_message() == "Cartea cu titlul In Search of Lost Time si autorul Marcel Proust aparuta in 1913 nu exista in lista!\n");
	}

	Book updatedBook{ 9, "War and Peace", "Lev Tolstoi", "Poveste de razboi", "Litera", 1869 };
	bookRepository.updateBook(updatedBook);
	string updatedISBN = updatedBook.getISBN();
	assert(bookRepository.findBook(updatedISBN).getGenre() == "Poveste de razboi");

	try {
		Book missingBook{23,  "To Kill a Mockingbird", "Harper Lee", "Thriller", "Art", 1960};
		bookRepository.updateBook(missingBook);
		assert(false);
	}
	catch (RepoException& re) {
		assert(re.get_error_message() == "Cartea cu titlul To Kill a Mockingbird si autorul Harper Lee aparuta in 1960 nu exista in lista!\n");
	}
}

void Tests::runServiceTests() {
	BookRepository bookRepository;
	Validator bookValidator;
	Library bookLibrary{ bookRepository, bookValidator };

	assert(bookLibrary.getSize() == 0);

	bookLibrary.storeBook(23, "To Kill a Mockingbird", "Harper Lee", "Thriller", "Humanitas", 1960);
	bookLibrary.storeBook(17, "War and Peace", "Lev Tolstoi", "War story", "Corint", 1869);

	assert(bookLibrary.getSize() == 2);
	vector<Book> booklist = bookLibrary.getAllBooks();
	assert(booklist.size() == 2);

	try {
		bookLibrary.storeBook(31, "To Kill a Mockingbird", "Harper Lee", "Roman juridic", "Art", 1960);
		assert(false);
	}
	catch (RepoException& re) {
		assert(re.get_error_message() == "Cartea cu titlul To Kill a Mockingbird si autorul Harper Lee aparuta in 1960 exista deja in lista!\n");
	}

	Book oldBook = bookLibrary.updateBook("23ROTH60", "Roman juridic", "Corint");
	assert(oldBook.getISBN() == "23ROTH60");
	assert(bookLibrary.findBook("23ROTH60").getGenre() == "Roman juridic");
	assert(bookLibrary.findBook("23ROTH60").getPublisher() == "Corint");

	try {
		bookLibrary.updateBook("19ROIM71", "Roman psihologic", "Arthur");
		assert(false);
	}
	catch (RepoException& re) {
		assert(re.get_error_message() == "Cartea cu ISBN-ul 19ROIM71 nu exista in lista!\n");
	}

	const Book& deletedBook = bookLibrary.removeBook("17ROWL69");
	assert(deletedBook.getId() == 17);
	assert(deletedBook.getISBN() == "17ROWL69");
	assert(bookLibrary.getSize() == 1);

	try {
		bookLibrary.removeBook("19ROIM71");
	}
	catch (RepoException&) {
		assert(true);
	}

	bookLibrary.removeBook("23ROTH60");
	assert(bookLibrary.getSize() == 0);

	bookLibrary.storeBook(14, "In Search of Lost Time", "Marcel Proust", "Fictiune filosofica", "Humanitas", 1890);
	bookLibrary.storeBook(67, "The Trial", "Franz Kafka", "Fictiune filosofica", "Art", 1925);
	bookLibrary.storeBook(6, "Les Miserables", "Victor Hugo", "Tragedie", "Humanitas", 1862);
	bookLibrary.storeBook(19, "The Castle", "Franz Kafka", "Comedie", "Corint", 1926);

	assert(bookLibrary.getSize() == 4);


	vector<Book> filteredBooksReleaseYear = bookLibrary.filterByReleaseYear(1860, 1900);
	assert(filteredBooksReleaseYear.size() == 2);


	vector<Book> filteredBooksGenre = bookLibrary.filterByGenre("Fictiune filosofica");
	assert(filteredBooksGenre.size() == 2);


	vector<Book> sortedBooksByTitle = bookLibrary.sortByTitle(false);
	assert(sortedBooksByTitle.at(0).getTitle() == "In Search of Lost Time");
	vector<Book> sortedBooksByTitleReversed = bookLibrary.sortByTitle(true);
	assert(sortedBooksByTitleReversed.at(0).getTitle() == "The Trial");

	vector<Book> sortedBooksByAuthor = bookLibrary.sortByAuthor(false);
	assert(sortedBooksByAuthor.at(0).getAuthor() == "Franz Kafka");
	vector<Book> sortedBooksByAuthorReversed = bookLibrary.sortByAuthor(true);
	assert(sortedBooksByAuthorReversed.at(0).getAuthor() == "Victor Hugo");

	bookLibrary.storeBook(96, "Madame Bovary", "Gustave Flaubert", "Tragedie", "Humanitas", 1862);
	bookLibrary.storeBook(12, "The Divine Comedy", "Dante Alighieri", "Drama", "Arthur", 1862);
	bookLibrary.storeBook(2, "The Brothers Karamazov", "Fyodor Dostoyevsky", "Tragic", "Humanitas", 1862);

	vector<Book> sortedBooksByReleaseYearAndGenre = bookLibrary.sortByReleaseYearAndGenre(false);
	assert(sortedBooksByReleaseYearAndGenre.at(0).getYear() == 1862);
	vector<Book> sortedBooksByReleaseYearAndGenreReversed = bookLibrary.sortByReleaseYearAndGenre(true);
	assert(sortedBooksByReleaseYearAndGenreReversed.at(0).getYear() == 1926);
}

void Tests::runWishlistTests() {
	BookRepository bookRepository;
	Validator bookValidator;
	Library bookService{ bookRepository, bookValidator };

	try {
		bookService.addRandomToWishlist(6);
		assert(false);
	}
	catch(RepoException&){
		assert(true);
	}

	bookService.storeBook(23, "To Kill a Mockingbird", "Harper Lee", "Thriller", "Humanitas", 1960);
	bookService.storeBook(17, "War and Peace", "Lev Tolstoi", "War story", "Corint", 1869);
	bookService.storeBook(15, "War and Peace", "Lev Tolstoi", "War story", "Arthur", 1887);
	bookService.storeBook(14, "In Search of Lost Time", "Marcel Proust", "Fictiune filosofica", "Humanitas", 1890);
	bookService.storeBook(67, "The Trial", "Franz Kafka", "Fictiune filosofica", "Art", 1925);
	bookService.storeBook(6, "Les Miserables", "Victor Hugo", "Tragedie", "Humanitas", 1862);
	bookService.storeBook(19, "The Castle", "Franz Kafka", "Comedie", "Corint", 1926);

	vector<Book> matchedBooks = bookService.matchWishlistBooks("War and Peace");
	assert(matchedBooks.size() == 2);

	assert(bookService.matchWishlistBooks("Anna Karenina").size() == 0);

	bookService.addToWishlist("23ROTH60");
	assert(bookService.getWishlistBooks().size() == 1);

	bookService.emptyWishlist();
	assert(bookService.getWishlistBooks().size() == 0);

	try {
		bookService.addToWishlist("14ROAH47");
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}

	bookService.addRandomToWishlist(3);
	assert(bookService.getWishlistBooks().size() == 3);

}