'use strict';

Object.defineProperty(exports, "__esModule", {
  value: true
});
exports.User = undefined;

var _mongoose = require('mongoose');

var _mongoose2 = _interopRequireDefault(_mongoose);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

let Schema = _mongoose2.default.Schema;

/*
  This section declares the schemas for the different documents
  that will be used
 */

// This schema represents the fullName of the user
let fullNameSchema = Schema({
  // firstName is a simple String type that is required
  firstName: { type: String, required: true },
  // lastName is a simple String type that is required
  lastName: { type: String, required: true }
});

// This is the main user schema
let userSchema = Schema({
  /*
   fullName is a subdocument of User, and will be stored
   in the same document as the User itself.
   Unlike a populated document, this doesn't require an
   ObjectId reference and the schema for name can be
   referenced directly
  */
  fullName: fullNameSchema,
  // userName is a simple String type that is required
  userName: { type: String, required: true, unique: true },
  // emailAddress is a simple String type that is required
  emailAddress: { type: String, required: true, unique: true }

});

/*
  This section creates interactive models from the defined schemas
  above so that you can perform Create Read Update and Delete (CRUD)
  operations against the schemas.
  NOTE since the nameSchema is embedded within userSchema, it does NOT have
  to be created as a model!
 */

let User = _mongoose2.default.model('User', userSchema);

// Export the one created User
exports.User = User;
//# sourceMappingURL=users.model.js.map
