-------------------------------------------------
-- afficher les tables
-------------------------------------------------
select name
from sqlite_master 
where type ='table' 
and name not like 'sqlite_%';
-------------------------------------------------
-- supprimer la table users
-------------------------------------------------
drop table users;
-------------------------------------------------
-- creer la table users
-------------------------------------------------
create table users(
id integer primary key autoincrement not null,
email char(256),
password char(256)
);
-------------------------------------------------
-- inserer des donnees dans la table users
-------------------------------------------------
insert into users(email, password)
values("alice@readydev.com", "alice_pass");
insert into users(email, password)
values("pierre@readydev.com", "pierre_pass");
insert into users(email, password)
values("paul@readydev.com", "paul_pass");
-------------------------------------------------
-- afficher les donnees de la table users
-------------------------------------------------
select * from users;
-------------------------------------------------
-- cryptage du mot de passe de la table users
-------------------------------------------------
update users set password = md5(email || '-' || password);
-------------------------------------------------
