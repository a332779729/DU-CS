
//Inside index.js create the basic outline that will let you define your REST API:
import express from 'express';

import * as controller from './users.controller';

//import * as users from './users';

let router = express.Router();

router.get('/', controller.index);
router.get('/:id', controller.show);

router.post('/', controller.create);

//Add a router.put(...)
router.put('/:id', controller.upsert);

//router.delete(...)
router.delete('/:id', controller.destroy);

export {router};
