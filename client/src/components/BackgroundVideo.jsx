import Lanyard from "./Lanyard";

export default function BackgroundVideo() {
  return (
    <div className="relative w-full h-screen overflow-hidden">
      {/* Background video */}
      <video
        autoPlay
        loop
        muted
        playsInline
        className="absolute top-0 left-0 w-full h-full object-cover z-[-1]"
      >
        <source src="/background.mp4" type="video/mp4" />
        Your browser does not support the video tag.
      </video>

      {/* Foreground content with right aligned card */}

      <Lanyard position={[5, 1, 30]} gravity={[0, -40, 0]} />
    </div>
  );
}
