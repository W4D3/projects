drop table if exists Hotel;
drop table if exists Room;
drop table if exists Booking;
drop table if exists Guest;

create table Hotel(
    hotelNo int(4),
    hotelName varchar(30),
    city varchar(20));

create table Room(
       roomNo int(3),
       hotelNo int(4),
       type varchar(9),
       price dec(5,2));

create table Booking(
       hotelNo int(4),
       guestNo int(7),
       dateFrom date,
       dateTo date,
       roomNo int(3));

create table Guest(
       guestNo int(7),
       guestName varchar(30),
       guestAddress varchar(50));

insert into Hotel values(1, 'Grosvenor Hotel', 'London');
insert into Hotel values(2, 'Holiday Inn', 'Knoxville');
insert into Hotel values(3, 'Hilton', 'Knoxville');
insert into Hotel values(4, 'Marriott', 'Memphis');

insert into Room values(100, 1, 'double', 89.99);
insert into Room values(200, 1, 'family', 109.99);
insert into Room values(300, 1, 'king', 135.50);
insert into Room values(500, 2, 'king', 205);
insert into Room values(100, 2, 'penthouse', 249.99);
insert into Room values(200, 2, 'double', 99.99);
insert into Room values(300, 2, 'double', 109.99);
insert into Room values(400, 2, 'family', 149.99);
insert into Room values(400, 1, 'penthouse', 899.99);

insert into Booking values(1, 20, '2015-09-11', '2015-09-14', 100);
insert into Booking values(1, 21, '2015-09-18', '2015-09-19', 100);
insert into Booking values(1, 22, '2015-09-23', '2015-10-28', 100);
insert into Booking values(1, 21, '2015-09-2', '2015-10-01', 100);

insert into Booking values(1, 30, '2015-09-11', '2015-09-14', 200);
insert into Booking values(1, 31, '2015-09-15', '2015-09-20', 200);
insert into Booking values(1, 32, '2015-09-27', '2015-09-30', 200);
insert into Booking values(1, 33, '2015-09-1', '2015-09-02', 200);

insert into Booking values(1, 41, '2015-09-05', '2015-09-06', 300);
insert into Booking values(1, 42, '2015-09-15', '2015-09-20', 300);
insert into Booking values(1, 33, '2015-09-20', '2015-09-25', 300);
insert into Booking values(1, 21, '2015-09-25', '2015-10-02', 300);
insert into Booking values(1, 33, '2015-09-06', '2015-09-10', 300);

insert into Booking values(2, 21, '2015-09-18', '2015-09-25', 100);
insert into Booking values(2, 42, '2015-09-05', '2015-09-28', 500);
insert into Booking values(2, 31, '2015-09-09', '2015-12-11', 300);
insert into Booking values(2, 31, '2015-09-11', '2015-09-12', 300);

insert into Guest values(20, 'Brad Vander Zanden', 'Knoxville, TN');
insert into Guest values(21, 'Minnie Mouse', 'Orlando, FL');
insert into Guest values(22, 'Wily Coyote', 'Phoenix, AZ');

insert into Guest values(30, 'Daffy Duck', 'Knoxville, TN');
insert into Guest values(31, 'Winnie The Pooh', 'Phoenix, AZ');
insert into Guest values(32, 'Pluto', 'Phoenix, AZ');
insert into Guest values(33, 'Snow White', 'Orlando, FL');

insert into Guest values(40, 'Bugs Bunny', 'Ithaca, NY');
insert into Guest values(41, 'Quickdraw McGraw', 'Townsend, TN');
insert into Guest values(42, 'Cinderella', 'Orlando, FL');
