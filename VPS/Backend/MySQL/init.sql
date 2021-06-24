DROP DATABASE meteoData;
ALTER USER 'root' IDENTIFIED WITH mysql_native_password BY 'Aa123456';
FLUSH PRIVILEGES;

CREATE DATABASE meteoData;

USE meteoData;
CREATE TABLE teplota(
    Cas TIMESTAMP,
    Teplota FLOAT(4,2),
    Vlhkost FLOAT(4,2),
    Tlak FLOAT(4,2),
    CO2 FLOAT(4,2),
    Dest TINYINT(1),
    IDZarizeni INT
);
CREATE TABLE pohyb(
    Cas TIMESTAMP,
    Pohyb TINYINT(1),
    IDZarizeni INT
);
CREATE TABLE errors(
    Cas TIMESTAMP,
    ID INT,
    IDZarizeni VARCHAR(10),
    Zaznam VARCHAR(255)
);