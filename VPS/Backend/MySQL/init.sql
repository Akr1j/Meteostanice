DROP DATABASE meteoData;
ALTER USER 'root' IDENTIFIED WITH mysql_native_password BY 'Aa123456';
FLUSH PRIVILEGES;

CREATE DATABASE meteoData;

USE meteoData;
CREATE TABLE teplota(
    TeplotaCas TIMESTAMP,
    TeplotaTeplota FLOAT(2),
    TeplotaVlhkost FLOAT(2),
    TeplotaTlak FLOAT(2),
    TeplotaCO2 FLOAT(2),
    Dest TINYINT(1)
);
CREATE TABLE pohyb(
    Cas TIMESTAMP,
    Pohyb TINYINT(1)
);