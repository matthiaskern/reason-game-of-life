open SharedTypes;

type state = {
  size,
  generation: int,
  cells
};

type action =
  | Toggle(int, int)
  | Reset;

let initialSize = (50, 70);

let initialState = {
  size: initialSize,
  generation: 0,
  cells: Logic.generateCells(initialSize)
};

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState: () => initialState,
  reducer: (action, state) =>
    switch action {
    | Toggle(x, y) =>
      Js.log((x,y));
      ReasonReact.NoUpdate;
    | Reset => ReasonReact.Update({...state, cells: Logic.generateCells(state.size)})
    },
  render: self =>
    <main>
      <Controls onReset=(() => self.send(Reset))/>
      <Board
        cells=self.state.cells
        onToggle=((y,x) => self.send(Toggle(x, y)))
      />
    </main>
};
