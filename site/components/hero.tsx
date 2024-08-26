"use client";
import { TypewriterEffectSmooth } from "@/components/ui/typewriter-effect";
import { BackgroundBeams } from "./ui/background-beams";
import Link from 'next/link';

export function HeroSection() {
  const words = [
    { text: "Build" },
    { text: "awesome" },
    { text: "programs" },
    { text: "with" },
    { text: "Sukuna.", className: "text-blue-500 dark:text-blue-500" },
  ];

  return (
    <div className="relative h-[40rem] w-full bg-neutral-950 flex flex-col items-center justify-center antialiased">
      <div className="relative z-10 flex flex-col items-center justify-center h-[40rem]">
        <p className="text-neutral-600 dark:text-neutral-200 text-xs sm:text-base">
          This project is still in Beta mode
        </p>
        <TypewriterEffectSmooth words={words} />
        <div className="flex flex-col md:flex-row space-y-4 md:space-y-0 space-x-0 md:space-x-4">
          <button className="w-40 h-10 rounded-xl bg-black border dark:border-white border-transparent text-white text-sm">
            <Link href="/learn/">Get Started</Link>
          </button>
          <button
            className="relative inline-flex h-11 overflow-hidden rounded-xl p-[1.5px] focus:outline-none focus:ring-2 focus:ring-slate-400 focus:ring-offset-2 focus:ring-offset-slate-50">
            <span className="absolute inset-[-1000%] animate-[spin_2s_linear_infinite] bg-[conic-gradient(from_90deg_at_50%_50%,#E2CBFF_0%,#393BB2_50%,#E2CBFF_100%)]" />
            <span className="inline-flex w-40 h-10 cursor-pointer items-center justify-center rounded-xl bg-slate-950 px-3 py-1 text-sm font-medium text-white backdrop-blur-3xl">
              <Link href="/download/">Download</Link>
            </span>
          </button>
        </div>
      </div>
      <BackgroundBeams  />
    </div>
  );
}
