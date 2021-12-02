import './App.css';

import Gain from '../components/Gain';
import logo from './logo.svg';
import {
  useControllerParameters,
  useControllerState,
  useProcessorState,
} from '../../controller';

function App() {
  const params = useControllerParameters();
  const state = useControllerState();
  const processorState = useProcessorState();
  return (
    <>
      <div className='container'>
        <Gain />
      </div>
      <div className='App'>
        <header className='App-header'>
          <img src={logo} className='App-logo' alt='logo' />
          <p>
            Edit <code>src/App.tsx</code> and save to reload.
          </p>
          <a
            className='App-link'
            href='https://reactjs.org'
            target='_blank'
            rel='noopener noreferrer'
          >
            Learn React
          </a>
          <code>
            <pre>
              {JSON.stringify(params, null, 2)}
              {JSON.stringify(state, null, 2)}
              {JSON.stringify(processorState, null, 2)}
            </pre>
          </code>
        </header>
      </div>
    </>
  );
}

export default App;
