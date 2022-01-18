"use strict";

Object.defineProperty(exports, "__esModule", {
  value: true
});

var _v = require("uuid/v4");

var _v2 = _interopRequireDefault(_v);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

let User = class User {
  constructor() {
    this.users = [];
  }

  find() {
    // Returns a list of all users
    return this.users;
  }

  findById(userId) {
    // Find user by Id
    // Returns user, or null if not present
    var findUser = null;
    for (var i = 0; i < this.users.length; i++) {
      var user = this.users[i];
      if (user.id === usersId) {
        findUser = user;
        break;
      }
    }
    //maybe return null or value.
    return findUser;
  }

  create(user) {
    // Create a new user
    // Return created user
    // Generate the id and overwrite any id that may be present in user
    let newId = (0, _v2.default)();
    let myUser = {
      id: newId,
      name: user.name,
      address: user.address,
      age: user.age
    };
    this.users.push(myUser);
    return myUser;
  }

  findOneAndUpdate(user) {
    // Find user and update
    // If user does not exist, create it using Id provided
    // Return true if user was updated, false if user was created
    var findUser = null;
    for (var i = 0; i < this.users.length; i++) {
      var currentUser = this.users[i];
      if (currentUser.id === user.id) {
        findUser = currentUser;
        break;
      }
    }
    if (findUser !== null) {
      findUser.name = user.name;
      findUser.address = user.address;
      findUser.age = user.age;
      return true;
    } else {
      let myUser = {
        id: user.id,
        name: user.name,
        address: user.address,
        age: user.age
      };
      this.users.push(myUser);
      return false;
    }
  }

  remove(user) {
    console.log("model-->user:", user);
    // Remove user if exists with the Id provided
    // Return true if removed
    // Return false if did user not exist
    var findUser = null;
    for (var i = 0; i < this.users.length; i++) {
      var currentUser = this.users[i];
      if (currentUser.id === user.id) {
        findUser = currentUser;
        break;
      }
    }

    if (findUser === null) {
      return false;
    } else {
      let newUsers = [];
      for (var i = 0; i < this.users.length; i++) {
        var currentUser = this.users[i];
        if (currentUser.id !== user.id) {
          newUsers.push(currentUser);
        }
      }
      //let result = users.filter(user=> user.id !== id);
      this.users = newUsers;
      return true;
    }
  }
};
exports.default = new User();
//# sourceMappingURL=users.model.js.map
