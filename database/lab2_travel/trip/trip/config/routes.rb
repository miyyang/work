Rails.application.routes.draw do
  match '/admins/create', to: 'admins#create', via:'post'
  match '/admins/destroy/:id',to: 'admins#destroy', via:'destroy'
  match '/users/destroy/:id',to: 'users#destroy', via:'destroy'
  match '/users/new/:id', to: 'users#new', via:'get'
  match '/cars/destroy/:id',to: 'cars#destroy', via:'destroy'
  match '/cars/edit/:id',to: 'cars#edit', via:'edit'
  match '/flights/destroy/:id',to: 'flights#destroy', via:'destroy'
  match '/flights/edit/:id',to: 'flights#edit', via:'edit'
  match '/hotels/destroy/:id',to: 'hotels#destroy', via:'destroy'
  match '/hotels/edit/:id',to: 'hotels#edit', via:'edit'
  match '/users/create', to: 'users#create', via:'post'
  match '/cars/create', to: 'cars#create', via:'post'
  match '/hotels/create', to: 'hotels#create', via:'post'
  match '/flights/create', to: 'flights#create', via:'post'
  match '/users/attempt:id', to: 'users#attempt_login', via:'post'
  match '/admins/attempt:id', to: 'admins#attempt_login', via:'post'
  get 'admins', :to => "admins#login"
  get 'users', :to => "users#login"
  match ':controller(/:action(/:id(.:format)))', :via => [:get, :post]
  #match ':controller(/:action(/:id))', :via => [:get]
  #resources :users
  resources :admins
  resources :cars
  resources :hotels
  resources :flights
  resources :reservations
  #match ':controller(/:action(/:id(.:format)))', :via => :all
  # The priority is based upon order of creation: first created -> highest priority.
  # See how all your routes lay out with "rake routes".

  # You can have the root of your site routed with "root"
  # root 'welcome#index'

  # Example of regular route:
  #   get 'products/:id' => 'catalog#view'

  # Example of named route that can be invoked with purchase_url(id: product.id)
  #   get 'products/:id/purchase' => 'catalog#purchase', as: :purchase

  # Example resource route (maps HTTP verbs to controller actions automatically):
  #   resources :products

  # Example resource route with options:
  #   resources :products do
  #     member do
  #       get 'short'
  #       post 'toggle'
  #     end
  #
  #     collection do
  #       get 'sold'
  #     end
  #   end

  # Example resource route with sub-resources:
  #   resources :products do
  #     resources :comments, :sales
  #     resource :seller
  #   end

  # Example resource route with more complex sub-resources:
  #   resources :products do
  #     resources :comments
  #     resources :sales do
  #       get 'recent', on: :collection
  #     end
  #   end

  # Example resource route with concerns:
  #   concern :toggleable do
  #     post 'toggle'
  #   end
  #   resources :posts, concerns: :toggleable
  #   resources :photos, concerns: :toggleable

  # Example resource route within a namespace:
  #   namespace :admin do
  #     # Directs /admin/products/* to Admin::ProductsController
  #     # (app/controllers/admin/products_controller.rb)
  #     resources :products
  #   end
end
