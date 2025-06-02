const express = require("express");
const path = require("path");
const { exec } = require("child_process");
const cors = require("cors");

const logRoutes = require("./logRoutes");

const app = express();
const PORT = 3000;

app.use(cors());

const simulatorDir = path.join(__dirname, "..", "OS-CCP");
const simulatorPath = path.join(simulatorDir, "simulator.exe");

// Route to run the simulator in a visible CMD window
app.get("/run", (req, res) => {
  // Windows command to open a new CMD window and run simulator.exe, keeping window open
  const command = `start cmd.exe /k "${simulatorPath}"`;

  exec(command, { cwd: simulatorDir }, (error, stdout, stderr) => {
    if (error) {
      console.error("Error launching simulator:", error);
      return res.status(500).send("Failed to open simulator window.");
    }
    console.log("Simulator CMD window launched.");
    res.send("Simulator window opened.");
  });
});

// Use the /logs routes
app.use("/logs", logRoutes);

app.listen(PORT, () => {
  console.log(`Server running at http://localhost:${PORT}`);
});
