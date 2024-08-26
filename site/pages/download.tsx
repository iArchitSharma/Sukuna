import { Accordian } from "@/components/accordian";


const Download: React.FC = () => {


  return (
    <div className='bg-neutral-950 h-full'>
      <h2 className="mb-5 text-xl sm:text-5xl text-white">
        Install Sukuna
      </h2>
      <p className="mb-5 text-md sm:text-xl text-white">After downloading a binary release suitable for your system, please follow the <a className="text-blue-500" href="#installation">installation instructions</a>.</p>

      <p className="mb-5 text-md sm:text-xl text-white">If you are building from source, follow the source installation instructions.</p>
      <Accordian />

      <h2 id="installation" className="mb-5 mt-10 text-xl sm:text-3xl text-white">
        Install Sukuna
      </h2>
      <p className="mb-5 text-md sm:text-xl text-white">Look for your computer's operating system below, then follow its installation instructions.</p>
      <h2 className="mb-3 mt-10 text-xl sm:text-3xl text-white">
      Installation Instructions for Windows
      </h2>
      <p className="mb-5 text-md sm:text-xl text-white">Follow the steps below to install the software on your Windows machine:</p>
      <p className="mb-2 text-sm sm:text-md text-white">1. First, download the archive file from the link provided above.</p>
      <p className="mb-2 text-sm sm:text-md text-white">2. The downloaded file is in <b>ZIP</b> format and needs to be extracted before installation. You can use the built-in Windows tool or a third-party application.</p>
      <p className="mb-2 text-sm sm:text-md text-white">3. Navigate to the extracted folder {'>'} Locate the <b>install.bat</b> file {'>'} <b>Run as administrator</b> to ensure the installation has the necessary permissions</p>
      <p className="mb-2 text-sm sm:text-md text-white">4. Add this to <b>PATH Environment Variable</b></p>

      <pre className="bg-neutral-900 text-white p-4 rounded-lg overflow-x-auto">
      <code className="font-mono text-sm">
      {`C:\\Program Files\\Sukuna\\`}
      </code>
    </pre>
    <h2 className="mb-3 mt-10 text-xl sm:text-3xl text-white">
      Installation Instructions for Linux
      </h2>
      <p className="mb-5 text-md sm:text-xl text-white">Follow the steps below to install the software on your Linux machine:</p>
      <p className="mb-2 text-sm sm:text-md text-white">1. First, download the archive file from the link provided above.</p>
      <p className="mb-2 text-sm sm:text-md text-white">2. The downloaded file is in <b>ZIP</b> format and needs to be extracted before installation.</p>
      <pre className="bg-neutral-900 text-white p-4 rounded-lg overflow-x-auto">
      <code className="font-mono text-sm">
      {`sudo apt-get install unzip`}<br/>
      {`unzip sukuna-linux-v1.zip`}
      </code>
    </pre>
      <p className="mb-2 text-sm sm:text-md text-white">3. Run the <b>install.sh</b> Script</p>
      <pre className="bg-neutral-900 text-white p-4 rounded-lg overflow-x-auto">
      <code className="font-mono text-sm">
      {`chmod +x install.sh`}<br/>
      {`sudo ./install.sh`}<br/>
      {`sudo chmod +x /usr/local/bin/sukuna`}
      </code>
    </pre>
    
    </div>
  );
};

export default Download;
