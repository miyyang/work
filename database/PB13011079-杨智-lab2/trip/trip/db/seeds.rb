# This file should contain all the record creation needed to seed the database with its default values.
# The data can then be loaded with the rake db:seed (or created alongside the db with db:setup).
#
# Examples:
#
#   cities = City.create([{ name: 'Chicago' }, { name: 'Copenhagen' }])
#   Mayor.create(name: 'Emanuel', city: cities.first)

Admin.create([{adminname: 'root', password: 'xingzuan2'}])

User.create([{username: 'user1', password: 'xingzuan2'}])
User.create([{username: 'user2', password: 'xingzuan2'}])

Car.create([{location: 'beijing', price: 10, numcars: 100, numavail: 99}])
Car.create([{location: 'shanghai', price: 9, numcars: 200, numavail: 198}])
Car.create([{location: 'guangzhou', price: 8, numcars: 150, numavail: 150}])
Car.create([{location: 'shenzhen', price: 8, numcars: 150, numavail: 150}])

Hotel.create([{location: 'beijing', price: 1000, numrooms: 50, numavail: 50}])
Hotel.create([{location: 'shanghai', price: 900, numrooms: 100, numavail: 99}])
Hotel.create([{location: 'guangzhou', price: 800, numrooms: 70, numavail: 70}])
Hotel.create([{location: 'shenzhen', price: 800, numrooms: 70, numavail: 70}])

Flight.create([{flightnum: 'CA001', price: 1000, numseats: 50, numavail: 49, fromcity: 'guangzhou', arivcity: 'beijing'}])
Flight.create([{flightnum: 'CA002', price: 1000, numseats: 50, numavail: 50, fromcity: 'shanghai', arivcity: 'guangzhou'}])
Flight.create([{flightnum: 'CA003', price: 1000, numseats: 50, numavail: 50, fromcity: 'shenzhen', arivcity: 'guangzhou'}])
Flight.create([{flightnum: 'CA004', price: 1000, numseats: 50, numavail: 50, fromcity: 'beijing', arivcity: 'wuhan'}])
Flight.create([{flightnum: 'CA005', price: 1000, numseats: 50, numavail: 50, fromcity: 'wuhan', arivcity: 'beijing'}])
Flight.create([{flightnum: 'CA006', price: 1000, numseats: 50, numavail: 50, fromcity: 'shanxi', arivcity: 'shenzhen'}])

#1为预订航班，2为预订宾馆房间，3为预订出租车
Reservation.create([{custid: 1, resvtype: 1, resvkey: 1}])
Reservation.create([{custid: 1, resvtype: 2, resvkey: 2}])
Reservation.create([{custid: 1, resvtype: 3, resvkey: 2}])
Reservation.create([{custid: 2, resvtype: 3, resvkey: 2}])
Reservation.create([{custid: 1, resvtype: 3, resvkey: 1}])