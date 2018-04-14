open Utils;

let component = ReasonReact.statelessComponent("Controls");

let make = (~onReset, ~onStart, ~onStop, ~generation, _children) => {
  ...component,
  render: _self =>
    <aside>
      <button onClick=((_) => onReset())> (strE("Reset")) </button>
      <button onClick=((_) => onStart())> (strE("Start")) </button>
      <button onClick=((_) => onStop())> (strE("Stop")) </button>
      <span style=(ReactDOMRe.Style.make(~float="right", ()))>
        (strE("generation: " ++ string_of_int(generation)))
      </span>
    </aside>
};
