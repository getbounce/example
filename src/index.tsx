import './index.css';

import React from 'react';
import ReactDOM from 'react-dom';

import App from './containers/App';
import bridge from './bridge';

async function main() {
  await bridge.open();
  ReactDOM.render(
    <React.StrictMode>
      <App />
    </React.StrictMode>,
    document.getElementById('root'),
  );
}

main();
