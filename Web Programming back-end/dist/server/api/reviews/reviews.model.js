'use strict';

Object.defineProperty(exports, "__esModule", {
  value: true
});
exports.Review = undefined;

var _mongoose = require('mongoose');

var _mongoose2 = _interopRequireDefault(_mongoose);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

let Schema = _mongoose2.default.Schema;

/*
  This section declares the schemas for the different documents
  that will be review
 */

// This is the main review schema
let reviewSchema = Schema({
  // reviewDescription is a simple String type that is required
  reviewDescription: { type: String, required: true },
  // reviewRating is a simple Number type that is required, and I design the review rating's range is 0-5 number.
  reviewRating: { type: Number, min: 0, max: 5, required: true },
  // dateCreated is a simple Date type, this should be set by the server
  dateCreated: { type: Date, default: Date.now },
  /*
   userCreatingReview is referenced as a 'foreign key' using the objectId
   of an User stored in a separate collection.
   The userCreatingReview will be populated by Mongoose using 'Population'
   http://mongoosejs.com/docs/populate.html
  */
  userCreatingReview: { type: Schema.Types.ObjectId, ref: "User" }

});

/*
  This section creates interactive models from the defined schemas
  above so that you can perform Create Read Update and Delete (CRUD)
  operations against the schemas.
  NOTE since the nameSchema is embedded within reviewSchema, it does NOT have
  to be created as a model!
 */
let Review = _mongoose2.default.model('Review', reviewSchema);

// Export the one created Review
exports.Review = Review;
//# sourceMappingURL=reviews.model.js.map
