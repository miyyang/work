class HotelsController < ApplicationController
  before_action :confirm_logged_in_admin, except: [:book, :unbook]
  before_action :confirm_logged_in_user, only: [:book]
  before_action :confirm_logged_in, only: [:unbook]
  before_action :set_hotel, only: [:edit]

  def edit
  end
  
  def new
    @hotel = Hotel.new
  end
  
  def create
    @hotel = Hotel.new(hotel_params)
    if @hotel.save
      flash[:notice] = "Hotel created successfully"
    else
      flash[:notice] = "Hotel created unsuccessfully"
    end
    redirect_to(:controller => 'admins', :action => 'manage')
  end

  def update
    @hotel = Hotel.find(params[:id])
    if @hotel.update_attributes(hotel_params)
      flash[:notice] = "Hotel updated successfully"
      redirect_to(:controller => 'admins', :action => 'manage')
    else 
      render('new')
    end
  end

  def destroy
    Hotel.delete(params[:id])
    Reservation.delete_all("resvtype = 2 and resvkey = #{params[:id]}")
    flash[:notice] = "Hotel deleted successfully"
    redirect_to(:controller => 'admins', :action => 'manage')
  end

  def book
    @hotel = Hotel.find(params[:hotel_id])
    if @hotel.update_attributes(:numavail => @hotel.numavail - 1)
      @res = Reservation.new(:custid => params[:user_id], :resvtype => 2, :resvkey => params[:hotel_id])
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
    @hotel = Hotel.find(@res.resvkey)
    @hotel.update_attributes(:numavail => @hotel.numavail + 1)
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
    def set_hotel
      @hotel = Hotel.find(params[:id])
    end
    def hotel_params
      params.require(:hotel).permit(:location, :price, :numrooms, :numavail)
    end
end
