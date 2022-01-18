import mongoose from 'mongoose';
let Schema = mongoose.Schema;

/*
  This section declares the schemas for the different documents
  that will be used
 */

// This schema represents the address of the user
let addressSchema = Schema({
  // addressLine1 is a simple String type that is required
  addressLine1: {type: String, required: true},
  // addressLine2 is a simple String type that is NOT required
  addressLine2: {type: String, required: false},
  // city is a simple String type that is required
  city: {type: String, required: true},
  // state is a simple String type that is required
  state: {type: String, required: true},
  // zip is a simple Number type that is required
  zip: {type: Number, required: true}
});

// This schema represents the name of the user
let nameSchema = Schema({
  // firstName is a simple String type that is required
  firstName: {type: String, required: true},
  // middleName is a simple String type that is not required
  middleName: {type: String, required: false},
  // lastName is a simple String type that is required
  lastName: {type: String, required: true}
});

// This is the main user schema
let userSchema = Schema({
  // Age is a simple number type that is required
  age: {type: Number, required: true},
  /*
   Address is referenced as a 'foreign key' using the objectId
   of an address stored in a separate collection.
   The address will be populated by Mongoose using 'Population'
   http://mongoosejs.com/docs/populate.html
  */
  address: {type: Schema.Types.ObjectId, ref: 'Address'},
  /*
   Name is a subdocument of User, and will be stored
   in the same document as the User itself.
   Unlike a populated document, this doesn't require an
   ObjectId reference and the schema for name can be
   referenced directly
  */
  name: nameSchema
});

/*
  This section creates interactive models from the defined schemas
  above so that you can perform Create Read Update and Delete (CRUD)
  operations against the schemas.
  NOTE since the nameSchema is embedded within userSchema, it does NOT have
  to be created as a model!
 */
let Address = mongoose.model('Address', addressSchema);
let User = mongoose.model('User', userSchema);

// Export the two created models, Address and User
export {Address, User};
