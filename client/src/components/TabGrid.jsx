import { useState, useRef, useEffect } from "react";
import { motion, AnimatePresence } from "framer-motion";

export default function TabGrid() {
  const tabs = [
    "Disk Scheduler",
    "File System",
    "Memory Manager",
    "Security Module",
  ];

  const tabEndpoints = {
    "Disk Scheduler": "http://localhost:3000/logs/ds",
    "File System": "http://localhost:3000/logs/fs",
    "Memory Manager": "http://localhost:3000/logs/mem",
    "Security Module": "http://localhost:3000/logs/scr",
  };

  const [selected, setSelected] = useState("");
  const [isModalOpen, setIsModalOpen] = useState(false);
  const [modalContent, setModalContent] = useState("Loading...");
  const [error, setError] = useState("");
  const [cache, setCache] = useState({});
  const modalRef = useRef(null);

  const handleTabClick = async (tab) => {
  setSelected(tab);
  setIsModalOpen(true);
  setError("");

  if (cache[tab]) {
    setModalContent(cache[tab]);
    return;
  }

  setModalContent("Loading...");

  try {
    const response = await fetch(tabEndpoints[tab]);
    if (!response.ok) throw new Error(`Failed to fetch data for "${tab}".`);

    const text = await response.text();
    const parsed = tab === "Memory Manager"
      ? extractMemorySections(text)
      : { log: text, table: null };

    setModalContent(parsed);
    setCache((prev) => ({ ...prev, [tab]: parsed }));
  } catch (err) {
    setModalContent("");
    setError(err.message);
  }
};


  const closeModal = () => {
    setIsModalOpen(false);
    setSelected("");
    setError("");
  };

  // Close modal when clicking outside the content
  useEffect(() => {
    const handleClickOutside = (event) => {
      if (modalRef.current && !modalRef.current.contains(event.target)) {
        closeModal();
      }
    };
    if (isModalOpen) {
      document.addEventListener("mousedown", handleClickOutside);
    }
    return () => {
      document.removeEventListener("mousedown", handleClickOutside);
    };
  }, [isModalOpen]);


  function extractMemorySections(text) {
  const lines = text.split("\n");
  const tableStartIndex = lines.findIndex(line => line.trim() === "[PAGE TABLE]");
  if (tableStartIndex === -1) {
    return { log: text.trim(), table: null };
  }

  const log = lines.slice(0, tableStartIndex).join("\n").trim();
  const headers = lines[tableStartIndex + 1].trim().split(/\s+/);
  const rows = [];

  for (let i = tableStartIndex + 2; i < lines.length; i++) {
    const line = lines[i].trim();
    if (line === "" || line.toLowerCase().startsWith("total page faults")) break;
    const [Page, Frame, Valid] = line.split(/\s+/);
    rows.push({ Page, Frame, Valid });
  }

  return {
    log,
    table: { headers, rows },
  };
}

  return (
    <>
      <div className="mx-auto grid max-w-4xl grid-cols-2 gap-4 px-4 py-12 lg:grid-cols-4">
        {tabs.map((tab) => {
          const isSelected = selected === tab;
          const bgColor = isSelected ? "bg-purple-600" : "bg-transparent";
          const borderColor = isSelected ? "border-white-600" : "border-white";
          const textColor = isSelected ? "text-white" : "text-white";
          const translateY = isSelected ? "-translate-y-1" : "";
          const rotateClass = !isSelected
            ? "hover:-rotate-2 hover:border-purple-600"
            : "";

          return (
            <div
              key={tab}
              className={`rounded-lg transition-colors ${bgColor}`}
            >
              <button
                onClick={() => handleTabClick(tab)}
                className={`
                  w-full origin-top-left rounded-lg border py-3 text-xs font-medium 
                  transition-all md:text-base ${borderColor} ${textColor} ${translateY} ${rotateClass} 
                `}
              >
                {tab}
              </button>
            </div>
          );
        })}
      </div>

      {/* Modal with animation, click-outside, glass effect, and caching */}
      <AnimatePresence>
        {isModalOpen && (
          <motion.div
            className="fixed inset-0 z-50 flex items-center justify-center bg-black/50 backdrop-blur-sm"
            initial={{ opacity: 0 }}
            animate={{ opacity: 1 }}
            exit={{ opacity: 0 }}
          >
            <motion.div
              ref={modalRef}
              initial={{ scale: 0.8, opacity: 0 }}
              animate={{ scale: 1, opacity: 1 }}
              exit={{ scale: 0.8, opacity: 0 }}
              transition={{ duration: 0.3 }}
              className="relative w-full max-w-md rounded-md border border-white/30 bg-white/10 p-6 text-white backdrop-blur-md shadow-lg"
            >
              <button
                onClick={closeModal}
                className="absolute right-3 top-3 text-white hover:text-red-500"
              >
                &#10005;
              </button>
              <h2 className="mb-4 text-lg font-semibold">{selected}</h2>
              {error ? (
  <p className="text-red-400">{error}</p>
) : (
  <div className="max-h-80 overflow-y-auto pr-2 text-sm space-y-4">
    {/* Log content */}
    <pre className="whitespace-pre-wrap">{modalContent.log}</pre>

    {/* Optional page table for memory */}
    {selected === "Memory Manager" && modalContent.table && (
      <div>
        <h3 className="text-base font-semibold mb-2">Page Table</h3>
        <table className="w-full table-auto border border-white/30 text-left text-xs">
          <thead>
            <tr className="bg-white/10">
              {modalContent.table.headers.map((header, i) => (
                <th key={i} className="border border-white/20 px-3 py-1">
                  {header}
                </th>
              ))}
            </tr>
          </thead>
          <tbody>
            {modalContent.table.rows.map((row, i) => (
              <tr key={i} className="hover:bg-white/5">
                <td className="border border-white/20 px-3 py-1">{row.Page}</td>
                <td className="border border-white/20 px-3 py-1">{row.Frame}</td>
                <td className="border border-white/20 px-3 py-1">{row.Valid}</td>
              </tr>
            ))}
          </tbody>
        </table>
      </div>
    )}
  </div>
)}

            </motion.div>
          </motion.div>
        )}
      </AnimatePresence>
    </>
  );
}
