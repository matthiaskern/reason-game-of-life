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
          (i, row) =>
            <div className="row" key=(string_of_int(i))>
              (
                row
                |> Array.mapi(makeCell(onToggle(i)))
                |> ReasonReact.arrayToElement
              )
            </div>,
          cells
        )
        |> ReasonReact.arrayToElement
      )
    </section>
};
