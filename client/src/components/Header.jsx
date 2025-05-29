import BlurText from "./BlurText";
import TabGrid from "./TabGrid";
import Lanyard from "./Lanyard";
const Header = () => {
  return (
    <header className="absolute top-0 left-0 w-full z-10">
      <div className="flex justify-between items-center px-20 py-4 bg-opacity-60 backdrop-blur-md text-white">
        {/* Left - Logo + Market Info */}
        <div className="flex items-center justify-center space-x-8">
          <BlurText
            text="OS - CCP"
            delay={130}
            animateBy="words"
            direction="top"
            className="text-2xl mb-0 font-bold"
          />
          <BlurText
            text="Shahzaib Khan (67421)"
            delay={130}
            animateBy="words"
            direction="top"
            className="text-2xl mb-0 font-bold"
          />
        </div>
      </div>
      <div className="border-b border-white opacity-20 w-full" />
      <TabGrid />
     
    </header>
  );
};

export default Header;
