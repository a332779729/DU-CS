'use strict';

Object.defineProperty(exports, "__esModule", {
  value: true
});
exports.router = undefined;

var _express = require('express');

var _express2 = _interopRequireDefault(_express);

var _users = require('./users.controller');

var controller = _interopRequireWildcard(_users);

function _interopRequireWildcard(obj) { if (obj && obj.__esModule) { return obj; } else { var newObj = {}; if (obj != null) { for (var key in obj) { if (Object.prototype.hasOwnProperty.call(obj, key)) newObj[key] = obj[key]; } } newObj.default = obj; return newObj; } }

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

let router = _express2.default.Router();

// GET methods
router.get('/', controller.index);
router.get('/:id', controller.show);

// POST method
router.post('/', controller.create);

// PUT method
router.put('/:id', controller.update);

// DELETE method
router.delete('/:id', controller.destroy);

exports.router = router;
//# sourceMappingURL=index.js.map
