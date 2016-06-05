class ApplicationController < ActionController::Base
  # Prevent CSRF attacks by raising an exception.
  # For APIs, you may want to use :null_session instead.
  protect_from_forgery with: :exception
  private
  def confirm_logged_in_admin 
    unless session[:user_id] && session[:priv] == 'admin'
      flash[:notice] = "Please log in."
      redirect_to(:controller => 'admins', :action => 'login')
      return false 
    else 
      return true
    end
  end
  
  def confirm_logged_in_user
    unless session[:user_id] && session[:priv] == 'user'
      flash[:notice] = "Please log in."
      redirect_to(:controller => 'users', :action => 'login')
      return false 
    else 
      return true
    end
  end  
  
  def confirm_logged_in
    unless session[:user_id]
      flash[:notice] = "Please log in."
      redirect_to(:controller => 'users', :action => 'login')
      return false 
    else 
      return true
    end
  end
end
