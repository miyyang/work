class ReservationsController < ApplicationController
  before_action :confirm_logged_in_admin
  before_action :set_reservation, only: [:edit]

  def edit
  end
  
  def new
    @reservation = Reservation.new
  end
  
  def create
    @reservation = Reservation.new(reservation_params)
    if @reservation.save
      flash[:notice] = "Reservation created successfully"
    else
      flash[:notice] = "Reservation created unsuccessfully"
    end
    redirect_to(:controller => 'admins', :action => 'manage')
  end

  def update
    @reservation = Reservation.find(params[:id])
    if @reservation.update_attributes(reservation_params)
      flash[:notice] = "Reservation updated successfully"
      redirect_to(:controller => 'admins', :action => 'manage')
    else 
      render('new')
    end
  end

  def destroy
    @reservation = Reservation.find(params[:id])
    @reservation.destroy
    flash[:notice] = "Reservation deleted successfully"
    redirect_to(:controller => 'admins', :action => 'manage')
  end


  private    
    def set_reservation
      @reservation = Reservation.find(params[:id])
    end
    def reservation_params
      params.require(:reservation).permit(:custid, :resvtype, :resvkey)
    end
end
