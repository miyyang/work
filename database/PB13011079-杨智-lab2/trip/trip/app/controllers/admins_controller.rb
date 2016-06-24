class AdminsController < ApplicationController
  
  before_action :confirm_logged_in_admin, :except => [:login, :attempt_login, :logout]

  def login
    @namedis = Admin.name
  end

  def attempt_login
    if params[:username].present? && params[:password].present? 
      found_user = Admin.where(:adminname => params[:username]).first
      if found_user
          authorized_user = found_user.authenticate(params[:password])
      end
    end
    if authorized_user
      session[:user_id] = authorized_user.id
      session[:username] = authorized_user.adminname
      session[:priv] = 'admin'
      flash[:notice] = "Login successful."
      redirect_to(:action => 'manage')
    else 
      flash[:notice] = "Invalid username or password."
      redirect_to(:action => 'login')
    end
  end

  def logout
      session[:user_id] = nil
      session[:username] = nil
      session[:priv] = nil
      flash[:notice] = "Logged out."
      redirect_to(:action => 'login')
  end
  
  
  ##########################################################
  
  def manage
    @admins = Admin.all
    @cars = Car.all
    @hotels = Hotel.all
    @flights = Flight.all
    @reservations = Reservation.all.group_by{|s| s.custid}
    @users = User.all
  end

  def new
    @admin = Admin.new
  end

  def create
    @admin = Admin.new(admin_params)
    if @admin.save
      flash[:notice] = "AdminUser created successfully"
    else
      flash[:notice] = "AdminUser created unsuccessfully"
    end
    redirect_to(:action => 'manage')
  end

  def destroy
    @admin = Admin.find(params[:id])
    @admin.destroy
    flash[:notice] = "AdminUser deleted successfully"
    redirect_to(:action => 'manage')
  end
  
  private
    def admin_params
      params.require(:admin).permit(:adminname, :password)
    end
end
