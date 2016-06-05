class CreateHotels < ActiveRecord::Migration
  def change
    create_table :hotels do |t|
      t.string :location
      t.integer :price
      t.integer :numrooms
      t.integer :numavail

      t.timestamps null: false
    end
  end
end
