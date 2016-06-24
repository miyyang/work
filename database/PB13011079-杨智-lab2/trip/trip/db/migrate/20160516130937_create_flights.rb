class CreateFlights < ActiveRecord::Migration
  def change
    create_table :flights do |t|
      t.string :flightnum
      t.integer :price
      t.integer :numseats
      t.integer :numavail
      t.string :fromcity
      t.string :arivcity

      t.timestamps null: false
    end
  end
end
