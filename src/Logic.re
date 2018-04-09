open SharedTypes;

/* Initialize random module */
Random.self_init();

let randomStatus = () : status => {
  let random = Random.int(2);
  switch random {
  | 0 => Dead
  | 1 => Alive
  | _ => Dead
  };
};

let getCell = (position, cells) : cell => {status: Alive};

let getAliveNeighbors = (position, cells) : int => 3; /* TODO */

let checkAliveCell = (position, cells) : cell => {
  let neighbors = getAliveNeighbors(position, cells);
  if (neighbors > 3 || neighbors < 1) {
    {status: Dead};
  } else {
    {status: Alive};
  };
};

let checkDeadCell = (position, cells) : cell => {
  let neighbors = getAliveNeighbors(position, cells);
  switch neighbors {
  | 3 => {status: Alive}
  | _ => {status: Dead}
  };
};

let checkCell = (position, cells) : cell => {
  let cell = getCell(position, cells);
  switch cell.status {
  | Alive => checkAliveCell(position, cells)
  | Dead => checkDeadCell(position, cells)
  };
};

let randomCell = _el : cell => {status: randomStatus()};

let generateCells = (size: size) : cells => {
  let (rows, cols) = size;
  Array.(make(cols, None) |> make(rows) |> map(map(randomCell)));
};

let mapCells = (fn: (position, cell, cells) => cell, cells) : cells =>
  Array.(
    mapi((y, row) => row |> mapi((x, cell') => fn((y, x), cell', cells)), cells)
  );

let cycleCell = cell : cell =>
  switch cell.status {
  | Alive => {status: Dead}
  | Dead => {status: Alive}
  };

let toggleCell = ((x, y): position) =>
  mapCells(((x', y'), cell, _) =>
    x === x' && y === y' ? cycleCell(cell) : cell
  );
