'use strict';

Object.defineProperty(exports, "__esModule", {
    value: true
});

exports.default = function (app) {
    // All undefined asset or api routes should return a 404
    app.use('/api/users', users.router);
    app.use('/api/recipes', recipes.router);
    app.use('/api/reviews', reviews.router);

    app.route('/:url(api|auth|components|app|bower_components|assets)/*').get(_errors2.default[404]);

    // All other routes should redirect to the app.html
    //app.use('/api/users', users.router);
    app.route('/*').get((req, res) => {
        res.sendFile(_path2.default.resolve(`${app.get('appPath')}/app.html`));
    });
};

var _users = require('./api/users');

var users = _interopRequireWildcard(_users);

var _recipes = require('./api/recipes');

var recipes = _interopRequireWildcard(_recipes);

var _reviews = require('./api/reviews');

var reviews = _interopRequireWildcard(_reviews);

var _errors = require('./components/errors');

var _errors2 = _interopRequireDefault(_errors);

var _path = require('path');

var _path2 = _interopRequireDefault(_path);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

function _interopRequireWildcard(obj) { if (obj && obj.__esModule) { return obj; } else { var newObj = {}; if (obj != null) { for (var key in obj) { if (Object.prototype.hasOwnProperty.call(obj, key)) newObj[key] = obj[key]; } } newObj.default = obj; return newObj; } }
//# sourceMappingURL=routes.js.map
