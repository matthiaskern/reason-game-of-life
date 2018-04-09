type status =
  | Alive
  | Dead;

type cell = {status};

type row = array(cell);

type cells = array(row);

type size = (int, int);
type position = (int, int);
