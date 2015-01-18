var passport = require('passport');
var FacebookStrategy = require('passport-facebook').Strategy; //Facebook
var GoogleStrategy = require('passport-google-oauth').OAuth2Strategy; //Google
var User = require('../models/User');
var secrets = require('./secrets');
var domain = "http://pillbox.ngrok.com";

// Passport session setup.
//   To support persistent login sessions, Passport needs to be able to
//   serialize users into and deserialize users out of the session.  Typically,
//   this will be as simple as storing the user ID when serializing, and finding
//   the user by ID when deserializing.  However, since this example does not
//   have a database of user records, the complete Windows Live profile is
//   serialized and deserialized.
passport.serializeUser(function(user, done) {
  done(null, user.id);
});

passport.deserializeUser(function(id, done) {
  User.findOne({
        id: id
    }, function(err, user) {
    done(err, user);
  });
});

passport.use(new FacebookStrategy({
    clientID: secrets.facebook.clientID,
    clientSecret: secrets.facebook.clientSecret,
    callbackURL: domain + "/auth/facebook/callback"
  },
  function(accessToken, refreshToken, profile, done) {
    User.findOne({
        id: profile.id
    }, function(err, user) {
        if (err) {
            return done(err);
        }
        //No user was found... so create a new user with values from Facebook (all the profile. stuff)
        if (!user) {
          // console.log(profile);
          user = new User({
              id: profile.id,
              name: profile.displayName,
              email: profile.emails[0].value,
              provider: profile.provider,
              //now in the future searching on User.findOne({'facebook.id': profile.id } will match because of this next line
              facebook: profile._json
          });
          user.save(function(err) {
              if (err) console.log(err);
              return done(err, user);
          });
        } else {
            //found user. Return
            return done(err, user);
        }
    });
  }
));

passport.use(new GoogleStrategy({
    clientID: secrets.google.clientID,
    clientSecret: secrets.google.clientSecret,
    callbackURL: domain + "/auth/google/callback"
  },
  function(accessToken, refreshToken, profile, done) {
    User.findOne({
        id: profile.id
    }, function(err, user) {
        if (err) {
            return done(err);
        }
        //No user was found... so create a new user with values from Google (all the profile. stuff)
        if (!user) {
          console.log(profile);
          user = new User({
              id: profile.id,
              name: profile.displayName,
              email: profile.emails[0].value,
              provider: profile.provider,
              //now in the future searching on User.findOne({'google.id': profile.id } will match because of this next line
              google: profile._json
          });
          user.save(function(err) {
              if (err) console.log(err);
              return done(err, user);
          });
        } else {
            //found user. Return
            return done(err, user);
        }
    });
  }
));
