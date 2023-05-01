#pragma once

class Tests {
public:
	void runAllTests();
private:
	void runDomainTests();
	void runValidationTests();
	void runRepoTests();
	void runServiceTests();
	void runWishlistTests();
	void runUndoTests();
};