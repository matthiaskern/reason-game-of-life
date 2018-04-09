open SharedTypes;

type state = {
  size,
  generation: int,
  cells
};

type action =
  | Start
  | Stop
  | Toggle(position)
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
    | Start => ReasonReact.NoUpdate
    | Stop => ReasonReact.NoUpdate
    | Toggle(position) =>
      Js.log3(
        Logic.getAliveNeighbors(position, state.cells),
        position,
        Cell.classNameOfStatus(Logic.findCell(position, state.cells).status)
      );
      ReasonReact.Update({
        ...state,
        cells: Logic.toggleCell(position, state.cells)
      });
    | Reset =>
      ReasonReact.Update({...state, cells: Logic.generateCells(state.size)})
    },
  render: self =>
    <main>
      <Controls
        onReset=(() => self.send(Reset))
        onStart=(() => self.send(Start))
        onStop=(() => self.send(Stop))
      />
      <Board
        cells=self.state.cells
        onToggle=((x, y) => self.send(Toggle((x, y))))
      />
    </main>
};
