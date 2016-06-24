USE LEARNSQL

/*
	CREATING TABLE INGREDIENTS & DISH & CALORIES
*/

DROP TABLE Ingredients;

DROP TABLE Dish;

DROP TABLE Calories;

DROP TABLE ShoppingList;

CREATE TABLE IF NOT EXISTS Dish (
	food VARCHAR(2) NOT NULL,
	cuisine ENUM('Chinese', 'Japanese', 'Indian') NOT NULL
	);

CREATE TABLE IF NOT EXISTS Ingredients (
	food VARCHAR(2) NOT NULL,
	ingredient ENUM('beef', 'butter', 'cumin', 'pork', 'rice', 
		'fish', 'cabbage', 'tomato') NOT NULL,
	quantity TINYINT UNSIGNED NOT NULL
	);

CREATE TABLE IF NOT EXISTS Calories (
	ingredient ENUM('beef', 'butter', 'cumin', 'pork', 'rice', 
		'fish', 'cabbage', 'tomato') NOT NULL,
	quantity TINYINT UNSIGNED NOT NULL,
	calories SMALLINT UNSIGNED NOT NULL
	);

INSERT INTO Dish VALUES
	('CA', 'Chinese'),
	('CB', 'Chinese'),
	('JA', 'Japanese'),
	('IA', 'Indian'),
	('IB', 'Indian');

INSERT INTO Ingredients VALUES
	('CA', 'beef', 30),
	('CA', 'tomato', 50),
	('CA', 'cumin', 5),
	('CB', 'cumin', 10),
	('CB', 'pork', 30),
	('CB', 'butter', 5),
	('CB', 'rice', 15),
	('JA', 'rice', 50),
	('JA', 'fish', 30),
	('JA', 'butter', 16),
	('IA', 'beef', 45),
	('IA', 'butter', 20),
	('IA', 'rice', 30),
	('IB', 'pork', 30),
	('IB', 'cumin', 10),
	('IB', 'cabbage', 20);

INSERT INTO Calories VALUES
	('beef', 2, 500),
	('butter', 1, 750),
	('cumin', 2, 35),
	('pork', 1, 330),
	('rice', 10, 700),
	('fish', 1, 180),
	('cabbage', 5, 30),
	('tomato', 1, 30);

SELECT * FROM Dish;

SELECT * FROM Ingredients;

SELECT * FROM Calories;

/* Find the foods that include more than 16 units of butter. */

SELECT DISTINCT Dish.food
FROM Dish INNER JOIN Ingredients
ON Dish.food = Ingredients.food
WHERE Ingredients.ingredient = 'pork' AND quantity > 16;

/* Find the cuisines that use cumin as an ingredient (in at least one dish). */

SELECT DISTINCT cuisine
FROM Dish INNER JOIN Ingredients
ON Dish.food = Ingredients.food
WHERE ingredient = 'cumin';

/* Change the ingredients for foods so that they include no more than 16 units of butter. 
	(If they already include more than 16 units of butter, then change it to 16 units of butter.) */

UPDATE Ingredients 
SET quantity = 16 
WHERE quantity > 16 AND ingredient = 'butter';

SELECT * FROM Ingredients;

/* Remove beef from all Indian (cuisine) dishes.  */

DELETE Ingredients.*
FROM Ingredients INNER JOIN Dish
ON Ingredients.food = Dish.food
WHERE cuisine = 'Indian' AND ingredient = 'beef';

SELECT * FROM Ingredients;

/* Create a summary table, ShoppingList that contains the total quantity of each ingredient 
used by all the dishes for each cuisine.  */

CREATE TABLE IF NOT EXISTS ShoppingList (
	cuisine ENUM('Chinese', 'Japanese', 'Indian') NOT NULL,
	ingredient ENUM('beef', 'butter', 'cumin', 'pork', 'rice', 
		'fish', 'cabbage', 'tomato') NOT NULL,
	total_calories FLOAT UNSIGNED NOT NULL
	);

INSERT INTO ShoppingList
SELECT cuisine, ingredient, SUM(quantity) AS total_quantity
FROM Ingredients INNER JOIN Dish
ON Ingredients.food = Dish.food
GROUP BY cuisine, ingredient;

SELECT * FROM SHOPPINGLIST;

/* For each dish, set the number of calories equal to the total number of calories 
	for the entire dish. Note that the quantity in relation Calories need not match the quantity in Ingredients, 
	so you need to compute calories per unit. */

SELECT food, sum(calories / Calories.quantity * Ingredients.quantity) AS Calories_Sum
FROM Ingredients INNER JOIN Calories 
ON Calories.ingredient = Ingredients.ingredient
GROUP BY food;
