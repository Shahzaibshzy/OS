// components/MemoryLogViewer.jsx

import React from "react";
import { parseMemoryLogs } from "../utils/parseMemoryLogs";

const typeColors = {
  load: "bg-blue-100",
  replace: "bg-yellow-100",
  hit: "bg-green-100",
  utilization: "bg-purple-100",
  info: "bg-gray-100"
};

const MemoryLogViewer = ({ logs }) => {
  const parsedLogs = parseMemoryLogs(logs);

  return (
    <div className="space-y-3">
      {parsedLogs.map((log, index) => (
        <div key={index} className={`p-4 rounded-lg shadow ${typeColors[log.type]}`}>
          <p className="font-semibold">{log.action}</p>
          <p className="text-sm text-gray-700">{log.explanation}</p>
          <p className="text-xs text-gray-500 mt-1">Raw: {log.raw}</p>
        </div>
      ))}
    </div>
  );
};

export default MemoryLogViewer;
