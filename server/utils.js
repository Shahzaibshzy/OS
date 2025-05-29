// server/utils.js

function extractSection(logText, startMarker, endMarker = null) {
  const startIndex = logText.indexOf(startMarker);
  if (startIndex === -1) return "";

  let endIndex = logText.length;
  if (endMarker) {
    endIndex = logText.indexOf(endMarker, startIndex);
    if (endIndex === -1) endIndex = logText.length;
  }

  return logText.substring(startIndex, endIndex).trim();
}

function parseKeyValueSection(text, regex = /^(.+?):\s*(.*)$/gm) {
  const result = {};
  let match;
  while ((match = regex.exec(text)) !== null) {
    result[match[1].trim()] = match[2].trim();
  }
  return result;
}

module.exports = { extractSection, parseKeyValueSection };
