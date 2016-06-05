class CarsController < ApplicationController
  before_action :confirm_logged_in_admin, except: [:book, :unbook]
  before_action :confirm_logged_in_user, only: [:book]
  before_action :confirm_logged_in, only: [:unbook]
  before_action :set_car, only: [:edit]

  def edit
  end
  
  def new
    @car = Car.new
  end
  
  def create
    @car = Car.new(car_params)
    if @car.save
      flash[:notice] = "Car created successfully"
    else
      flash[:notice] = "Car created unsuccessfully"
    end
    redirect_to(:controller => 'admins', :action => 'manage')
  end

  def update
    @car = Car.find(params[:id])
    if @car.update_attributes(car_params)
      flash[:notice] = "Car updated successfully"
      redirect_to(:controller => 'admins', :action => 'manage')
    else 
      render('new')
    end
  end

  def destroy
    Car.delete(params[:id])
    Reservation.delete_all("resvtype = 3 and resvkey = #{params[:id]}")
    flash[:notice] = "Car deleted successfully"
    redirect_to(:controller => 'admins', :action => 'manage')
  end

  def book
    @car = Car.find(params[:car_id])
    if @car.update_attributes(:numavail => @car.numavail - 1)
      @res = Reservation.new(:custid => params[:user_id], :resvtype => 3, :resvkey => params[:car_id])
      if @res.save
        flash[:notice] = "book successfully"
      else
        flash[:notice] = "book unsuccessfully"
      end
    else
        flash[:notice] = "book unsuccessfully"
    end
    if (params[:from] == 'manage')
      redirect_to(:controller => 'users', :action => 'manage', :id => params[:user_id ])
    elsif (params[:from] == 'check')
      redirect_to(:controller => 'users', :action => 'check', :user_id => params[:user_id], :fromcity => params[:fromcity],
          :arivcity => params[:arivcity])
    end
  end
  
  def unbook
    @res = Reservation.find(params[:res_id])
    @car = Car.find(@res.resvkey)
    @car.update_attributes(:numavail => @car.numavail + 1)
    @res.destroy
    flash[:notice] = "unbook successfully"
    if (params[:from] == '0')
      redirect_to(:controller => 'admins', :action => 'manage')
    elsif (params[:from] == '1')
      redirect_to(:controller => 'users', :action => 'manage', :id => params[:id])
    else
      redirect_to(:controller => 'err', :action => 'err')
    end
  end
  
  private    
    def set_car
      @car = Car.find(params[:id])
    end
    def car_params
      params.require(:car).permit(:location, :price, :numcars, :numavail)
    end
end
