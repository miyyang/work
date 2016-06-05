class CreateCars < ActiveRecord::Migration
  def change
    create_table :cars do |t|
      t.string :location
      t.integer :price
      t.integer :numcars
      t.integer :numavail

      t.timestamps null: false
    end
  end
end
