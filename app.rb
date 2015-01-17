require 'bundler' #require bundler
Bundler.require #require everything in bundler in gemfile
require 'pry'
require 'pg'
require 'sinatra/activerecord'
require './lib/login.rb'

get '/' do
	erb :index
end

post '/' do
	@username = params[:username]
	@password = params[:password]
	erb :index, :locals => {'username' => @username, 'password' => @password}
end