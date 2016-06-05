class Addresvinfo < ActiveRecord::Migration
  def change
    add_column "reservations", "resvinfo", :string
  end
end
