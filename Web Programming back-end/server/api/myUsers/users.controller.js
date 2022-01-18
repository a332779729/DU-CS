import uuidv4 from 'uuid/v4';

import User from './users.model';

/*let users = [{"id":101,"name":"Fight Club","year":1999,"rating":8.1},
{"id":102,"name":"Inception","year":2010,"rating":8.7},
{"id":103,"name":"The Dark Knight","year":2008,"rating":9},
{"id":104,"name":"12 Angry Men","year":1957,"rating":8.9}];*/

//let users = [];

//Create a new exported function listContents that takes two parameters,
//req and res (provided by Express.js when a web request comes in),
//that sends the users array as json to the res object

//function named listContents it can check all users data.
export function index(req, res) {
   /* Implementation here */
   res.status(200);
   res.json(User.find());
}

//Create a second exported function, findOne, that takes two parameters, req and res (provided by Express.js when a web request comes in),
//that extracts a parameter named id from the req object and searches the users list for a user with a matching id

//function named findOne it can check one user data.
export function show(req, res) {
   /* Implementation here */
   var id = req.params.id;
   var findUser = User.findById(id);
   /*for(var i=0; i <users.length; i++){
     var user = users[i];
     if(user.id === id){
       findUser = user;
       break;
     }
   }*/
  if(findUser === null){
    res.status(404);
    res.json({message: 'Not Found'});
  }else{
    res.status(200);
    res.json(findUser);
  }
}

//Create a new exported function createUser that takes two parameters,
//req and res (provided by Express.js when a web request comes in), that adds a new user object to the in-memory users list

//function named createUser it can create a user data.
export function create(req, res) {
   /* Implementation here */
   //let id = uuidv4();
   let name = req.body.name;
   let address = req.body.address;
   let age = req.body.age;
   if(typeof(name) === "string" && typeof(address) ==="string" && typeof(age) ==="number" && age > 0){
     let user = {"id":null,"name":name,"address":address,"age":age};
     res.status(201);
     res.json(User.create(user));
   }else{
     res.status(400);
     res.json({message: 'request is not valid'});
   }
}

//Create a new exported function updateUser that takes two parameters, req and res.
//The method updates a user object if it exists, or creates a new user if it does not exist.
//The method returns the updated or created user as json to the res object with the HTTP status code OK (200) for an update and CREATED (201) for an insert

//function named updateUser it can updata a user data.
export function upsert(req, res) {
  var id = req.params.id;
  let name = req.body.name;
  let address = req.body.address;
  let age = req.body.age;

  /*var findUser = null;
  for(var i=0; i <users.length; i++){
    var user = users[i];
    if(user.id === id){
      findUser = user;
      break;
    }
  }
  if(findUser !== null){
    findUser.name = name;
    findUser.address = address;
    findUser.age = age;
    res.status(200);
    res.json(findUser);
  }else{
    if(typeof(name) === "string" && typeof(address) ==="string" &&typeof(age) ==="number" && age > 0){
      let user = {"id":id, "name":name, "adress":address, "age":age};
      users.push(user);
      res.status(201);
      res.json(user);
    }
  }*/

  let myUser = ({
    id : id,
    name: name,
    address: address,
    age: age
  });

  var result = User.findOneAndUpdate(myUser)
  if(result == true){
    res.status(200);
    res.json(myUser);
  }else{
      //let user = {"id":id, "name":name, "adress":address, "age":age};
      res.status(201);
      res.json(myUser);

  }
}

//Create a second exported function removeUser that takes two parameters, req and res, that removes a user from the in-memory store

////function named removeUser it can remove a user data.
export function destroy(req, res){
  var id = req.params.id;
  console.log("controller--->id:",id);
  //var findUser = null;
  /*for(var i=0; i <users.length; i++){
    var user = users[i];
    if(user.id === id){
      findUser = user;
      break;
    }
  }

  if(findUser === null){
    res.status(404);
    res.json({message: "Not Found"});
  }else{
    let newUsers = [];
    for(var i=0; i<users.length; i++){
      var user = users[i];
      if(user.id !== id){
        newUsers.push(user);
      }
    }
    //let result = users.filter(user=> user.id !== id);
    users = newUsers;
    res.status(204).send();
    res.json(users);
  }*/
  let myUser = ({
    id : id
  });
  var result = User.remove(myUser);
  if(result == false){
    res.status(404);
    res.json({message: "Not Found"});
  }else{
    res.status(204).send();
    //res.json(myUser);
  }
}


















//res.status(404);
//res.json({message: 'Not Found'});
