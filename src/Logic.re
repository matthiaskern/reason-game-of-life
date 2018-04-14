open SharedTypes;

/* Initialize random module */
Random.self_init();

let biggerThanNine = num => num > 9;

let randomStatus = () : status => {
  let isBiggerThanNine = biggerThanNine(Random.int(11));
  isBiggerThanNine ? Alive : Dead;
};

let randomCell = _el : cell => {status: randomStatus()};

let generateCells = (size: size) : cells => {
  let (rows, cols) = size;
  Array.(make(cols, None) |> make(rows) |> map(map(randomCell)));
};

let mapCells = (fn: (position, cell, cells) => cell, cells) : cells =>
  Array.(
    mapi(
      (y, row) => row |> mapi((x, cell') => fn((x, y), cell', cells)),
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
  let lengthX = Array.length(cells[0]);
  let lengthY = Array.length(cells);
  let x' = correctIndex(lengthX, x);
  let y' = correctIndex(lengthY, y);
  let cell = cells[y'][x'];
  cell;
};

let filterIndex = (index: int, len: int) : bool =>
  index > (-1) && index <= len;

let getNeighborCells = ((x, y): position, cells) : list(cell) =>
  [
    (x - 1, y - 1),
    (x - 1, y),
    (x - 1, y + 1),
    (x, x - 1),
    (x, x + 1),
    (x + 1, y - 1),
    (x + 1, y),
    (x + 1, y + 1)
  ]
  |> List.filter(((x', y'): position) =>
       filterIndex(x', Array.length(cells[0]))
       && filterIndex(y', Array.length(cells))
     )
  |> List.map(findCell(cells));

let getAliveNeighbors = (cells, position) : int => {
  let neighborCells = getNeighborCells(position, cells);
  neighborCells |> List.filter(({status}) => status == Alive) |> List.length;
};

let checkAliveCell = (neighbors: int) : cell =>
  if (neighbors > 3 || neighbors < 1) {
    {status: Dead};
  } else {
    {status: Alive};
  };

let checkDeadCell = (neighbors: int) : cell =>
  switch neighbors {
  | 3 => {status: Alive}
  | _ => {status: Dead}
  };

let checkCell = (position, cell, cells) : cell => {
  let neighbors = getAliveNeighbors(cells, position);
  switch cell.status {
  | Alive => checkAliveCell(neighbors)
  | Dead => checkDeadCell(neighbors)
  };
};

let evolution = cells : cells => mapCells(checkCell, cells);
