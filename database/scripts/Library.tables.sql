CREATE TABLE Variable (
	name   STRING KEY,
	value  STRING
);

CREATE TABLE Book (
	id       STRING KEY,
	name     STRING,
	author   STRING
);

CREATE TABLE Page (
	id       STRING KEY,
	book_id  STRING NOT NULL,
	contents TEXT NOT NULL,
	number   INTEGER NOT NULL,
	CONSTRAINT unique_book_number UNIQUE(book_id, number)
);
