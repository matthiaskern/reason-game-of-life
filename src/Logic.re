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

let randomCell = _el : cell => {status: randomStatus()};

let generateCells = (size: size) : cells => {
  let (rows, cols) = size;
  Array.(make(cols, None) |> make(rows) |> map(map(randomCell)));
};

let mapCells = (fn: (position, cell, cells) => cell, cells) : cells =>
  Array.(
    mapi(
      (y, row) => row |> mapi((x, cell') => fn((y, x), cell', cells)),
      cells
    )
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

let correctIndex = (length: int, i: int) : int =>
  i === (-1) ? length - 1 : i === length ? 0 : i;

let findCell = (cells, (x, y): position) : cell => {
  let length = Array.length(cells);
  let x' = correctIndex(length, x);
  let y' = correctIndex(length, y);
  Array.(get(get(cells, x'), y'));
};

let getArray = (n, a) => a[n];

let getNeighborCells = ((y, x): position, cells) : list(cell) =>
  [
    (y - 1, x - 1),
    (y - 1, x),
    (y - 1, x + 1),
    (y, x - 1),
    (y, x + 1),
    (y + 1, x - 1),
    (y + 1, x),
    (y + 1, x + 1)
  ]
  |> List.map(findCell(cells));

let getAliveNeighbors = (cells, position) : int =>
  getNeighborCells(position, cells)
  |> List.filter(({status}) => status == Alive)
  |> List.length;

let checkAliveCell = (neighbors: int) : cell => {
  if (neighbors > 3 || neighbors < 1) {
    {status: Dead};
  } else {
    {status: Alive};
  };
};

let checkDeadCell = (neighbors: int) : cell => {
  switch neighbors {
  | 3 => {status: Alive}
  | _ => {status: Dead}
  };
};

let checkCell = (cells, position) : cell => {
  let cell = findCell(cells, position);
  let neighbors = getAliveNeighbors(cells, position);
  switch cell.status {
  | Alive => checkAliveCell(neighbors)
  | Dead => checkDeadCell(neighbors)
  };
};
