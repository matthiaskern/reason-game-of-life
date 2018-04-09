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

let getAliveNeighbors = (cell: cell) : int => 3; /* TODO */

let checkAliveCell = cell : cell => {
  let neighbors = getAliveNeighbors(cell);
  if (neighbors > 3 || neighbors < 1) {
    {status: Dead};
  } else {
    cell;
  };
};

let checkDeadCell = cell : cell => {
  let neighbors = getAliveNeighbors(cell);
  switch neighbors {
  | 3 => {status: Alive}
  | _ => cell
  };
};

let checkCell = cell : cell =>
  switch cell.status {
  | Alive => checkAliveCell(cell)
  | Dead => checkDeadCell(cell)
  };

let randomCell = _el : cell => {status: randomStatus()};

let generateCells = (size: size) : cells => {
  let (rows, cols) = size;
  Array.(make(cols, None)
  |> make(rows)
  |> map(map(randomCell)));
};

