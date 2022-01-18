'use strict';

import {Review} from './reviews.model';
import {User} from '../users/users.model';
import {Recipe} from '../recipes/recipes.model';

/**
* Find all Review
*/
export function index(req, res) {
  Review.find()
    .populate('userCreatingReview')
    .exec()
    .then(function(reviews) {
      res.json({
        reviews
      });
    })
    .catch(function(err) {
      res.status(500);
      res.send(err);
    });
}



/**
* Find review details by review Id
* @param {String} id : review Id
*/
export function show(req, res) {
  Review.findById(req.params.id)
    .populate('userCreatingReview')
    .exec()
    .then(function(existingReview) {
      /*
       findById will return null if the object was not found
       This if check will evaluate to false for a null review
      */
      if(existingReview) {
        // Review was found by Id
        res.status(200);
        res.json(existingReview);
      } else {
        // Review was not found
        res.status(404);
        res.json({message: 'Not Found'});
      }
    })
    .catch(function(err) {
      res.status(400);
      res.send(err);
    });
}



/**
* Create a new Review
* @param {String} reviewDescription : Review description
* @param {Number} reviewRating : Review rating (i.e. number of stars)
* @param {String} userId : User ID
* @param {String} recipeId : Recipe ID
*/
export async function create(req, res) {

  let userId = req.body.userId;
  let recipeId = req.body.recipeId;
  let user;

  //find user by user Id
  try{
    console.log(userId);
    user = await User.findById(userId);
    console.log(user);
    if(!user){
      res.status(400);
      res.json({message: 'Not Found User'});
      return;
    }

  }catch(err){
    console.log(err);
    res.status(400);
    res.send(err);
    return;
  }

  //find the recipes by recipe's ID
  let recipe;
  try{
    console.log(recipeId);
    recipe = await Recipe.findById(recipeId);
    console.log(recipe);
    if(!recipe){
      res.status(400);
      res.json({message: 'Not Found Recipe'});
      return;
    }

  }catch(err){
    console.log(err);
    res.status(400);
    res.send(err);
    return;
  }


  let review = {
    reviewDescription: req.body.reviewDescription,
    reviewRating: req.body.reviewRating,
    userCreatingReview: user
  };

  //save review to mongoose
  try{
    let createdReview = await Review.create(review);
    //take review to recipes
    recipe.userReviews.push(createdReview);
    recipe.increment().save();

    res.status(201);
    res.json(createdReview);

  }catch(err){
    console.log(err);
    res.status(400);
    res.send(err);
  }

}



/**
* Update a review
* @param {String} id : Review ID
* @param {String} reviewDescription : Review description
* @param {Number} reviewRating : Review rating (i.e. number of stars)
*/
export function update(req, res) {
  // Start by trying to find the review by its id
  Review.findById(req.params.id)
    .exec()
    // Update review
    .then(function(existingReview) {
      // If review exists, update all fields of the object
      console.log(existingReview);
      if(existingReview) {
        existingReview.reviewDescription = req.body.reviewDescription;
        existingReview.reviewRating = req.body.reviewRating;

        //update review commend not need update the user information
        //existingReview.userCreatingReview = req.body.userCreatingReview;

        /*
         Promise.all takes an array of promises as an argument
         It ensures that all the promises in the array have successfully resolved before
         continuing the promise chain. It will pass to the next .then an array of results, one
         for each promise that was passed
        */
        return Promise.all([
          existingReview.increment().save()
        ]);
      } else {
        // Review was not found
        return existingReview;
      }
    })
    // This .then will be called after the Promise.all resolves, or be called with null if the review was not found
    .then(function(savedObjects) {
      // savedObjects should be defined if Promise.all was invoked (review was found)
      if(savedObjects) {
        res.status(200);
        // The order of responses are guaranteed to be the same as the order of the promises, so we can assume
        // the second element of the array is the result of the review update
        res.json(savedObjects[1]);
      } else {
        // Review was not found
        res.status(404);
        res.json({message: 'Not Found'});
      }
    })
    // Error encountered during the save of the review
    .catch(function(err) {
      console.log(err);
      res.status(400);
      res.send(err);
    });
}



/**
* Remove a review
* @param {String} id : Review ID
*/
export function destroy(req, res) {
  Review.findById(req.params.id)
    .exec()
    .then(function(existingReview) {
      if(existingReview) {
        /*
          This is the equivalent of cascading delete in a relational database
          If the review was found, remove both the review object and the address object from
          their respective collections. Only record the delete as successful if both objects
          are deleted
         */
        return Promise.all([
          existingReview.remove()
        ]);
      } else {
        return existingReview;
      }
    })
    // Delete was successful
    .then(function(deletedReview) {
      if(deletedReview) {
        res.status(204).send();
      } else {
        // review was not found
        res.status(404);
        res.json({message: 'Not Found'});
      }
    })
    // Review delete failed
    .catch(function(err) {
      res.status(400);
      res.send(err);
    });
}
