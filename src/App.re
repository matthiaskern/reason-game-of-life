open SharedTypes;

type state = {
  size,
  generation: int,
  cells
};

type action =
  | Reset;

let deadCell = {status: Dead};

let initialState = {size: (50, 70), generation: 0, cells: [|[||]|]};

let component = ReasonReact.reducerComponent("App");

let generateCells = (size: size) : cells => {
  let (cols, rows) = size;
  Array.make(cols, Array.make(rows, deadCell));
};

let make = _children => {
  ...component,
  initialState: () => initialState,
  reducer: (action, state) =>
    switch action {
    | Reset => ReasonReact.Update({...state, cells: generateCells(state.size)})
    },
  render: ({state}) => <main> <Controls /> <Board cells=state.cells /> </main>
};