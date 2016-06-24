class Removedirty < ActiveRecord::Migration
  def change
    
    remove_column "reservations", "exist"
  end
end
