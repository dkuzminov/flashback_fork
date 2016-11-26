INSERT INTO Variable (name, value) VALUES
('Language', 'Spanish');


INSERT INTO Book (id, name, author) VALUES
('countdown', 'Countdown to Spanish', ''),
('coronel', 'El Coronel no tiene quien le escriba', 'Gabriel Garcia Marquez');

INSERT INTO Page (id, book_id, contents, number) VALUES
('page1', 'countdown', '<p>Placeholder</p>', 1),
('page1', 'coronel', '<p>Placeholder</p>', 1);
