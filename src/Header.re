open Utils;

let component = ReasonReact.statelessComponent("Header");

let make = _children => {
  ...component,
  render: _self =>
    <header>
      <h1> (strE("Reason game of life")) </h1>
      <h2>
        (strE("An implementation of "))
        <a href="https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life" target="_blank">
          (strE("Conway's Game of Life"))
        </a>
        (strE(" in "))
        <a href="https://reasonml.github.io" target="_blank"> (strE("ReasonML")) </a>
        (strE(" and "))
        <a href="https://reasonml.github.io/reason-react/" target="_blank">
          (strE("ReasonReact"))
        </a>
      </h2>
    </header>
};
