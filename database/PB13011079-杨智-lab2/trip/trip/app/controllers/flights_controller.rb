class FlightsController < ApplicationController
  before_action :confirm_logged_in_admin, except: [:book, :unbook]
  before_action :confirm_logged_in_user, only: [:book]
  before_action :confirm_logged_in, only: [:unbook]
  before_action :set_flight, only: [:edit]

  def edit
  end
  
  def new
    @flight = Flight.new
  end
  
  def create
    @flight = Flight.new(flight_params)
    if @flight.save
      flash[:notice] = "Flight created successfully"
    else
      flash[:notice] = "Flight created unsuccessfully"
    end
    redirect_to(:controller => 'admins', :action => 'manage')
  end

  def update
    @flight = Flight.find(params[:id])
    if @flight.update_attributes(flight_params)
      flash[:notice] = "Flight updated successfully"
      redirect_to(:controller => 'admins', :action => 'manage')
    else 
      render('new')
    end
  end

  def destroy
    Flight.delete(params[:id])
    Reservation.delete_all("resvtype = 1 and resvkey = #{params[:id]}")
    flash[:notice] = "Flight deleted successfully"
    redirect_to(:controller => 'admins', :action => 'manage')
  end


  def book
    @flight = Flight.find(params[:flight_id])
    if @flight.update_attributes(:numavail => @flight.numavail - 1)
      @res = Reservation.new(:custid => params[:user_id], :resvtype => 1, :resvkey => params[:flight_id])
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
      redirect_to(:controller => 'users', :action => 'check', :user_id => params[:user_id], :fromcity => @flight.fromcity,
          :arivcity => @flight.arivcity)
    end
  end
  
  def unbook
    @res = Reservation.find(params[:res_id])
    @flight = Flight.find(@res.resvkey)
    @flight.update_attributes(:numavail => @flight.numavail + 1)
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
    def set_flight
      @flight = Flight.find(params[:id])
    end
    def flight_params
      params.require(:flight).permit(:flightnum, :price, :numseats, :numavail, :fromcity, :arivcity)
    end
end