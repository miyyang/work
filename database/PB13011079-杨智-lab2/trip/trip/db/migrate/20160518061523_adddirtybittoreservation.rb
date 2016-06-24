class Adddirtybittoreservation < ActiveRecord::Migration
  def change
    add_column "reservations", "exist", :boolean
  end
end
