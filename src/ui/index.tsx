import './index.css';

import React from 'react';
import ReactDOM from 'react-dom';

import App from './containers/App';
import controller, { ControllerProvider } from '../controller';

async function main() {
  await controller.initialize();
  ReactDOM.render(
    <React.StrictMode>
      <ControllerProvider>
        <App />
      </ControllerProvider>
    </React.StrictMode>,
    document.getElementById('root'),
  );
}

main();
