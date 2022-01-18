/**
 * Main application routes
 */

//Inside server/routes.js register your routes with the main application

//import * as users from './api/users.js';
//I find the users file do not have router
import * as users from './api/users';
import * as recipes from './api/recipes';
import * as reviews from './api/reviews';

import errors from './components/errors';
import path from 'path';

export default function(app) {
    // All undefined asset or api routes should return a 404
    app.use('/api/users', users.router);
    app.use('/api/recipes', recipes.router);
    app.use('/api/reviews', reviews.router);

    app.route('/:url(api|auth|components|app|bower_components|assets)/*')
        .get(errors[404]);

    // All other routes should redirect to the app.html
    //app.use('/api/users', users.router);
    app.route('/*')
        .get((req, res) => {
            res.sendFile(path.resolve(`${app.get('appPath')}/app.html`));
        });


}
