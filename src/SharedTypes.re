type status =
  | Alive
  | Dying
  | Dead;

type cell = {status};

type row = array(cell);

type cells = array(row);

type size = (int, int);
