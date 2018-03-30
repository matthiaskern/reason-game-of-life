open SharedTypes;

type state = {
  size,
  generation: int,
  cells
};

type action =
  | Reset;

/* Initialize random module */
Random.self_init();

let randomStatus = () : status => {
  let random = Random.int(2);
  switch random {
  | 0 => Dead
  | 1 => Alive
  | _ => Dead
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
