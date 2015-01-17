var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'Express' });
});

router.get('/login', function(req, res) {
    res.render('login', { title: 'IOTPillBox' })
});

router.get('/register', function(req, res) {
    res.render('register', { title: 'IOTPillBox' })
});

module.exports = router;
