// server/index.js

const express = require("express");
const path = require("path");
const { execFile } = require("child_process");
const cors = require("cors");

const logRoutes = require("./logRoutes");

const app = express();
const PORT = 3000;

app.use(cors());

const simulatorPath = path.join(__dirname, "..", "OS-CCP", "simulator.exe");

// Route to run the simulator
app.get("/run", (req, res) => {
  execFile(simulatorPath, { cwd: path.join(__dirname, "..", "OS-CCP") }, (error, stdout, stderr) => {
    if (error) {
      console.error("Execution error:", error);
      return res.status(500).send("Failed to run simulator.");
    }
    console.log("Simulator ran successfully.");
    res.send("Simulator executed.");
  });
});

// Use the /logs routes
app.use("/logs", logRoutes);

app.listen(PORT, () => {
  console.log(`Server running at http://localhost:${PORT}`);
});
