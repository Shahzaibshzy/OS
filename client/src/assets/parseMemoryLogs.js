// utils/parseMemoryLogs.js

export function parseMemoryLogs(logLines) {
  return logLines.map(line => {
    const entry = { raw: line, type: "info", action: "", explanation: "" };

    if (line.includes("Loaded page")) {
      const [, page, frame] = line.match(/page (\d+) into frame (\d+)/);
      entry.type = "load";
      entry.action = `Loaded Page ${page} into Frame ${frame}`;
      entry.explanation = `Page ${page} was brought into memory and stored in frame ${frame}.`;
    } else if (line.includes("Replacing page")) {
      const [, page, frame] = line.match(/page (\d+) from frame (\d+)/);
      entry.type = "replace";
      entry.action = `Replaced Page ${page} from Frame ${frame}`;
      entry.explanation = `Page ${page} was removed from frame ${frame} to make room for a new page.`;
    } else if (line.includes("already in frame")) {
      const [, page, frame] = line.match(/Page (\d+) is already in frame (\d+)/);
      entry.type = "hit";
      entry.action = `Page Hit for Page ${page} in Frame ${frame}`;
      entry.explanation = `Page ${page} was already in memory (frame ${frame}). No page fault occurred.`;
    } else if (line.includes("MEMORY UTILIZATION")) {
      const [, used, total, percent] = line.match(/Used Frames: (\d+)\/(\d+) \(([\d.]+)%\)/);
      entry.type = "utilization";
      entry.action = `Memory Utilization: ${used}/${total} (${percent}%)`;
      entry.explanation = `Currently using ${used} out of ${total} frames (${percent}% utilization).`;
    } else {
      entry.explanation = "Unrecognized log entry.";
    }

    return entry;
  });
}
