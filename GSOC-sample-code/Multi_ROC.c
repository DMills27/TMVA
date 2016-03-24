#ifndef Multi_ROC
#define Multi_ROC

#include <iostream>
#include <vector>

#include "TFile.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TColor.h"
#include "gStyle.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TH1F.h"
#include "TTree.h"
#include "TH2F.h"

void Multi_ROC(){
    
    gStyle->SetOptStat(0);
    gStyle->SetLabelSize(0.08,"xy");
    gStyle->SetTitleSize(0.08, "xy");
    gStyle->SetTitleOffset(1.2, "xy");
    gStyle->SetPadTopMargin(0.1);
    gStyle->SetPadRightMargin(0.1);
    gStyle->SetPadBottomMargin(0.16);
    gStyle->SetPadLeftMargin(0.12);
    
    TFile* f = new TFile("mydataset.root");
    
    TCanvas *c1 = new TCanvas("c1", "c1", 800, 800);
    canvas->SetTickx();
    canvas->SetTicky();
    
    //Need to fix this section
    TH1F h1 = file1.Get("Var0Sig");
    TH1F h2 = file1.Get("Var1Sig");
    TH1F h3 = file1.Get("Var2Sig");
     
    h1->SetTitle('');
    h1->GetYaxis().SetTitle('Background rejection');
    h1->GetXaxis().SetTitle('Signal efficiency');
    h1->SetLineColor(TColor.kAzure);
    h1->SetLineWidth(2);
    h1->SetFillStyle(0);
    h1->SetFillColor(TColor.kAzure-2);
     
    h2->SetLineColor(TColor.kRed);
    h2->SetLineWidth(2);
    h2->SetFillStyle(0);
    
    h3->SetLineColor(TColor.kGreen);
    h3->SetLineWidth(2);
    h3->SetFillStyle(0);
     
    l = new TLegend(0.2, 0.25, 0.4, 0.45);
    l->SetTextSize(0.04);
    l->SetTextFont(42);
    l->SetFillColor(10);
    l->SetLineColor(10);
    l->SetBorderSize(0);
    l->AddEntry(h1,"5 trees","l");
    l->AddEntry(h2,"850 trees","l");
    l->AddEntry(h3,"2500 trees","l");
     
    h1->Draw("HIST");
    h2->Draw("HISTsame");
    h3->Draw("HISTsame");
    l->Draw("same");
    canvas->RedrawAxis();
    canvas->Print("ROC.png");
     
    file1.Close()
    
}