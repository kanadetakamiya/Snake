const canvas = document.getElementById("main");
const context = canvas.getContext("2d");

function drawBackground() {
  context.fillStyle = "black";
  context.fillRect(0, 0, 600, 400);
}

const CELL_SIZE = 10;
const snake = [
  [5, 3],
  [4, 3],
  [3, 3],
];
let direction = 0;

const food = [10, 10];

function drawFood() {
  context.fillStyle = "red";
  context.fillRect(
    food[0] * CELL_SIZE + 2,
    food[1] * CELL_SIZE + 2,
    CELL_SIZE - 4,
    CELL_SIZE - 4
  );
}

function drawSnake() {
  context.fillStyle = "white";
  for (let cell of snake) {
    context.fillRect(
      cell[0] * CELL_SIZE + 1,
      cell[1] * CELL_SIZE + 1,
      CELL_SIZE - 2,
      CELL_SIZE - 2
    );
  }
}

function displayScore() {
  context.font = "20px Arial";
  context.fillStyle = "grey";
  context.fillText("Score: " + (snake.length - 3), 5, 20);
}

let intent = direction;

document.addEventListener("keydown", (e) => {
  if (e.key === "ArrowRight" && direction !== 2) {
    intent = 0;
  } else if (e.key === "ArrowLeft" && direction !== 0) {
    intent = 2;
  } else if (e.key === "ArrowUp" && direction !== 1) {
    intent = 3;
  } else if (e.key === "ArrowDown" && direction !== 3) {
    intent = 1;
  }
});

function wall() {
  if (snake[0][0] < 0) {
    snake[0][0] = 59;
  } else if (snake[0][0] > 59) {
    snake[0][0] = 0;
  }
  if (snake[0][1] < 0) {
    snake[0][1] = 39;
  } else if (snake[0][1] > 39) {
    snake[0][1] = 0;
  }
}

function randfood() {
  do {
    food[0] = Math.floor(Math.random() * 60);
    food[1] = Math.floor(Math.random() * 40);
    i = 0;
    for (; i < snake.length; i++) {
      if (snake[i][0] === food[0] && snake[i][1] === food[1]) {
        break;
      }
    }
    if (i === snake.length) {
      break;
    }
  } while (true);
}

function survive() {
  for (let i = 1; i < snake.length; i++) {
    if (snake[i][0] === snake[0][0] && snake[i][1] === snake[0][1]) {
      return false;
    }
  }
  return true;
}
const tmp = [0, 0];

function updateGameState() {
  if (direction !== intent) {
    direction = intent;
  }
  tmp[0] = snake[snake.length - 1][0];
  tmp[1] = snake[snake.length - 1][1];
  for (let i = snake.length - 1; i >= 1; i--) {
    snake[i][0] = snake[i - 1][0];
    snake[i][1] = snake[i - 1][1];
  }
  switch (direction) {
    case 0:
      snake[0][0] += 1;
      break;
    case 1:
      snake[0][1] += 1;
      break;
    case 2:
      snake[0][0] -= 1;
      break;
    default:
      snake[0][1] -= 1;
  }
  wall();
  if (snake[0][0] === food[0] && snake[0][1] === food[1]) {
    snake.push([0, 0]);
    snake[snake.length - 1][0] = tmp[0];
    snake[snake.length - 1][1] = tmp[1];
    randfood();
  }
}

const STEP = 0.1;
let accumulate = 0;
function update(delta) {
  accumulate += delta;

  while (accumulate >= STEP) {
    updateGameState(STEP);
    accumulate -= STEP;
  }
  context.clearRect(0, 0, 600, 400);
  drawBackground();
  displayScore();
  drawSnake();
  drawFood();

}

let lastUpdate = Date.now();
(function loop() {
  const delta = (Date.now() - lastUpdate) / 1000;
  lastUpdate = Date.now();

  update(delta);

  if (!survive()) {
    alert("You lose!\nScore: " + (snake.length - 3));
    return;
  }
  requestAnimationFrame(loop);
})();
