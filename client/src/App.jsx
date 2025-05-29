import React from "react";
import BackgroundVideo from "./components/BackgroundVideo";
import Header from "./components/Header";

function App() {
  return (
    <div className="relative w-full h-screen overflow-hidden">
      <BackgroundVideo />

      {/* Lanyard behind the header */}

      {/* Header on top */}
      <Header />
    </div>
  );
}

export default App;
