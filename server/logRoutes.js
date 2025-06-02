const express = require("express");
const fs = require("fs");
const path = require("path");
const router = express.Router();

const logsDir = path.join(__dirname, "..", "OS-CCP", "logs");

// Helper function to send file content as plain text
function sendLogFile(res, filename) {
  const filePath = path.join(logsDir, filename);
  fs.readFile(filePath, "utf8", (err, data) => {
    if (err) {
      console.error(`Error reading ${filename}:`, err);
      return res.status(500).send(`Error reading file ${filename}`);
    }
    res.type("text/plain").send(data.trim());
  });
}

// Replace old sectional routes with direct file serving routes
router.get("/mem", (req, res) => {
  sendLogFile(res, "memory.log");
});

router.get("/fs", (req, res) => {
  sendLogFile(res, "filesystem.log");
});

router.get("/ds", (req, res) => {
  sendLogFile(res, "disk_io.log");
});

router.get("/scr", (req, res) => {
  sendLogFile(res, "security.log");
});

module.exports = router;
