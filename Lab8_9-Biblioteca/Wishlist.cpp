#pragma once
#pragma warning (disable: 26823) // dereferencing null pointer
#include "Wishlist.h"

using std::shuffle;
using std::default_random_engine;
using std::random_device;

void Wishlist::addBookToWishlist(const Book& book) noexcept {
	this->wishlistBooks.push_back(book);
}

void Wishlist::emptyWishlist() noexcept {
	this->wishlistBooks.clear();
}

const vector<Book>& Wishlist::getAllWishlistBooks() noexcept {
	return this->wishlistBooks;
}

void Wishlist::addRandomBooks(vector<Book> allBooks, int howMany) {
	if (allBooks.size() < howMany) {
		throw RepoException("Nu exista carti suficiente disponibile in oferta, nu s-a putut crea wishlist-ul!\n");
	}
	else {
		shuffle(allBooks.begin(), allBooks.end(), default_random_engine(random_device{}()));
		while (wishlistBooks.size() < howMany && allBooks.size() > 0) {
			wishlistBooks.push_back(allBooks.back());
			allBooks.pop_back();
		}
	}
}