CREATE TABLE Variables (
	name	STRING NOT NULL PRIMARY KEY,
	value	STRING
);

CREATE TABLE Words (
	word	STRING NOT NULL,
	translation	STRING NOT NULL,
	hits	INTEGER DEFAULT 0,
	PRIMARY KEY (word, translation)
);
