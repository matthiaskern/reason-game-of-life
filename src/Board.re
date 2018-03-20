open SharedTypes;

let component = ReasonReact.statelessComponent("Board");

let make = (~cells: cells, _children) => {
  ...component,
  render: _self =>
    <section>
      (
        Array.mapi(
          (i, row) =>
            <div className="row" key=(string_of_int(i))>
              (
                Array.mapi(
                  (i, _cell) =>
                    <div className="cell" key=(string_of_int(i)) />,
                  row
                )
                |> ReasonReact.arrayToElement
              )
            </div>,
          cells
        )
        |> ReasonReact.arrayToElement
      )
    </section>
};