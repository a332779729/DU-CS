'use strict';

/*eslint no-process-env:0*/

// Development specific configuration
// ==================================
module.exports = {
    // MongoDB connection options
    mongo: {
        useMongoClient: true,
        uri: process.env.MONGODB_URI || 'mongodb://web2-mongodb/web2-chezhang'
    },

    // Seed database on startup
    seedDB: true
};
//# sourceMappingURL=development.js.map
