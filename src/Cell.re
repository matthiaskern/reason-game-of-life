open SharedTypes;

let component = ReasonReact.statelessComponent("Cell");

let classNameOfStatus = status : string =>
  switch (status) {
  | Alive => "alive"
  | Dead => "dead"
  };

let make = (~onToggle, ~cell: cell, _children) => {
  ...component,
  render: _self =>
    <div
      className=("cell " ++ classNameOfStatus(cell.status))
      onClick=((_) => onToggle())
    />,
};
