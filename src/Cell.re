open SharedTypes;

type retainedProps = {cell};

let component = ReasonReact.statelessComponentWithRetainedProps("Cell");

let classNameOfStatus = status : string =>
  switch (status) {
  | Alive => "alive"
  | Dead => "dead"
  };

let make = (~onToggle, ~cell: cell, _children) => {
  ...component,
  retainedProps: { cell: cell },
  shouldUpdate: ({oldSelf, newSelf}) =>
    oldSelf.retainedProps.cell.status !== newSelf.retainedProps.cell.status,
  render: _self =>
    <div
      className=("cell " ++ classNameOfStatus(cell.status))
      onClick=((_) => onToggle())
    />,
};
