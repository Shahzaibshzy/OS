import { useState } from "react";

export default function TabGrid() {
  const tabs = ["Disk Scheduler", "File System", "Memory Manager", "Security Module"];
  const [selected, setSelected] = useState(""); 

  return (
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
              onClick={() => setSelected(tab)}
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
  );
}
