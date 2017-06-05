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

INSERT INTO users_info (login,password) VALUES ('zpr','cae2c166cd6f1094ef1609cae3721759');
INSERT INTO warriors (warrior_name,points,user_id) VALUES ('projekt',0,1);
