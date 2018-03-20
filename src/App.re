open SharedTypes;

type state = {
  size,
  generation: int,
  cells
};

type action =
  | Reset;

let deadCell = {status: Dead};

let generateCells = (size: size) : cells => {
  let (cols, rows) = size;
  Array.make(cols, Array.make(rows, deadCell));
};

let initialSize = (50, 70);

let initialState = {
  size: initialSize,
  generation: 0,
  cells: generateCells(initialSize)
};

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState: () => initialState,
  reducer: (action, state) =>
    switch action {
    | Reset => ReasonReact.Update({...state, cells: generateCells(state.size)})
    },
  render: ({state}) => <main> <Controls /> <Board cells=state.cells /> </main>
};