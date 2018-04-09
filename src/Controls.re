let component = ReasonReact.statelessComponent("Controls");

let make = (~onReset, _children) => {
  ...component,
  render: _self => <aside> <button onClick=((_) => onReset())> (Utils.strE("Reset")) </button> </aside>
};
