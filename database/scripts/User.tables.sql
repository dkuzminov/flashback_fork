CREATE TABLE Variable (
	name   STRING KEY,
	value  STRING
);

CREATE TABLE Bookmark (
	id       STRING KEY,
	book_id  STRING NOT NULL,
	page_id  STRING NOT NULL
);
