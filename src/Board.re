let component = ReasonReact.statelessComponent("Board");

let cell = 1;

let make = (~size, _children) => {
  ...component,
  render: _self => {
    let (cols, rows) = size;
    <section>
      (
        Array.mapi(
          (i, _row) =>
            <div className="row" key=(string_of_int(i))>
              (
                Array.mapi(
                  (i, _cell) =>
                    <div className="cell" key=(string_of_int(i)) />,
                  Array.make(rows, cell)
                )
                |> ReasonReact.arrayToElement
              )
            </div>,
          Array.make(cols, cell)
        )
        |> ReasonReact.arrayToElement
      )
    </section>;
  }
};