open SharedTypes;

type state = {
  size,
  generation: int,
  cells
};

type action =
  | Reset;

let randomStatus = () : status => {
  let random = int_of_float(Js.Math.round(Js.Math.random() ** 1.0));
  switch random {
  | 0 => Dead
  | 1 => Alive
  };
};

let randomCell = _el : cell => {status: randomStatus()};

let generateCells = (size: size) : cells => {
  let (rows, cols) = size;
  Array.make(cols, None)
  |> Array.make(rows)
  |> Array.map(Array.map(randomCell));
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