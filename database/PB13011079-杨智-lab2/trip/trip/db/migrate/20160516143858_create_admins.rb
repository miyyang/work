class CreateAdmins < ActiveRecord::Migration
  def change
    create_table :admins do |t|
      t.string :adminname
      t.string :password

      t.timestamps null: false
    end
  end
end
