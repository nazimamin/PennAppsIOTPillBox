var express = require("express");
var session = require('express-session');
var app = express();
var http = require("http").createServer(app);
var bodyParser = require("body-parser");

var passport = require('passport');
// var _ = require("underscore");
// var MongoStore = require('connect-mongo')({ session: session });
var mongoose = require('mongoose');

/**
 * API keys and Passport configuration.
 */

var secrets = require('./config/secrets');
var passportConf = require('./config/passport');

/**
 * Connect to MongoDB.
 */

// mongoose.connect(secrets.db);
// mongoose.connection.on('error', function() {
//   console.error('MongoDB Connection Error. Make sure MongoDB is running.');
// });
// var User = require('./models/User');

app.set("ipaddr", "127.0.0.1");
app.set("port", 8080);

app.set("views", __dirname + "/views");
app.set("view engine", "jade");
//Specify where the static content is
app.use(express.static("public", __dirname + "/public"));

app.use(bodyParser.json());

// app.use(session({secret: secrets.sessionSecret, resave: true, saveUninitialized: true}));
// Initialize Passport!  Also use passport.session() middleware, to support
// persistent login sessions (recommended).
app.use(passport.initialize());
app.use(passport.session());

//route homepage
app.get("/", function(req, res) {
  res.render("index");
});

app.get("/login", function(req, res) {
  res.render("login");
});

app.get("/register", function(req, res) {
  res.render("register");
});

// GET /auth/facebook
//   Use passport.authenticate() as route middleware to authenticate the
//   request.  The first step in Facebook authentication will involve
//   redirecting the user to facebook.com.  After authorization, Facebook
//   will redirect the user back to this application at
//   /auth/facebook/callback
app.get('/auth/facebook',
  passport.authenticate('facebook', { scope: ['email'] }),
  function(req, res){
    // The request will be redirected to Facebook for authentication, so
    // this function will not be called.
  });

// GET /auth/facebook/callback
//   Use passport.authenticate() as route middleware to authenticate the
//   request.  If authentication fails, the user will be redirected back to the
//   login page.  Otherwise, the primary route function function will be called,
//   which will redirect the user to the hub page.
app.get('/auth/facebook/callback', 
  passport.authenticate('facebook', { failureRedirect: '/login' }),
  function(req, res) {
    res.redirect('/');
  });

//Same thing for Google
app.get('/auth/google',
  passport.authenticate('google'),
  function(req, res){
    // The request will be redirected to Google for authentication, so
    // this function will not be called.
  });

app.get('/auth/google/return', 
  passport.authenticate('google', { failureRedirect: '/login' }),
  function(req, res) {
    res.redirect('/');
  });

app.get('/logout', function(req, res){
  req.logout();
  res.redirect('/');
});

// //route boards
// app.get("/board", function(req, res) {
//   res.render("board", { user: req.user });
// });

// app.get("/hub", function(req, res) {
//   if (!req.user) {
//     res.redirect('/');
//   }
//   req.user._id = req.user._id.toHexString();
//   console.log(req.user)
//   res.render("hub", { user: req.user });
// });

http.listen(app.get("port"), app.get("ipaddr"), function() {
  console.log("Server up and running. Go to http://" + app.get("ipaddr") + ":" + app.get("port"));
});