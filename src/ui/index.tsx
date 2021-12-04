import './index.css';

import ReactDOM from 'react-dom';
import { StrictMode } from 'react';

import App from './containers/App';
import controller, { ControllerProvider } from '../controller';

async function main() {
	await controller.initialize();
	ReactDOM.render(
		<StrictMode>
			<ControllerProvider>
				<App />
			</ControllerProvider>
		</StrictMode>,
		document.getElementById('root'),
	);
}

main();
