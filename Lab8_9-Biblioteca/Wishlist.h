#pragma once
#include "Book.h"
#include "Exceptions.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using std::vector;

class Wishlist {
private:
	vector<Book> wishlistBooks;
public:

	//Constructor Wishlist
	Wishlist() = default;

	/*
	* Adauga o carte din biblioteca in wishlist
	* @param book - entitate Book existenta in biblioteca
	* @return -
	*/
	void addBookToWishlist(const Book& book) noexcept;

	/*
	* Goleste wishlist-ul curent
	* @param -
	* @return -
	*/
	void emptyWishlist() noexcept;

	/*
	* Adauga un numar dat de carti random din lista de carti curenta, disponibile din biblioteca
	* @param allBooks - lista curenta de carti disponibile din biblioteca
			 howMany - int, numarul de carti ce urmeaza a fi adaugate in wishlist
	  @return -
	  @throws - RepoException daca nu exista suficiente carti disponibile in biblioteca
	*/
	void addRandomBooks(vector<Book> allBooks, int howMany);

	/*
	* Returneaza lista de carti curenta din wishlist
	* @param -
	* @return - o lista de carti regasite in wishlist
	*/
	const vector<Book>& getAllWishlistBooks() noexcept;
};