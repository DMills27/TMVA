#include <TFile.h>
#include <TH1.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

#include <vector>
#include <iostream>

//Computes efficiencies
void GetROC(float[] *sig, float[] *bac){
  
  int ndivisions = 40;
  std::vector<Float_t> vec_epsilon_s(1);
  vec_epsilon_s.push_back(0);
  
  std::vector<Float_t>  vec_epsilon_b(1);
  vec_epsilon_b.push_back(0);
  
  Float_t epsilon_s = 0.0;
  Float_t epsilon_b = 0.0;

  for(Float_t i=-1.0;i<1.0;i+=(1.0/ndivisions))
  {
      Float_t acounter = 0.0;
      Float_t bcounter = 0.0;
      Float_t ccounter = 0.0;
      Float_t dcounter = 0.0;
      
      for(UInt_t j=0;j<sig.size();j++)
      {
        if(sig[j] > i) acounter++;
        else            bcounter++;
	
        if(bac[j] > i) ccounter++;
        else            dcounter++;
      }
      
      if(acounter != 0 || bcounter != 0)
      {
	epsilon_s = 1.0*bcounter/(acounter+bcounter);
      }
      vec_epsilon_s.push_back(epsilon_s);
      
      if(ccounter != 0 || dcounter != 0)
      {
	epsilon_b = 1.0*dcounter/(ccounter+dcounter);
      }
      vec_epsilon_b.push_back(epsilon_b);      
  }
  vec_epsilon_s.push_back(1.0);
  vec_epsilon_b.push_back(1.0);
  
}

void Multi_ROC(TFile* file){
    
    //Create vectors to store the Background values          
    std::vector<float>* Var0Bkg;
    std::vector<float>* Var1Bkg;
    std::vector<float>* Var2Bkg;
   
    //Create vectors to store the Signal values
    std::vector<float>* Var0Sig;
    std::vector<float>* Var1Sig;
    std::vector<float>* Var2Sig;
    
    //Assumes trees are named 'MyMCBkg' and 'MyMCSig'
    TTree* Background = (TTree*) file.Get("MyMCBkg"); //Get the Background signal tree from the file
    TTree* Signal = (TTree*) file.Get("MyMCSig"); //Get the Background signal tree from the file
    
    // Links the local variables to the tree branches. TTreeReader could have also been used to do this job.
    Background->SetBranchAddress("Var0Bkg", &Var0Bkg);
    Background->SetBranchAddress("Var1Bkg", &Var1Bkg);
    Background->SetBranchAddress("Var2Bkg", &Var2Bkg);
    // After this stage the local variables are still empty.
    // With every subsequent call to myTree->GetEntry(i) the local variables will be filled with the content of branches
    
    //Does the same as above except with the Signal branches instead
    Signal->SetBranchAddress("Var0Sig", &Var0Sig);
    Signal->SetBranchAddress("Var1Sig", &Var1Sig);
    Signal->SetBranchAddress("Var2Sig", &Var2Sig);
    
    // Loops over all entries in the Background tree
    int nEntries1 = Background->GetEntries(); // Get the number of entries in this tree
    for (int iEnt = 0; iEnt < nEntries1; iEnt++) {
        Background->GetEntry(iEnt); // Gets the next entry (filling the linked variables)
    }
    
    // Loops over all entries in the Signal tree
    int nEntries2 = Signal->GetEntries(); // Get the number of entries in this tree
    for (int iEnt = 0; iEnt < nEntries2; iEnt++) {
        Signal->GetEntry(iEnt); // Gets the next entry (filling the linked variables)
    }
    
        TCanvas *c1 = new TCanvas("c1","ROC Curve",700,500);
        TMultiGraph *mg = new TMultiGraph();
        
        //Compute signal efficiencies and background rejection for first graph
        GetROC(Var0Sig, Var0Bkg);
        //Create first ROC curve
        TGraph *gr1 = new TGraph(nEntries1,vec_epsilon_b,vec_epsilon_s); //signal:  y-axis; background: x-axis
        gr1->SetLineColor(4);
        
        mg->Add(gr1);
        
        //Computes signal efficiencies and background rejection for second graph
        GetROC(Var1Sig, Var1Bkg);
        //Create second ROC curve
        TGraph *gr2 = new TGraph(nEntries1,vec_epsilon_b,vec_epsilon_s); //signal:  y-axis; background: x-axis
        gr1->SetLineColor(3);
        
        mg->Add(gr2);
        
        //Computes signal efficiencies and background rejection for third graph
        GetROC(Var2Sig, Var2Bkg);
        //Create third ROC curve
        TGraph *gr3 = new TGraph(nEntries1,vec_epsilon_b,vec_epsilon_s); //signal:  y-axis; background: x-axis
        gr1->SetLineColor(2);
        
        mg->Add(gr3);
        mg->Draw();
        return c1;
        
        c1->Print("ROC.png");
        file.Close();

}
