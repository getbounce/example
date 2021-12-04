import { Controller } from 'foobartestxyz';
import { createHooks } from 'react-foobartestxyz';

import Parameter from '../schemas/Parameter';
import createParameters from '../config/parameters';
import { ProcessorState } from '../processor/ProcessorState';
import { State } from './State';

const controller = new Controller<Parameter, State, ProcessorState>({
	parameters: createParameters(),
});

const { ControllerProvider, useControllerState, useProcessorState, useControllerParameters } =
	createHooks(controller);

export default controller;
export { ControllerProvider, useControllerState, useProcessorState, useControllerParameters };
