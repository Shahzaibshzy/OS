const express = require("express");
const fs = require("fs");
const path = require("path");
const router = express.Router();

const { extractSection } = require("./utils");

const logPath = path.join(__dirname, "..", "OS-CCP", "log.txt");

// Return the entire log
router.get("/", (req, res) => {
  fs.readFile(logPath, "utf8", (err, data) => {
    if (err) {
      console.error("Error reading log file:", err);
      return res.status(500).send("Error reading log file.");
    }

    res.type("text/plain").send(data.trim());
  });
});

function readLogAndSendSection(res, startMarker, endMarker = null) {
  fs.readFile(logPath, "utf8", (err, data) => {
    if (err) {
      console.error("Error reading log file:", err);
      return res.status(500).send("Error reading log file.");
    }

    const section = extractSection(data, startMarker, endMarker);
    res.type("text/plain").send(section.trim());
  });
}

router.get("/mem", (req, res) => {
  readLogAndSendSection(res, "[MEMORY]", "--- FILE SYSTEM TESTS ---");
});

router.get("/fs", (req, res) => {
  readLogAndSendSection(res, "--- FILE SYSTEM TESTS ---", "--- DISK SCHEDULER TESTS ---");
});

router.get("/ds", (req, res) => {
  readLogAndSendSection(res, "--- DISK SCHEDULER TESTS ---", "--- SECURITY TESTS ---");
});

router.get("/scr", (req, res) => {
  readLogAndSendSection(res, "--- SECURITY TESTS ---");
});

module.exports = router;
