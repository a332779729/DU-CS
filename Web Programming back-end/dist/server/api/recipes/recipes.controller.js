'use strict';

Object.defineProperty(exports, "__esModule", {
  value: true
});

var _promise = require('babel-runtime/core-js/promise');

var _promise2 = _interopRequireDefault(_promise);

exports.index = index;
exports.show = show;
exports.create = create;
exports.update = update;
exports.destroy = destroy;

var _recipes = require('./recipes.model');

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

/**
* Find all Recipes
*/
function index(req, res) {
  _recipes.Recipe.find().populate('userReviews').exec()
  // This then method will only be called if the query was successful, so no need to error check!
  .then(function (recipes) {
    res.json({
      recipes
    });
  }).catch(function (err) {
    res.status(500);
    res.send(err);
  });
}

/**
* Find review details by recipe Id
* @param {String} id : recipe Id
*/
function show(req, res) {
  _recipes.Recipe.findById(req.params.id).populate('userReviews').exec().then(function (existingRecipe) {
    /*
     findById will return null if the object was not found
     This if check will evaluate to false for a null recipe
    */
    if (existingRecipe) {
      // Recipe was found by Id
      res.status(200);
      res.json(existingRecipe);
    } else {
      // Recipe was not found
      res.status(404);
      res.json({ message: 'Not Found' });
    }
  }).catch(function (err) {
    res.status(400);
    res.send(err);
  });
}

/**
* Create a new Recipe
* @param {String} name : Name of recipe
* @param {String} description : Description of recipe
* @param {String} pictureURL : Picture URL for recipe
* @param {Number} prepTime : Prep time (minutes)
* @param {Number} cookingTime : Cooking time (minutes)
* @param {String} directions : Array of directions (i.e. step by step directions)
* @param {Object} ingredients : Array of ingredients
    {
      @param {String} nutrition, nutrition
      @param {String} poison poison
    }
*/
async function create(req, res) {
  /*
    In this function we are taking the request body
    As it was sent and using it as the JSON for the address
    and recipe objects.
    Since address is stored in a separate collection from recipe
    we must create each document individually, and then associate
    the address to the recipe after we know its id
  */
  let recipe = req.body;

  //Exceeding basic requirements
  //i used the async/await function
  try {
    let createdRecipe = await _recipes.Recipe.create(recipe);

    res.status(201);
    res.json(createdRecipe);
  } catch (err) {
    //console.log(err);
    res.status(400);
    res.send(err);
  }
}

/**
* Update a recipe
* @param {String} id : Recipe ID
* @param {String} name : Name of recipe
* @param {String} description : Description of recipe
* @param {String} pictureURL : Picture URL for recipe
* @param {Number} prepTime : Prep time (minutes)
* @param {Number} cookingTime : Cooking time (minutes)
* @param {String} directions : Array of directions (i.e. step by step directions)
* @param {Object} ingredients : Array of ingredients
* @param {Object} ingredients : Array of ingredients
    {
      @param {String} nutrition, nutrition
      @param {String} poison poison
    }
*/
function update(req, res) {
  // Start by trying to find the recipe by its id
  _recipes.Recipe.findById(req.params.id).exec()
  // Update recipe and address
  .then(function (existingRecipe) {
    // If recipe exists, update all fields of the object
    console.log(existingRecipe);
    if (existingRecipe) {
      existingRecipe.name = req.body.name;
      existingRecipe.description = req.body.description;
      existingRecipe.pictureURL = req.body.pictureURL;
      existingRecipe.prepTime = req.body.prepTime;
      existingRecipe.cookingTime = req.body.cookingTime;
      existingRecipe.directions = req.body.directions;
      existingRecipe.ingredients.nutrition = req.body.ingredients.nutrition;
      existingRecipe.ingredients.poison = req.body.ingredients.poison;
      //existingRecipe.userReviews = req.body.userReviews;
      /*
       Promise.all takes an array of promises as an argument
       It ensures that all the promises in the array have successfully resolved before
       continuing the promise chain. It will pass to the next .then an array of results, one
       for each promise that was passed
      */
      return _promise2.default.all([existingRecipe.increment().save()]);
    } else {
      // Recipe was not found
      return existingRecipe;
    }
  })
  // This .then will be called after the Promise.all resolves, or be called with null if the recipe was not found
  .then(function (savedObjects) {
    // savedObjects should be defined if Promise.all was invoked (recipe was found)
    if (savedObjects) {
      res.status(200);
      // The order of responses are guaranteed to be the same as the order of the promises, so we can assume
      // the second element of the array is the result of the recipe update
      res.json(savedObjects[1]);
    } else {
      // Recipe was not found
      res.status(404);
      res.json({ message: 'Not Found' });
    }
  })
  // Error encountered during the save of the recipe
  .catch(function (err) {
    console.log(err);
    res.status(400);
    res.send(err);
  });
}

/**
* Remove a recipe
* @param {String} id : Recipe ID
*/
function destroy(req, res) {
  _recipes.Recipe.findById(req.params.id).exec().then(function (existingRecipe) {
    if (existingRecipe) {
      /*
        This is the equivalent of cascading delete in a relational database
        If the recipe was found, remove both the recipe object and the address object from
        their respective collections. Only record the delete as successful if both objects
        are deleted
       */
      return _promise2.default.all([existingRecipe.remove()]);
    } else {
      return existingRecipe;
    }
  })
  // Delete was successful
  .then(function (deletedRecipe) {
    if (deletedRecipe) {
      res.status(204).send();
    } else {
      // Recipe was not found
      res.status(404);
      res.json({ message: 'Not Found' });
    }
  })
  // Recipe delete failed
  .catch(function (err) {
    res.status(400);
    res.send(err);
  });
}
//# sourceMappingURL=recipes.controller.js.map
