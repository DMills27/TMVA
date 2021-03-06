#include <vector>
#include <string>
#include "tmvaglob.C"

#include "TH1.h"
#include "TGraph.h"

// input: - Input file (result from TMVA),
//        - use of TMVA plotting TStyle
void bdtcontrolplots(TDirectory *);

void BDTControlPlots( TString fin = "TMVA.root", Bool_t useTMVAStyle = kTRUE )
{
   // set style and remove existing canvas'
   TMVAGlob::Initialize( useTMVAStyle );
  
   // checks if file with name "fin" is already open, and if not opens one
   TFile* file;
   file = TMVAGlob::OpenFile( fin );  

   // get all titles of the method BDT
   TList titles;
   TString methodName = "Method_BDT";
   UInt_t ninst = TMVAGlob::GetListOfTitles(methodName,titles);
   if (ninst==0) {
      cout << "Could not locate directory 'Method_BDT' in file " << fin << endl;
      return;
   }
   // loop over all titles
   TIter keyIter(&titles);
   TDirectory *bdtdir;
   TKey *key;
   while ((key = TMVAGlob::NextKey(keyIter,"TDirectory"))) {
      bdtdir = (TDirectory *)key->ReadObj();
      bdtcontrolplots( bdtdir );
   }
}

void bdtcontrolplots( TDirectory *bdtdir ) {

   const Int_t nPlots = 6;

   Int_t width  = 900;
   Int_t height = 600;
   char cn[100], cn2[100];
   const TString titName = bdtdir->GetName();
   sprintf( cn, "cv_%s", titName.Data() );
   TCanvas *c = new TCanvas( cn,  Form( "%s Control Plots", titName.Data() ),
                             width, height ); 
   c->Divide(3,2);




   TString hname[nPlots]={"BoostMonitor","BoostWeight","BoostWeightVsTree","ErrFractHist","NodesBeforePruning",titName+"_FOMvsIterFrame"};

   Bool_t BoostMonitorIsDone=kFALSE;

   for (Int_t i=0; i<nPlots; i++){
      Int_t color = 4; 
      c->cd(i+1);
      TH1 *h = (TH1*) bdtdir->Get(hname[i]);
      
      if (h){
         h->SetMaximum(h->GetMaximum()*1.3);
         h->SetMinimum( 0 );
         h->SetMarkerColor(color);
         h->SetMarkerSize( 0.7 );
         h->SetMarkerStyle( 24 );
         h->SetLineWidth(1);
         h->SetLineColor(color);
         if(hname[i]=="NodesBeforePruning")h->SetTitle("Nodes before/after pruning");
         h->Draw();
         if(hname[i]=="NodesBeforePruning"){
            TH1 *h2 = (TH1*) bdtdir->Get("NodesAfterPruning");
            h2->SetLineWidth(1);
            h2->SetLineColor(2);
            h2->Draw("same");
         }
         if(hname[i]=="BoostMonitor"){ // a plot only available in case DoBoostMontior option has bee set
            TGraph *g = (TGraph*) bdtdir->Get("BoostMonitorGraph");
            g->Draw("LP*");
            BoostMonitorIsDone = kTRUE;
         }
         if(hname[i]==titName+"_FOMvsIterFrame"){ // a plot only available in case DoBoostMontior option has bee set
            TGraph *g = (TGraph*) bdtdir->Get(titName+"_FOMvsIter");
            g->Draw();
         }
         c->Update();
      }
   }
   
   
   TCanvas *c2 = NULL;
   if (BoostMonitorIsDone){
      sprintf( cn2, "cv2_%s", titName.Data() );
      c2 = new TCanvas( cn2,  Form( "%s BoostWeights", titName.Data() ),
                                 1200, 1200 ); 
      c2->Divide(5,5);
      Int_t ipad=1;
      
      TIter keys( bdtdir->GetListOfKeys() );
      TKey *key;
      //      gDirectory->ls();
      while ( (key = (TKey*)keys.Next()) && ipad < 26) {
         TObject *obj=key->ReadObj();
         if (obj->IsA()->InheritsFrom(TH1::Class())){   
            TH1F *hx = (TH1F*)obj;
            TString hhname(Form("%s",obj->GetTitle()));
            if (hhname.Contains("BoostWeightsInTreeB")){ 
               c2->cd(ipad++);
               hx->SetLineColor(4);
               hx->Draw();
               hhname.ReplaceAll("TreeB","TreeS");
               bdtdir->GetObject(hhname.Data(),hx);
               if (hx) {
                  hx->SetLineColor(2);
                  hx->Draw("same");
               }
            }
            c2->Update();
         }
      }
               
   }

   // write to file
   TString fname = Form( "plots/%s_ControlPlots", titName.Data() );
   TMVAGlob::imgconv( c, fname );
   
   if (c2){
      fname = Form( "plots/%s_ControlPlots2", titName.Data() );
      TMVAGlob::imgconv( c2, fname );
   }

   TCanvas *c3 = NULL;
   if (BoostMonitorIsDone){
      sprintf( cn2, "cv3_%s", titName.Data() );
      c3 = new TCanvas( cn2,  Form( "%s Variables", titName.Data() ),
                        1200, 1200 ); 
      c3->Divide(5,5);
      Int_t ipad=1;
      
      TIter keys( bdtdir->GetListOfKeys() );
      TKey *key;
      //      gDirectory->ls();
      while ( (key = (TKey*)keys.Next()) && ipad < 26) {
         TObject *obj=key->ReadObj();
         if (obj->IsA()->InheritsFrom(TH1::Class())){   
            TH1F *hx = (TH1F*)obj;
            TString hname(Form("%s",obj->GetTitle()));
            if (hname.Contains("SigVar0AtTree")){ 
               c3->cd(ipad++);
               hx->SetLineColor(4);
               hx->Draw();
               hname.ReplaceAll("Sig","Bkg");
               bdtdir->GetObject(hname.Data(),hx);
               if (hx) {
                  hx->SetLineColor(2);
                  hx->Draw("same");
               }
            }
            c3->Update();
         }
      }
               
   }


}


