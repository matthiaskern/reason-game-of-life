let component = ReasonReact.statelessComponent("Canvas");

let make = _children => {
  ...component,
  render: _self =>
  <main>
    <Controls />
    <Canvas />
  </main>
};

