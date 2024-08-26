"use client";
import { VersionTable } from '@/components/versionTable';
import { useState } from 'react';
 
export function Accordian() {
    const [openIndex, setOpenIndex] = useState<number | null>(1);

    const toggleAccordion = (index: number) => {
      setOpenIndex(openIndex === index ? null : index);
    };
  
    return (
      <div>
      <div id="accordion-collapse">
        <h2 id="accordion-collapse-heading-1">
          <button
            type="button"
            className="flex items-center justify-between w-full p-5 font-medium text-gray-500 border border-b-0 rounded-t-xl focus:ring-4 focus:ring-gray-200 dark:focus:ring-gray-800 dark:text-gray-400 hover:bg-neutral-800 gap-3"
            onClick={() => toggleAccordion(1)}
            aria-expanded={openIndex === 1}
            aria-controls="accordion-collapse-body-1"
          >
            <span>Sukuna v1</span>
            <svg
              className={`w-3 h-3 transition-transform duration-300 ${openIndex === 1 ? 'rotate-180' : ''}`}
              aria-hidden="true"
              xmlns="http://www.w3.org/2000/svg"
              fill="none"
              viewBox="0 0 10 6"
            >
              <path
                stroke="currentColor"
                strokeLinecap="round"
                strokeLinejoin="round"
                strokeWidth="2"
                d="M9 5 5 1 1 5"
              />
            </svg>
          </button>
        </h2>
        <div id="accordion-collapse-body-1" className={`${openIndex === 1 ? '' : 'hidden'}`} aria-labelledby="accordion-collapse-heading-1">
          <div className="p-5 border border-b-0 dark">
            {/* Table startes */}
            <VersionTable/>
            {/* Tables ends */}
            
          </div>
        </div>
  
        <h2 id="accordion-collapse-heading-2">
          <button
            type="button"
            className="flex items-center justify-between w-full p-5 font-medium text-gray-500 border border-b-0 focus:ring-4 focus:ring-gray-200 dark:focus:ring-gray-800 dark:text-gray-400 hover:bg-neutral-800 gap-3"
            onClick={() => toggleAccordion(2)}
            aria-expanded={openIndex === 2}
            aria-controls="accordion-collapse-body-2"
          >
            <span>Sukuna v2 (Coming soon)</span>
            <svg
              className={`w-3 h-3 transition-transform duration-300 ${openIndex === 2 ? 'rotate-180' : ''}`}
              aria-hidden="true"
              xmlns="http://www.w3.org/2000/svg"
              fill="none"
              viewBox="0 0 10 6"
            >
              <path
                stroke="currentColor"
                strokeLinecap="round"
                strokeLinejoin="round"
                strokeWidth="2"
                d="M9 5 5 1 1 5"
              />
            </svg>
          </button>
        </h2>
        <div id="accordion-collapse-body-2" className={`${openIndex === 2 ? '' : 'hidden'}`} aria-labelledby="accordion-collapse-heading-2">
          <div className="p-5 border border-b-0">
            
          </div>
        </div>
  
        
      </div></div>
    );
}