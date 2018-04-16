open SharedTypes;

type state = {
  size,
  generation: int,
  cells,
  timer: ref(option(Js.Global.timeoutId)),
  isPlaying: bool
};

type action =
  | Evolution
  | Start
  | Stop
  | Clear
  | ToggleCell(position)
  | Random;

let initialSize = (50, 70);

let initialState = () => {
  size: initialSize,
  generation: 0,
  cells: Logic.generateRandomCells(initialSize),
  timer: ref(None),
  isPlaying: false
};

let component = ReasonReact.reducerComponent("App");

type self = ReasonReact.self(state, ReasonReact.noRetainedProps, action);

let clearTimerAndStop = (self: self) => {
  switch self.state.timer^ {
  | None => ()
  | Some(timeout) => Js.Global.clearTimeout(timeout)
  };
  self.send(Stop);
};

let togglePlay = (self: self, _) =>
  if (self.state.isPlaying) {
    clearTimerAndStop(self);
  } else {
    let rec play = () => {
      self.state.timer := Some(Js.Global.setTimeout(play, 500));
      self.send(Evolution);
    };
    play();
    self.send(Start);
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
    | Stop =>
      ReasonReact.Update({...state, isPlaying: false, timer: ref(None)})
    | ToggleCell(position) =>
      ReasonReact.Update({
        ...state,
        cells: Logic.toggleCell(position, state.cells)
      })
    | Clear =>
      ReasonReact.UpdateWithSideEffects(
        {
          ...state,
          cells: Logic.generateEmptyCells(initialSize),
          generation: 0
        },
        clearTimerAndStop
      )
    | Random =>
      ReasonReact.UpdateWithSideEffects(
        {
          ...state,
          cells: Logic.generateRandomCells(state.size),
          generation: 0
        },
        clearTimerAndStop
      )
    },
  render: self =>
    <main>
      <Controls
        onRandom=(() => self.send(Random))
        onTogglePlay=(togglePlay(self))
        isPlaying=self.state.isPlaying
        onClear=(() => self.send(Clear))
        generation=self.state.generation
      />
      <Board
        cells=self.state.cells
        onToggle=((y, x) => self.send(ToggleCell((x, y))))
      />
    </main>
};
