# DAPP_Project

Project Detectors and Accelerators in Particle Physics  
The codes are copies of AnaEx01 to which small modifications have been made to make them more suitable for the course project Detectors and Accelerators in Particle Physics.  

## Modifications made  
- AnaEx01.cc:  
  * I inserted setters to modify materials and the geometry of the detector to obtain a single Polystyrene block  
  * I added a `while` loop that saves in a root file, with the same name as the macro, the histograms obtained at the end of the simulation (e.g. gamma.mac->gamma.root). If the simulation is launched without a macro, the histograms will automatically be saved in "AnaEx001.root".  

- ActionInizialize:  
  * I modified both the `header` and the `source` by adding a string variable that passes the name of the macro to HistoManager  

- HistoManager:  
  * I added the string variable to pass to `analysisManager->OpenFile()`  
  * I modified the default settings of the histograms by changing the bins from 100 to 700 (a rebinning could be done later in the root file), and the maximum from 800 MeV to 700 keV  

- StackingEvent.cc:  
  * I commented out the line that printed the number of positrons (nPositrons) to the terminal for each event to avoid unnecessary prints  

- gamma.mac:  
  * I changed the energy from 10 MeV to 662 keV, the number of events to 100,000, set all `verbose` to 0, and set `/vis/disable` and `/tracking/storeTrajectory 0`  

- plotHisto.C:  
  * I removed the plots of histograms that are not relevant to our case
  *Ensured that the root file containing the histogram to be plotted is passed as an argument to the plotHisto function. (e.g. if you want to plot the histogram of the energy absorbed by the block contained in the file gammaQSGP_BIC_EMZ.root, you should launch the command: `root -l 'plotHisto.C("build/gammaQGSP_BIC_EMZ.root")'`, where specifying the path is necessary if the plotHisto.C code is in a different directory from the root file to be plotted.)
