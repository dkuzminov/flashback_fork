CREATE TABLE Variable (
	name   STRING NOT NULL,
	value  STRING
);

CREATE TABLE User (
	id       STRING KEY,
	name     STRING NOT NULL,
	filename STRING NOT NULL
);
