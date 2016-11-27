CREATE TABLE Variable (
	name   STRING KEY,
	value  STRING
);

CREATE TABLE User (
	id       STRING KEY,
	name     STRING NOT NULL,
	filename STRING NOT NULL
);
