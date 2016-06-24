class UseCustidInstead < ActiveRecord::Migration
  def up
    remove_column "reservations", "custname"
    add_column "reservations", "custid", :integer
  end
    def down
    add_column "reservations", "custname", :string
    remove_column "reservations", "custid"
  end
end
