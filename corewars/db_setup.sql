CREATE TABLE users_info (
	user_id SERIAL PRIMARY KEY,
	login varchar (20) NOT NULL,
	password varchar (32) NOT NULL, 
	best_score integer);
CREATE TABLE warriors (
	warrior_id SERIAL,
	user_id int4,
	warrior_name varchar (32) NOT NULL, 
	points integer, 
	PRIMARY KEY (warrior_id), 
	FOREIGN KEY (user_id) REFERENCES users_info(user_id));
