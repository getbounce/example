import { Controller } from 'foobartestxyz';
import { createHooks } from 'react-foobartestxyz';

import parameters from '../config/parameters.json';
import { ProcessorState } from '../processor/ProcessorState';
import { State } from './State';

export type Parameter = keyof typeof parameters;

const controller = new Controller<Parameter, State, ProcessorState>({
  parameters,
});

const {
  ControllerProvider,
  useControllerState,
  useProcessorState,
  useControllerParameters,
} = createHooks(controller);

export default controller;
export {
  ControllerProvider,
  useControllerState,
  useProcessorState,
  useControllerParameters,
};
