open Utils;

let component = ReasonReact.statelessComponent("Controls");

let make = (~onRandom, ~onTogglePlay, ~isPlaying, ~onClear, ~generation, _children) => {
  ...component,
  render: _self =>
    <aside>
      <button onClick=((_) => onRandom())> (strE("Random")) </button>
      <button onClick=((_) => onTogglePlay())> (strE(isPlaying ? "Stop" : "Start")) </button>
      <button onClick=((_) => onClear())> (strE("Clear")) </button>
      <span style=(ReactDOMRe.Style.make(~float="right", ()))>
        (strE("generation: " ++ string_of_int(generation)))
      </span>
    </aside>
};
