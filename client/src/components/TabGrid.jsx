import { useState } from "react";

export default function TabGrid() {
  const tabs = ["Disk Scheduler", "File System", "Memory Manager", "Security Module"];
  const [selected, setSelected] = useState(""); 
  const [isModalOpen, setIsModalOpen] = useState(false);
  const [modalContent, setModalContent] = useState("");

  const handleTabClick = (tab) => {
    setSelected(tab);
    // Simulate API data fetch
    setModalContent(`This is some text content for "${tab}".`); // Replace with actual fetch later
    setIsModalOpen(true);
  };

  const closeModal = () => {
    setIsModalOpen(false);
    setSelected("");
  };

  return (
    <>
      <div className="mx-auto grid max-w-4xl grid-cols-2 gap-4 px-4 py-12 lg:grid-cols-4">
        {tabs.map((tab) => {
          const isSelected = selected === tab;
          const bgColor = isSelected ? "bg-purple-600" : "bg-transparent";
          const borderColor = isSelected ? "border-white-600" : "border-white";
          const textColor = isSelected ? "text-white" : "text-white";
          const translateY = isSelected ? "-translate-y-1" : "";
          const rotateClass = !isSelected ? "hover:-rotate-2" : "";

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

      {/* Modal */}
      {isModalOpen && (
        <div className="fixed inset-0 z-50 flex items-center justify-center bg-black bg-opacity-60">
          <div className="relative w-full max-w-md rounded-lg bg-white p-6 shadow-lg">
            <button
              onClick={closeModal}
              className="absolute right-3 top-3 text-gray-500 hover:text-red-500"
            >
              &#10005;
            </button>
            <h2 className="mb-4 text-lg font-semibold">{selected}</h2>
            <p className="text-gray-700">{modalContent}</p>
          </div>
        </div>
      )}
    </>
  );
}
