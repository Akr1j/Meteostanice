DROP DATABASE meteoData;
ALTER USER 'root' IDENTIFIED WITH mysql_native_password BY 'Aa123456';
FLUSH PRIVILEGES;

CREATE DATABASE meteoData;

USE meteoData;
CREATE TABLE teplota(
    Cas TIMESTAMP,
    Teplota FLOAT(4,2),
    Vlhkost FLOAT(2,2),
    Tlak INT,
    CO2 INT,
    Dest TINYINT(1)
);
CREATE TABLE pohyb(
    Cas TIMESTAMP,
    Pohyb TINYINT(1)
);
CREATE TABLE errors(
    Cas TIMESTAMP,
    ID INT,
    Misto VARCHAR(10),
    Zaznam VARCHAR(255)
);