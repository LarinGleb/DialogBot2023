DROP TABLE IF EXISTS EventsDemo;

CREATE TABLE EventsDemo (
	idEvent SERIAL PRIMARY KEY,
	nameEvent TEXT,
	dataEvent DATE
);

INSERT INTO eventsdemo(nameevent, dataevent) VALUES('test', '01.02.2020');

SELECT * FROM eventsdemo;