class Setresvid < ActiveRecord::Migration
  def change
    remove_column "reservations", "resvinfo"
    remove_column "reservations", "resvkey"
    add_column "reservations", "resvkey", :integer
  end
end
