open SharedTypes;

let component = ReasonReact.statelessComponent("Board");

let classNameOfCell = ({status}) : string =>
  switch status {
  | Alive => "alive"
  | Dying => "dying"
  | Dead => "dead"
  };

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
                  (i, cell: cell) =>
                    <div
                      className=("cell " ++ classNameOfCell(cell))
                      key=(string_of_int(i))
                    />,
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