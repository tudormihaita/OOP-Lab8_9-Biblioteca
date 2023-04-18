#pragma once
#include <string>
#include "Book.h"

int Book::nrEntities = 0;

string Book::getISBN() const {
	return this->ISBN;
}

int Book::getId() const noexcept {
	return this->id;
}

string Book::getTitle() const {
	return this->title;
}

string Book::getAuthor() const {
	return this->author;
}

string Book::getGenre() const {
	return this->genre;
}

string Book::getPublisher() const {
	return this->publisher;
}

int Book::getYear() const noexcept {
	return this->year;
}


void Book::setTitle(const string& newTitle) {
	this->title = newTitle;
}

void Book::setAuthor(const string& newAuthor) {
	this->author = newAuthor;
}


void Book::setGenre(const string& newGenre) {
	this->genre = newGenre;
}

void Book::setPublisher(const string& newPublisher) {
	this->publisher = newPublisher;
}

void Book::setYear(const int& newReleaseYear) noexcept{
	this->year = newReleaseYear;
}


/*bool cmpByTitle(const Book& b1, const Book& b2) {
		return b1.getTitle() < b2.getTitle();
}

bool cmpByAuthor(const Book& b1, const Book& b2) {
	return b1.getAuthor() < b2.getAuthor();
}

bool cmpByReleaseYearAndGenre(const Book& b1, const Book& b2) {
		if (b1.getYear() == b2.getYear()) {
			return b1.getGenre() < b2.getGenre();
		}
		else {
			return b1.getYear() < b2.getYear();
		}
}*/