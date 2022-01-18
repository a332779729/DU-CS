'use strict';

Object.defineProperty(exports, "__esModule", {
  value: true
});
exports.Recipe = undefined;

var _mongoose = require('mongoose');

var _mongoose2 = _interopRequireDefault(_mongoose);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

let Schema = _mongoose2.default.Schema;

/*
  This section declares the schemas for the different documents
  that will be recipe
 */

// This schema represents the ingredient of the recipe
let ingredientSchema = Schema({
  // nutrition is a simple String type that is required
  nutrition: { type: String, required: true },
  // poison is a simple String type that is required
  poison: { type: String, required: true }
});

// This is the main user schema
let recipeSchema = Schema({
  // name is a simple String type that is required
  name: { type: String, required: true },
  // description is a simple String type that is required
  description: { type: String, required: true },
  // pictureURL is a simple String type that is required
  pictureURL: { type: String, required: true },
  // prepTime is a simple Number type that is required, and I design the min number is 0
  prepTime: { type: Number, min: 0, required: true },
  // cookingTime is a simple Number type that is required, and I design the min number is 0
  cookingTime: { type: Number, min: 0, required: true },
  // directions is a array and the every element is a simple String type that is required
  directions: [{ type: String, required: true }],
  /*
   ingredients is a subdocument of Recipe, and will be stored
   in the same document as the Recipe itself.
   Unlike a populated document, this doesn't require an
   ObjectId reference and the schema for name can be
   referenced directly
  */
  ingredients: [ingredientSchema],
  /*
   userReviews is referenced as a 'foreign key' using the objectId
   of an Review stored in a separate collection.
   The userReviews will be populated by Mongoose using 'Population'
   http://mongoosejs.com/docs/populate.html
  */
  userReviews: [{ type: Schema.Types.ObjectId, ref: "Review" }]

});

/*
  This section creates interactive models from the defined schemas
  above so that you can perform Create Read Update and Delete (CRUD)
  operations against the schemas.
  NOTE since the nameSchema is embedded within reviewSchema, it does NOT have
  to be created as a model!
 */
let Recipe = _mongoose2.default.model('Recipe', recipeSchema);

// Export the one created Recipe
exports.Recipe = Recipe;
//# sourceMappingURL=recipes.model.js.map
