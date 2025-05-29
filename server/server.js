// server/index.js

const express = require('express');
const path = require('path');
const fs = require('fs');
const { execFile } = require('child_process');

const cors = require('cors');

const app = express();
const PORT = 3000;

app.use(cors())

// Path to simulator.exe (one level up from /server)
const simulatorPath = path.join(__dirname, '..', 'simulator.exe');
const logPath = path.join(__dirname, '..', 'log.txt');

// Route to run the simulator
app.get('/run', (req, res) => {
  execFile(simulatorPath, (error, stdout, stderr) => {
    if (error) {
      console.error('Execution error:', error);
      return res.status(500).send('Failed to run simulator.');
    }
    console.log('Simulator ran successfully.');
    res.send('Simulator executed.');
  });
});

// Route to read the log file
app.get('/logs', (req, res) => {
  fs.readFile(logPath, 'utf8', (err, data) => {
    if (err) {
      console.error('Failed to read log:', err);
      return res.status(500).send('Could not read log file.');
    }
    res.type('text/plain').send(data);
  });
});

app.listen(PORT, () => {
  console.log(`Server running at http://localhost:${PORT}`);
});
