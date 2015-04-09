DROP DATABASE IF EXISTS mil_svr93;
DROP USER IF EXISTS mil_svr93;
CREATE USER mil_svr93 WITH PASSWORD '39rvs_lim';
CREATE DATABASE mil_svr93 OWNER mil_svr93;
\c mil_svr93;
CREATE TABLE satellites (
  id smallserial,
  apogee_height integer /* meters */
);
GRANT ALL PRIVILEGES ON satellites TO mil_svr93;
INSERT INTO satellites VALUES
  (DEFAULT, '918100'); 
INSERT INTO satellites VALUES
  (DEFAULT, '1044000');
