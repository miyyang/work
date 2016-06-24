class CreateReservations < ActiveRecord::Migration
  def change
    create_table :reservations do |t|
      t.string :custname
      t.integer :resvtype
      t.string :resvkey

      t.timestamps null: false
    end
  end
end
