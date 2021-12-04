const path = require('path');

module.exports = {
	paths: (paths) => ({
		...paths,
		appIndexJs: path.join(__dirname, '../ui/index.tsx'),
		appTypeDeclarations: path.join(__dirname, 'react-app-env.d.ts'),
	}),
};
