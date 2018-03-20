let component = ReasonReact.statelessComponent("Controls");

let make = _children => {
  ...component,
  render: _self => <aside> <button> (Utils.strE("Start")) </button> </aside>
};