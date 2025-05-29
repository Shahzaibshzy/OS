import React, { useState } from 'react';

export default function OSSimulatorDropdown() {
  const [isOpen, setIsOpen] = useState(false);
  const [logs, setLogs] = useState('');
  const [loading, setLoading] = useState(false);
  const [error, setError] = useState(null);

  // Function to run the simulator and fetch logs
  const runSimulator = async () => {
    setLoading(true);
    setError(null);
    try {
      // Run the simulator
      const runResponse = await fetch('http://localhost:3000/run');
      if (!runResponse.ok) throw new Error('Failed to run simulator');

      // Fetch logs after simulator runs
      const logsResponse = await fetch('http://localhost:3000/logs');
      if (!logsResponse.ok) throw new Error('Failed to fetch logs');

      const logText = await logsResponse.text();
      setLogs(logText);
      setIsOpen(true); // auto open the dropdown
    } catch (err) {
      setError(err.message);
    } finally {
      setLoading(false);
    }
  };

  return (
    <div className="max-w-xl mx-auto mt-10 p-4">
      <button
        onClick={runSimulator}
        disabled={loading}
        className="w-full bg-sky-600 text-white py-2 rounded-md hover:bg-sky-700 transition mb-3 disabled:opacity-50"
      >
        {loading ? 'Running Simulator...' : 'Run Simulator and Fetch Logs'}
      </button>

      {error && (
        <div className="mb-3 text-red-600 font-semibold">{error}</div>
      )}

      <button
        onClick={() => setIsOpen(!isOpen)}
        className="w-full bg-sky-600 text-white py-2 rounded-md hover:bg-sky-700 transition flex justify-between items-center"
      >
        <span>Show OS Simulator Output</span>
        <svg
          className={`w-5 h-5 transform transition-transform duration-300 ${
            isOpen ? 'rotate-180' : ''
          }`}
          fill="none"
          stroke="currentColor"
          strokeWidth={2}
          viewBox="0 0 24 24"
          xmlns="http://www.w3.org/2000/svg"
        >
          <path strokeLinecap="round" strokeLinejoin="round" d="M19 9l-7 7-7-7" />
        </svg>
      </button>

      <div
        className={`overflow-auto transition-all duration-500 ease-in-out ${
          isOpen ? 'max-h-96 mt-4' : 'max-h-0'
        } bg-gray-100 rounded-md p-4 whitespace-pre-wrap text-sm font-mono text-gray-800`}
      >
        {logs || 'No logs to display. Run the simulator first.'}
      </div>
    </div>
  );
}
