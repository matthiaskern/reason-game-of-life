open SharedTypes;

let component = ReasonReact.statelessComponent("Board");

let makeCell = (onToggle, x: int, cell) =>
  <Cell key=(string_of_int(x)) cell onToggle=((_) => onToggle(x)) />;

let make = (~cells: cells, ~onToggle, _children) => {
  ...component,
  render: _self =>
    <section>
      (
        Array.mapi(
          (y, row) =>
            <div className="row" key=(string_of_int(y))>
              (
                row |> Array.mapi(makeCell(onToggle(y))) |> ReasonReact.array
              )
            </div>,
          cells,
        )
        |> ReasonReact.array
      )
    </section>,
};
