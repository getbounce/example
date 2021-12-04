import ReactSlider from 'react-slider';

import controller from '../../controller';

function Gain(): JSX.Element {
	return (
		<ReactSlider
			invert
			pearling
			orientation='vertical'
			className='vertical-slider'
			thumbClassName='example-thumb'
			trackClassName='example-track'
			renderThumb={(props, state) => <div {...props}>{state.valueNow}</div>}
			onChange={(value) => controller.updateParameter('gain', value / 100)}
		/>
	);
}

export default Gain;
