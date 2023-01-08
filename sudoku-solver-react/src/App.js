import React from 'react';
import ReactDOM from 'react-dom/client';
import './App.css';

function Cell(props) {
  return (
    <input type="text" className="square" key={`cell${props.x}${props.y}`} id={`cell${props.x}${props.y}`} name={`cell${props.x}${props.y}`} defaultValue={props.value} onChange={props.value} readOnly={props.readOnly} />
  );
}

class Board extends React.Component {
  renderCell(x, y, value, readOnly) {
    return (
      <Cell
        x={x}
        y={y}
        value={value}
        readOnly={readOnly}
      />
    );
  }

  render() {
    return (
      <div>
        {/* {this.props?.solutionNum > 0 && <p>Solution: {this.props.solutionCount}</p>} */}
        <form onSubmit={this.props.onSubmit}>
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

  handleSubmit(event) {
    // get input
    event.preventDefault()

    let inputBoard = JSON.parse(JSON.stringify(this.emptyBoard))

    for (let i = 0; i < 9; i++) {
      for (let j = 0; j < 9; j++) {
        let name = `cell${i}${j}`
        inputBoard[i][j] = event.target.elements[name]?.value
      }
    }

    // if board is invalid, do not continue
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

    this.setState({
      invalidBoard: false
    })
  }

  resetBoard() {
    clearSolutions();
    // let emptyBoard = JSON.parse(JSON.stringify(this.emptyBoard))
    let emptyBoard =
      [['9', '', '', '', '', '', '', '', ''],
      ['', '', '', '', '', '', '', '', ''],
      ['', '', '', '', '', '', '', '', ''],
      ['', '', '', '', '', '', '', '', ''],
      ['', '', '', '', '', '', '', '', ''],
      ['', '', '', '', '', '', '', '', ''],
      ['', '', '', '', '', '', '', '', ''],
      ['', '', '', '', '', '', '', '', ''],
      ['', '', '', '', '', '', '', '', '']]
    this.setState({
      board: emptyBoard
    })
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
