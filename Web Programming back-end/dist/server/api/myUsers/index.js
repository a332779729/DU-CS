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

//import * as users from './users';

//Inside index.js create the basic outline that will let you define your REST API:
let router = _express2.default.Router();

router.get('/', controller.index);
router.get('/:id', controller.show);

router.post('/', controller.create);

//Add a router.put(...)
router.put('/:id', controller.upsert);

//router.delete(...)
router.delete('/:id', controller.destroy);

exports.router = router;
//# sourceMappingURL=index.js.map
