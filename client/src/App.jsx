import React from "react";
import BackgroundVideo from "./components/BackgroundVideo";
import Header from "./components/Header";
import Lanyard from "./components/Lanyard";

function App() {
  return (
    <div className="relative w-full h-screen overflow-hidden">
      <BackgroundVideo />

      {/* Lanyard behind the header */}
      <div className="absolute top-0 right-0 p-4 z-0 pointer-events-none">
        <Lanyard position={[0, -2, 30]} gravity={[0, -40, 0]} />
      </div>

      {/* Header on top */}
      <Header />
    </div>
  );
}

export default App;
