open SharedTypes;

let getInitialSize = () : size => {
  let width = Utils.viewportWidth;
  width > 992 ? (50, 70) : width > 576 ? (30, 50) : (15, 25);
};

/* Initialize random module */
Random.self_init();

let alivePercentile = 8;

let biggerThanAlivePercentile = num => num > alivePercentile;

let randomStatus = () : status => {
  let isAlive = biggerThanAlivePercentile(Random.int(11));
  isAlive ? Alive : Dead;
};

let randomCell = _el : cell => {status: randomStatus()};

let deadCell = _el : cell => {status: Dead};

let generateCells = (size: size, fn: _ => cell) : cells => {
  let (rows, cols) = size;
  Array.(make(cols, None) |> make(rows) |> map(map(fn)));
};

let generateEmptyCells = (size: size) => generateCells(size, deadCell);

let generateRandomCells = (size: size) => generateCells(size, randomCell);

let mapCells = (fn: (position, cell, cells) => cell, cells) : cells =>
  Array.(
    mapi(
      (y, row) => row |> mapi((x, cell') => fn((x, y), cell', cells)),
      cells,
    )
  );

let cycleCell = cell : cell =>
  switch (cell.status) {
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
  cells[y'][x'];
};

let getNeighborCells = ((x, y): position, cells) : list(cell) =>
  [
    (x - 1, y - 1),
    (x - 1, y),
    (x - 1, y + 1),
    (x, y - 1),
    (x, y + 1),
    (x + 1, y - 1),
    (x + 1, y),
    (x + 1, y + 1),
  ]
  |> List.map(findCell(cells));

let getAliveNeighbors = (cells, position) : int => {
  let neighborCells = getNeighborCells(position, cells);
  neighborCells |> List.filter(({status}) => status == Alive) |> List.length;
};

let checkCell = (position, cell, cells) : cell => {
  let neighbors = getAliveNeighbors(cells, position);
  switch (cell.status) {
  | Alive when neighbors > 3 || neighbors < 2 => {status: Dead}
  | Dead when neighbors == 3 => {status: Alive}
  | _ => cell
  };
};

let evolution = cells : cells => mapCells(checkCell, cells);
