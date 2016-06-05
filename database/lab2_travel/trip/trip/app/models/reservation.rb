class Reservation < ActiveRecord::Base
  has_many :hotels
  validates_associated :hotels
  has_many :cars
  validates_associated :cars
  has_many :flights
  validates_associated :flights
end
