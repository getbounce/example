import ReactSlider from 'react-slider';

import bridge from '../bridge';

function Gain(): JSX.Element {
  console.log('render', window.innerWidth, window.innerHeight);
  return (
    <ReactSlider
      invert
      pearling
      orientation='vertical'
      className='vertical-slider'
      thumbClassName='example-thumb'
      trackClassName='example-track'
      renderThumb={(props, state) => <div {...props}>{state.valueNow}</div>}
      onChange={(value) => {
        bridge.editParameter('gain', value / 100);
      }}
    />
  );
}

export default Gain;
