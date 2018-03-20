type state = {size: (int, int)};

let initialState = {size: (50, 70)};

let component = ReasonReact.statelessComponent("App");

let make = _children => {
  ...component,
  render: _self => <main> <Controls /> <Board size=initialState.size /> </main>
};