import React from 'react';
import ReactDOM from 'react-dom/client';
import './App.css';

const inputBoardOriginal =
  [['', '', '', '', '', '', '', '', ''],
  ['', '', '', '', '', '', '', '', ''],
  ['', '', '', '', '', '', '', '', ''],
  ['', '', '', '', '', '', '', '', ''],
  ['', '', '', '', '', '', '', '', ''],
  ['', '', '', '', '', '', '', '', ''],
  ['', '', '', '', '', '', '', '', ''],
  ['', '', '', '', '', '', '', '', ''],
  ['', '', '', '', '', '', '', '', '']]

function Cell(props) {
  return (
    <input type="text" className="square" id={`cell${props.x}${props.y}`} name={`cell${props.x}${props.y}`} defaultValue={props.value} readOnly={props.readOnly} style={props.fixedCell ? { backgroundColor: 'grey' } : { backgroundColor: null }} />
  );
}

class Board extends React.Component {
  onSubmit(event) {
    // obtain input
    event.preventDefault();
    for (let i = 0; i < 9; i++) {
      for (let j = 0; j < 9; j++) {
        let name = `cell${i}${j}`
        inputBoardOriginal[i][j] = event.target.elements[name]?.value
      }
    }
    // submit a clone
    this.props.onSubmit(JSON.parse(JSON.stringify(inputBoardOriginal)));
  }

  renderCell(x, y, value, readOnly) {
    return (
      <Cell
        x={x}
        y={y}
        value={value}
        readOnly={readOnly}
        fixedCell={inputBoardOriginal[x][y] === '' ? false : true}
      />
    );
  }

  render() {
    return (
      <div>
        {this.props?.solutionNum > 0 && <p>Solution: {this.props.solutionCount}</p>}
        <form onSubmit={(event) => this.onSubmit(event)}>
          {[0, 1, 2, 3, 4, 5, 6, 7, 8].map((i, iindex) => {

            return (
              <div className='board-row' key={iindex}>
                {[0, 1, 2, 3, 4, 5, 6, 7, 8].map((j, jindex) => {
                  return (
                    <div key={jindex}>
                      {this.renderCell(i, j, this.props.boardContent[i][j], this.props.readOnly)}
                    </div>
                  );
                })}
              </div>
            )

          })}
          <br />
          <button type="submit" hidden={this.props.readOnly}>Solve</button>
          <br />
        </form>
        <br />
      </div>
    );
  }
}

class Sudoku extends React.Component {
  constructor(props) {
    super(props);
    this.emptyBoard =
      [['', '', '', '', '', '', '', '', ''],
      ['', '', '', '', '', '', '', '', ''],
      ['', '', '', '', '', '', '', '', ''],
      ['', '', '', '', '', '', '', '', ''],
      ['', '', '', '', '', '', '', '', ''],
      ['', '', '', '', '', '', '', '', ''],
      ['', '', '', '', '', '', '', '', ''],
      ['', '', '', '', '', '', '', '', ''],
      ['', '', '', '', '', '', '', '', '']]

    this.state = {
      board: JSON.parse(JSON.stringify(this.emptyBoard)),
      solutionCount: 0,
      invalidBoard: false
    }
  }

  handleSubmit(inputBoard) {

    // validate input board; do not continue if board is invalid
    if (!checkBoardConsistency(inputBoard)) {
      clearSolutions();
      this.setState({
        board: inputBoard,
        invalidBoard: true
      })
      return;
    }

    clearSolutions();

    // solve sudoku
    solve(inputBoard, this.state.solutionCount);

    if (this.state.invalidBoard)
      this.setState({
        invalidBoard: false
      })

  }

  resetBoard() {
    clearSolutions();
    this.setState({
      invalidBoard: false
    })
    // below is not working
    // let emptyBoard = JSON.parse(JSON.stringify(this.emptyBoard))
    // this.setState({
    //   board: emptyBoard
    // })
    const cells = document.getElementsByClassName("square");
    for (let i = 0; i < cells.length; i++) {
      cells[i].value = ''
    }
  }

  render() {
    return (
      <div className='sudoku'>
        <button className="reset-board" onClick={() => this.resetBoard()}>
          Reset Board
        </button>
        <br /><br />
        <div className='input-game-board'>
          <Board
            boardContent={this.state.board}
            readOnly={false}
            onSubmit={(event) => this.handleSubmit(event)}
          />
        </div>
        <div className='error-invalid-board'>
          {this.state.invalidBoard && <p>Invalid input!</p>}
        </div>
      </div>
    );
  }
}

function solve(inputBoard, solutionCount) {
  displaySolution(inputBoard, solutionCount);
}

function displaySolution(board, solutionCount) {
  const solutionsDiv = document.getElementById('solutions')
  const solution = document.createElement("div")
  const solutionId = 'solution' + solutionCount
  solution.id = solutionId
  solutionsDiv.appendChild(solution)

  const root = ReactDOM.createRoot(document.getElementById(solutionId))
  root.render(
    <React.StrictMode>
      <Board
        boardContent={board}
        readOnly={true}
        solutionNum={solutionCount}
      />
    </React.StrictMode>
  )
}

function checkBoardConsistency(board) {
  for (let i = 0; i < 9; i++) {
    for (let j = 0; j < 9; j++) {
      if (!['', '1', '2', '3', '4', '5', '6', '7', '8', '9'].includes(board[i][j])) {
        return false;
      }
    }
  }
  return true;
}

function clearSolutions() {
  // clear previous solution from UI
  const solutionsDiv = document.getElementById('solutions')
  solutionsDiv.innerHTML = ''
}

export default Sudoku;
