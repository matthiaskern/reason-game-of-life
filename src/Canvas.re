let component = ReasonReact.statelessComponent("Canvas");

let cell = 1;

let row = Array.make(50, cell);

let cells = Array.map(_col => Array.make(70, cell), row);

let make = _children => {
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
                    <span className="cell" key=(string_of_int(i)) />,
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
