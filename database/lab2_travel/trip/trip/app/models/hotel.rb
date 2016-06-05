class Hotel < ActiveRecord::Base
  validates :location, presence: true, uniqueness: true
  validates_numericality_of :numavail, :greater_than_or_equal_to => 0
end
