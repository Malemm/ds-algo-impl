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

const hardCodedSudoku =
  [['5', '3', '', '', '7', '', '', '', ''],
  ['6', '', '', '1', '9', '5', '', '', ''],
  ['', '9', '8', '', '', '', '', '6', ''],
  ['8', '', '', '', '6', '', '', '', '3'],
  ['4', '', '', '8', '', '3', '', '', '1'],
  ['7', '', '', '', '2', '', '', '', '6'],
  ['', '6', '', '', '', '', '2', '8', ''],
  ['', '', '', '4', '1', '9', '', '', '5'],
  ['', '', '', '', '8', '', '', '7', '9']]

/**
 * Cell React component
 * @param {*} props 
 * @returns 
 */
function Cell(props) {
  return (
    <input type="text" className="cell" id={`cell${props.x}${props.y}`} name={`cell${props.x}${props.y}`} defaultValue={props.value} readOnly={props.readOnly} style={props.fixedCell ? { backgroundColor: 'grey' } : { backgroundColor: null }} />
  );
}

/**
 * Board React component
 */
class Board extends React.Component {
  /**
   * Input form submission handler
   * @param {*} event 
   */
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

  /**
   * Render each cell of the sudoku board
   * @param {*} x 
   * @param {*} y 
   * @param {*} value 
   * @param {*} readOnly 
   * @returns 
   */
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
        {this.props?.solutionNum > 0 && <p>Solution: {this.props.solutionNum}</p>}
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

/**
 * Root component
 */
class Sudoku extends React.Component {
  constructor(props) {
    super(props);

    this.inputBoard =
      [['', '', '', '', '', '', '', '', ''],
      ['', '', '', '', '', '', '', '', ''],
      ['', '', '', '', '', '', '', '', ''],
      ['', '', '', '', '', '', '', '', ''],
      ['', '', '', '', '', '', '', '', ''],
      ['', '', '', '', '', '', '', '', ''],
      ['', '', '', '', '', '', '', '', ''],
      ['', '', '', '', '', '', '', '', ''],
      ['', '', '', '', '', '', '', '', '']]

    // for testing
    this.inputBoard = hardCodedSudoku;

    this.solutions = []

    this.state = {
      board: JSON.parse(JSON.stringify(this.inputBoard)),
      solutionCount: 0,
      invalidBoard: false
    }
  }

  /**
   * To check consistency on input sudoku
   * @returns 
   */
  checkBoardConsistency() {
    let count = 0;
    for (let i = 0; i < 9; i++) {
      for (let j = 0; j < 9; j++) {
        if (!['', '1', '2', '3', '4', '5', '6', '7', '8', '9'].includes(this.inputBoard[i][j])) {
          return false;
        }
        if (this.inputBoard[i][j] !== '') {
          count++
        }
      }
    }

    if (count < 20) {
      // system might crash if tried to generate solution for such cases
      return false;
    }
    return true;
  }

  /**
   * Handle sudoku submission
   * @param {*} inputBoard 
   * @returns 
   */
  handleSubmit(inputBoard) {
    this.inputBoard = inputBoard

    // validate input board; do not continue if board is invalid
    if (!this.checkBoardConsistency()) {
      clearSolutions();
      this.setState({
        invalidBoard: true
      })
      return;
    }

    clearSolutions();

    // solve sudoku
    this.solve();

    // display solutions
    for (let i = 0; i < this.solutions.length; i++) {
      displaySolution(this.solutions[i], i + 1)
    }

    this.solutions = []

    if (this.state.invalidBoard)
      this.setState({
        invalidBoard: false
      })

  }

  /**
   * solve - recursive backtracking algorithm
   * @returns 
   */
  solve() {
    for (let x = 0; x < 9; x++) {
      for (let y = 0; y < 9; y++) {
        if (this.inputBoard[x][y] === '') {
          for (let value = 1; value <= 9; value++) {
            if (this.canWePut(x, y, '' + value)) {
              this.inputBoard[x][y] = '' + value
              this.solve()
              this.inputBoard[x][y] = ''
            }
          }
          return;
        }
      }
    }

    // save the solution
    this.solutions.push(JSON.parse(JSON.stringify(this.inputBoard)))
  }

  /**
   * canWePut - to check if a value can be put in a given position
   * @param {*} x 
   * @param {*} y 
   * @param {*} value 
   * @returns 
   */
  canWePut(x, y, value) {
    // check rows
    for (let i = 0; i < 9; i++) {
      if (this.inputBoard[x][i] === value) {
        return false
      }
    }

    // check columns
    for (let j = 0; j < 9; j++) {
      if (this.inputBoard[j][y] === value) {
        return false
      }
    }

    // check the sub-square
    let x_start = Math.floor(x / 3) * 3
    let y_start = Math.floor(y / 3) * 3
    for (let i = x_start; i < x_start + 3; i++) {
      for (let j = y_start; j < y_start + 3; j++) {
        if (this.inputBoard[i][j] === value) {
          return false
        }
      }
    }

    return true
  }

  /**
   * Reset the board.
   */
  resetBoard() {
    clearSolutions();
    this.setState({
      invalidBoard: false
    })
    
    // below is not working
    // let emptyBoard = JSON.parse(JSON.stringify(hardCodedSudoku))
    // this.setState({
    //   board: emptyBoard
    // })

    // this is a work around
    // for (let i = 0; i < 9; i++) {
    //   for (let j = 0; j < 9; j++) {
    //     const cell = document.getElementById(`cell${i}${j}`);
    //     cell.value = hardCodedSudoku[i][j]
    //   }
    // }

    const cells = document.getElementsByClassName("cell");
    for (let i = 0; i < cells.length; i++) {
      cells[i].value = ''
    }

    // reset inputBoardOriginal
    for (let i = 0; i < 9; i++) {
      for (let j = 0; j < 9; j++) {
        inputBoardOriginal[i][j] = ''
      }
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

/**
 * Creates new DIVs and appends solution boards
 * @param {*} board 
 * @param {*} solutionCount 
 */
function displaySolution(board, solutionCount) {
  const solutionsDiv = document.getElementById('solutions')
  const solution = document.createElement("div")
  const solutionId = 'solution' + solutionCount
  solution.id = solutionId
  solutionsDiv.appendChild(solution)

  const solutionComp = ReactDOM.createRoot(document.getElementById(solutionId))
  solutionComp.render(
    <React.StrictMode>
      <Board
        boardContent={board}
        readOnly={true}
        solutionNum={solutionCount}
      />
    </React.StrictMode>
  )
}

/**
 * Remove the solution boards/DIVs
 */
function clearSolutions() {
  // clear previous solution from UI
  const solutionsDiv = document.getElementById('solutions')
  solutionsDiv.innerHTML = ''
}

export default Sudoku;
