-------------------------------------------------
select name
from sqlite_master 
where type ='table' 
and ame not like 'sqlite_%';
-------------------------------------------------
create table users(
id integer primary key autoincrement not null,
email char(256),
password char(256)
);
-------------------------------------------------
insert into users(email, password)
values("gerard@readydev.com", "gerpass")
-------------------------------------------------
select * from users
-------------------------------------------------
