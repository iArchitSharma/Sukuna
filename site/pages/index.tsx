import { Contact } from '@/components/contact';
import { HeroSection } from '@/components/hero';
import { HomeSections } from '@/components/homeSections';
import React from 'react';

const page = () => {
  return (
    <main>
      <HeroSection/>
      <HomeSections/>
      <Contact />
    </main>
  );
};

export default page;