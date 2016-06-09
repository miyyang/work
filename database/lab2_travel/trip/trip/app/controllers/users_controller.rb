class UsersController < ApplicationController
  before_action :confirm_logged_in_user, :except => [:login, :attempt_login, :logout, :destroy, :create, :new]
  
  def login
    @namedis = User.name
  end
  
  def attempt_login
    if params[:username].present? && params[:password].present? 
      found_user = User.where(:username => params[:username]).first
      if found_user
          authorized_user = found_user.authenticate(params[:password])
      end
    end
    if authorized_user
      session[:user_id] = authorized_user.id
      session[:username] = authorized_user.username
      session[:priv] = 'user'
      flash[:notice] = "Login successful."
      redirect_to(:action => 'manage', :id => found_user.id)
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
    @user = User.find(params[:id])
    @cars = Car.all
    @hotels = Hotel.all
    @flights = Flight.all
    @reservations = Reservation.find_by_sql("select * from reservations where custid = '#{@user.id}'")
  end

  def new
    @user = User.new
  end

  def create
    @user = User.new(user_params)
    if @user.save
      flash[:notice] = "User created successfully"
    else
      flash[:notice] = "User created unsuccessfully"
    end
    redirect_to(:action => 'login', :id => @user.id)
  end
  
  def destroy
    @user = User.find(params[:id])
    @user.destroy
    Reservation.delete_all("custid = #{params[:id]}")
    flash[:notice] = "User deleted successfully"
    redirect_to(:controller => 'admins', :action => 'manage')
  end
  
  def check
    @user = User.find(params[:user_id])
    @flight = Flight.where(:fromcity => params[:fromcity], :arivcity => params[:arivcity])
    @fromcar = Car.where(:location => params[:fromcity]).first
    @tocar = Car.where(:location => params[:arivcity]).first
    @hotel = Hotel.where(:location => params[:arivcity]).first
    @reservations = Reservation.find_by_sql("select * from reservations where custid = '#{@user.id}'")
  end
  
  def check_path
    @user = User.find(params[:user_id])
    @startnode = params[:fromcity]
    @endnode = params[:arivcity]
    @userfli = Flight.find_by_sql("select * from flights where id in (select resvkey from reservations where custid = '#{@user.id}' and resvtype = 1)")
  end

  def search
    @user = User.find(params[:user_id])
    @reservations = Reservation.find_by_sql("select * from reservations where custid = '#{@user.id}'")
  end
  
  private
    def user_params
      params.require(:user).permit(:username, :password)
    end
end
