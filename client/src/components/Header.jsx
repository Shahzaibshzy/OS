import React, { useState, useRef, useEffect } from "react";
import { AnimatePresence, motion } from "framer-motion";
import BlurText from "./BlurText";
import TabGrid from "./TabGrid";

const Header = () => {
  const [selected, setSelected] = useState("");
  const [isModalOpen, setIsModalOpen] = useState(false);
  const [modalContent, setModalContent] = useState("");
  const [loading, setLoading] = useState(false);
  const modalRef = useRef(null);

  const handleButtonClick = async (label) => {
    setSelected(label);
    setIsModalOpen(true);
    setModalContent("Loading...");
    setLoading(true);

    const apiEndpoint =
      label === "logs"
        ? "http://localhost:3000/logs"
        : label === "run"
        ? "http://localhost:3000/run"
        : null;

    if (!apiEndpoint) {
      setModalContent("Invalid action.");
      setLoading(false);
      return;
    }

    try {
      const res = await fetch(apiEndpoint);
      const text = await res.text();
      setModalContent(text);
    } catch (error) {
      setModalContent("Error: Something went wrong while fetching.");
    }

    setLoading(false);
  };

  const closeModal = () => {
    setIsModalOpen(false);
    setSelected("");
  };

  // Close on outside click
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

  const renderButton = (label) => {
    const isSelected = selected === label;
    const bgColor = isSelected ? "bg-purple-600" : "bg-transparent";
    const borderColor = isSelected ? "border-white-600" : "border-white";
    const textColor = "text-white";
    const translateY = isSelected ? "-translate-y-1" : "";
    const rotateClass = !isSelected ? "hover:-rotate-2 hover:border-purple-600" : "";

    return (
      <div key={label} className={`rounded-lg transition-colors ${bgColor} mx-1`}>
        <button
          disabled={loading || isSelected}
          onClick={() => handleButtonClick(label)}
          className={`
            w-full origin-top-left rounded-lg border py-2 px-3 text-xs md:text-sm
            font-medium transition-all ${borderColor} ${textColor} ${translateY} ${rotateClass}
            disabled:cursor-not-allowed disabled:opacity-70
          `}
        >
          {label}
        </button>
      </div>
    );
  };

  return (
    <>
      <header className="absolute top-0 left-0 w-full z-10">
        <div className="flex flex-wrap md:flex-nowrap justify-between items-center px-4 md:px-8 lg:px-12 py-2 bg-opacity-60 backdrop-blur-md text-white">
          {/* Left - Logo + Info */}
          <div className="flex items-center space-x-3 md:space-x-6 mb-1 md:mb-0">
            <BlurText
              text="OS - CCP"
              delay={130}
              animateBy="words"
              direction="top"
              className="text-lg md:text-xl font-bold"
            />
            <BlurText
              text="Shahzaib Khan (67421)"
              delay={130}
              animateBy="words"
              direction="top"
              className="text-xs md:text-xl font-bold"
            />
            <BlurText
              text="Ram Kumar (67452)"
              delay={130}
              animateBy="words"
              direction="top"
              className="text-xs md:text-xl font-bold"
            />
          </div>

          {/* Right - Buttons */}
          <div className="flex space-x-2">
            {["run"].map(renderButton)}
          </div>
        </div>

        <div className="border-b border-white opacity-20 w-full" />
        <TabGrid />
      </header>

      {/* Modal Popup */}
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
              className="relative w-full max-w-sm rounded-md border border-white/30 bg-white/10 p-4 text-white backdrop-blur-md shadow-lg"
            >
              <button
                onClick={closeModal}
                className="absolute right-3 top-3 text-white hover:text-red-500 text-lg font-bold"
                aria-label="Close modal"
              >
                &#10005;
              </button>
              <h2 className="mb-3 text-base font-semibold">{selected}</h2>
              <div className="max-h-80 overflow-y-auto whitespace-pre-line pr-2 text-sm">
                {modalContent}
              </div>
            </motion.div>
          </motion.div>
        )}
      </AnimatePresence>
    </>
  );
};

export default Header;