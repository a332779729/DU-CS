'use strict';

import {User} from './users.model';

/**
* Find all User
*/
export function index(req, res) {
  /*
   The pattern you see below where one function is
   called right after the other is called method chaining,
   and is a common practice in JavaScript and many other languages
   https://en.wikipedia.org/wiki/Method_chaining
   */
  User.find()
    /*
       For each user object, populate the address attribute.
       This will make all the attributes available in the address
       accessible as though the address were a subdocument by joining
       the two tables for you
       http://mongoosejs.com/docs/populate.html
    */
    /*
       exec() runs the query and returns a promise object.
       Promises are a cleaner way to chain asynchronous actions together than
       callbacks because, instead of nesting functions within functions, you can
       chain function calls together and pass the return value from one function
       as the argument to the next! It also allows you to have one method to handle
       exceptions, instead of having to provide them in each callback function you write
       http://www.javascriptkit.com/javatutors/javascriptpromises.shtml
       http://bluebirdjs.com/docs/why-promises.html
    */
    .exec()
    // This then method will only be called if the query was successful, so no need to error check!
    .then(function(users) {
      res.json({
        users
      });
    })
    /*
     Any errors encountered here must be server side, since there are no arguments to the find
     Return 500 (server error) and send the error encountered back to the requester
    */
    .catch(function(err) {
      res.status(500);
      res.send(err);
    });
}



/**
* Find user details by user Id
* @param {String} id : user Id
*/
export function show(req, res) {
  User.findById(req.params.id)
    .exec()
    .then(function(existingUser) {
      /*
       findById will return null if the object was not found
       This if check will evaluate to false for a null user
      */
      if(existingUser) {
        // User was found by Id
        res.status(200);
        res.json(existingUser);
      } else {
        // User was not found
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
* Create a new User
* @param {Object} fullName : Full Name
    {
      @param {String} firstName, First name
      @param {String} lastName Last name
    }
* @param {String} userName : Username
* @param {String} emailAddress : Email address
*/
export async function create(req, res) {
  /*
    In this function we are taking the request body
    As it was sent and using it as the JSON for the address
    and user objects.
    Since address is stored in a separate collection from user
    we must create each document individually, and then associate
    the address to the user after we know its id
  */

  let user = req.body;

  //Exceeding basic requirements
  //i used the async/await function
  try{
    let createdUser = await User.create(user);

    res.status(201);
    res.json(createdUser);

  }catch(err){
    res.status(400);
    res.send(err);
  }


  // Start off by saving the address
  //await User.create(user)

    // User and Address saved successfully! return 201 with the created user object
    /*.then(function(createdUser) {
      res.status(201);
      res.json(createdUser);
    })
    // An error was encountered during either the save of the address or the save of the user
    .catch(function(err) {
      res.status(400);
      res.send(err);
    });*/
}



/**
* Update a user
* @param {String} id : User ID
* @param {Object} fullName : Full Name
    {
      @param {String} firstName, First name
      @param {String} lastName Last name
    }
* @param {String} userName : Username
* @param {String} emailAddress : Email address
*/
export function update(req, res) {
  // Start by trying to find the user by its id
  User.findById(req.params.id)
    .exec()
    // Update user and address
    .then(function(existingUser) {
      // If user exists, update all fields of the object
      console.log(existingUser);
      if(existingUser) {
        existingUser.fullName.firstName = req.body.fullName.firstName;
        existingUser.fullName.lastName = req.body.fullName.lastName;
        existingUser.userName = req.body.userName;
        existingUser.emailAddress = req.body.emailAddress;
        /*
         Promise.all takes an array of promises as an argument
         It ensures that all the promises in the array have successfully resolved before
         continuing the promise chain. It will pass to the next .then an array of results, one
         for each promise that was passed
        */
        return Promise.all([
          existingUser.increment().save()
        ]);
      } else {
        // User was not found
        return existingUser;
      }
    })
    // This .then will be called after the Promise.all resolves, or be called with null if the user was not found
    .then(function(savedObjects) {
      // savedObjects should be defined if Promise.all was invoked (user was found)
      if(savedObjects) {
        res.status(200);
        // The order of responses are guaranteed to be the same as the order of the promises, so we can assume
        // the second element of the array is the result of the user update
        res.json(savedObjects[1]);
      } else {
        // User was not found
        res.status(404);
        res.json({message: 'Not Found'});
      }
    })
    // Error encountered during the save of the user or address
    .catch(function(err) {
      //console.log(err);
      res.status(400);
      res.send(err);
    });
}



/**
* Remove a user
* @param {String} id : User ID
*/
export function destroy(req, res) {
  User.findById(req.params.id)
    .exec()
    .then(function(existingUser) {
      if(existingUser) {
        /*
          This is the equivalent of cascading delete in a relational database
          If the user was found, remove both the user object and the address object from
          their respective collections. Only record the delete as successful if both objects
          are deleted
         */
        return Promise.all([
          existingUser.remove()
        ]);
      } else {
        return existingUser;
      }
    })
    // Delete was successful
    .then(function(deletedUser) {
      if(deletedUser) {
        res.status(204).send();
      } else {
        // User was not found
        res.status(404);
        res.json({message: 'Not Found'});
      }
    })
    // Address or user delete failed
    .catch(function(err) {
      res.status(400);
      res.send(err);
    });
}
