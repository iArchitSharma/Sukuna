"use client";
import React from "react";
import { StickyScroll } from "@/components/ui/sticky-scroll-reveal";
import Image from "next/image";
 
const content = [
  {
    title: "Performance",
    description:
      "Sukuna is blazingly fast and memory-efficient: with no runtime or garbage collector, it can power performance-critical services, run on embedded devices, and easily integrate with other languages.",
    content: (
      <div className="h-full w-full bg-[linear-gradient(to_bottom_right,var(--cyan-500),var(--emerald-500))] flex items-center justify-center text-white">
        Performance
      </div>
    ),
  },
  {
    title: "Simple",
    description:
      "Sukuna is designed with simplicity at its core, making it an ideal programming language for developers who value clear and concise code. Its straightforward structure eliminate unnecessary complexity, allowing you to focus on building functionality.",
    content: (
        <div className="h-full w-full flex items-center justify-center text-white">
        <Image
          src="/compiler.png"
          width={900}
          height={900}
          className="h-full w-full object-contain"
          alt="linear board demo"
        />
      </div>
    ),
  },
  {
    title: "Open Source",
    description:
      "Sukuna is an open-source programming language designed for developers who value flexibility and community-driven development. By being open source, Sukuna allows anyone to contribute to its growth and improvement, fostering a collaborative environment where innovation thrives.",
    content: (
        <div className="h-full w-full flex items-center justify-center text-white">
  <Image
    src="/github.png"
    width={900}
    height={900}
    className="h-full w-full object-contain"
    alt="linear board demo"
  />
</div>
    ),
  },
];
export function HomeSections() {
  return (
    <div>
      <StickyScroll content={content} />
    </div>
  );
}