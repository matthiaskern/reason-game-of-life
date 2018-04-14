open SharedTypes;

type state = {
  size,
  generation: int,
  cells,
  timer: ref(option(Js.Global.timeoutId)),
  isPlaying: bool
};

type action =
  | Start
  | Evolution
  | Stop
  | Toggle(position)
  | Reset;

let initialSize = (50, 70);

let initialState = () => {
  size: initialSize,
  generation: 0,
  cells: Logic.generateCells(initialSize),
  timer: ref(None),
  isPlaying: false
};

let component = ReasonReact.reducerComponent("App");

type self_props = ReasonReact.self(state, ReasonReact.noRetainedProps, action);

let togglePlay = (self: self_props, _) => {
  let rec play = () => {
    self.state.timer := Some(Js.Global.setTimeout(play, 500));
    self.send(Evolution);
  };
  if (self.state.isPlaying) {
    switch self.state.timer^ {
    | None => ()
    | Some(timeout) => Js.Global.clearTimeout(timeout)
    };
    self.send(Stop);
  } else {
    play();
    self.send(Start);
  };
};

let make = _children => {
  ...component,
  initialState: () => initialState(),
  reducer: (action, state) =>
    switch action {
    | Start => ReasonReact.Update({...state, isPlaying: true})
    | Evolution =>
      ReasonReact.Update({
        ...state,
        cells: Logic.evolution(state.cells),
        generation: state.generation + 1
      })
    | Stop => ReasonReact.Update({...state, isPlaying: false, timer: ref(None)})
    | Toggle(position) =>
      let cell = Logic.findCell(state.cells, position);
      Js.log4(
        Logic.getAliveNeighbors(state.cells, position),
        position,
        Cell.classNameOfStatus(Logic.findCell(state.cells, position).status),
        Cell.classNameOfStatus(
          Logic.checkCell(position, cell, state.cells).status
        )
      );
      ReasonReact.Update({
        ...state,
        cells: Logic.toggleCell(position, state.cells)
      });
    | Reset =>
      ReasonReact.Update({
        ...state,
        cells: Logic.generateCells(state.size),
        generation: 0
      })
    },
  render: self => {
    let togglePlay = togglePlay(self);
    <main>
      <Controls
        onReset=(() => self.send(Reset))
        onStart=togglePlay
        onStop=togglePlay
        generation=self.state.generation
      />
      <Board
        cells=self.state.cells
        onToggle=((y, x) => self.send(Toggle((x, y))))
      />
    </main>;
  }
};
