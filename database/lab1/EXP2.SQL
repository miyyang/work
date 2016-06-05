USE LEARNSQL

/*
	CREATING TABLES
*/

DROP TABLE Cars;

DROP TABLE Motorcycle;

DROP TABLE Ownership;

CREATE TABLE IF NOT EXISTS Cars(
	licence VARCHAR(10) NOT NULL,
	owner VARCHAR(10) NOT NULL,
	model VARCHAR(10) NOT NULL
	);

CREATE TABLE IF NOT EXISTS Motorcycle(
	licence VARCHAR(10) NOT NULL,
	owner VARCHAR(10) NOT NULL,
	model VARCHAR(10) NOT NULL
	);

INSERT INTO Cars VALUES
	('C011', 'P1', 'M1'),
	('C012', 'P3', 'M1'),
	('C013', 'P4', 'M3'),
	('C014', 'P4', 'M2'),
	('C015', 'P5', 'M3');

INSERT INTO Motorcycle VALUES
	('M011', 'P2', 'M7'),
	('M012', 'P3', 'M8'),
	('M013', 'P4', 'M7'),
	('M014', 'P4', 'M8');

SELECT * FROM Cars;

SELECT * FROM Motorcycle;

/* List people who own a car but do not own a motorcycle. */

SELECT DISTINCT Cars.owner 
FROM Cars LEFT JOIN Motorcycle 	
ON Cars.owner = Motorcycle.owner 	
WHERE Motorcycle.owner IS NULL;

/* List people who own a car and also own a motorcycle. */

SELECT DISTINCT Cars.owner 
FROM Cars INNER JOIN Motorcycle 
ON Cars.owner = Motorcycle.owner;

/* List the number of cars owned by each person. */

SELECT owner, COUNT(licence) AS CAR_NUM
FROM Cars
GROUP BY owner;

/* Write ONE SQL request that populates the table :
	Ownership(owner, numberOfCars, numberOfMotorcycles) */

CREATE TABLE IF NOT EXISTS Ownership(
	owner VARCHAR(10),
	numberOfCars TINYINT UNSIGNED NOT NULL,
	numberOfMotorcycles TINYINT UNSIGNED NOT NULL
	);

INSERT INTO Ownership
SELECT OWNER, SUM(C1) AS numberOfCars, SUM(C2) AS numberOfMotorcycles
FROM (
SELECT OWNER, COUNT(LICENCE) AS C1, '' AS C2 FROM CARS GROUP BY OWNER 
UNION
SELECT OWNER, '', COUNT(LICENCE) FROM Motorcycle GROUP BY OWNER
) AS TT 
GROUP BY OWNER;

SELECT * FROM Ownership;