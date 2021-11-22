import Controller from 'foobartestxyz';

import parameters from '../constants/parameters.json';
import { ProcessorState } from './ProcessorState';
import { State } from './State';

export type Parameter = keyof typeof parameters;

const controller = new Controller<Parameter, State, ProcessorState>({
  parameters,
});

export default controller;
