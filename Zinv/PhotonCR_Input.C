#include "TH1F.h"
#include "ReadTree.cc"
#include "SetStyle.C"
#include "StackPlot.C"
using namespace std;
void PhotonCR_Input(){

     //Sets the style of Canvas ,it is like the tdrStyle function
     TStyle *gStyle = new TStyle("gStyle","Style for P-TDR");
     SetStyle st;
     st.SetPars(gStyle);
    
     
     //Creates a root file that will store all the histograms needed for prediction later
     TFile *f =new TFile("PhotonCR_Input.root","RECREATE"); 
     //Location of Ntuples
     //TString InputFilePath="root://cmseos.fnal.gov//store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV5/";
     TString InputFilePath="root://cmseos.fnal.gov//store/user/cmsdas/2017/long_exercises/SUSYHadronic/";
     

     //Reads GJets MC Ntuples
     TChain* tGJets = new TChain("tree");
     tGJets->Add(InputFilePath+"tree_GJet_CleanVarsGJloose/tree_GJets_HT-100to200.root");
     tGJets->Add(InputFilePath+"tree_GJet_CleanVarsGJloose/tree_GJets_HT-200to400.root");
     tGJets->Add(InputFilePath+"tree_GJet_CleanVarsGJloose/tree_GJets_HT-400to600.root");
     tGJets->Add(InputFilePath+"tree_GJet_CleanVarsGJloose/tree_GJets_HT-600toInf.root");
     ReadTree GJets(tGJets);

     //reads QCD MC Ntuples
     TChain* tQCD = new TChain("tree");
     tQCD->Add(InputFilePath+"tree_GJet_CleanVarsGJloose/tree_QCD_HT-200to300.root");
     tQCD->Add(InputFilePath+"tree_GJet_CleanVarsGJloose/tree_QCD_HT-300to500.root");
     tQCD->Add(InputFilePath+"tree_GJet_CleanVarsGJloose/tree_QCD_HT-500to700.root");
     tQCD->Add(InputFilePath+"tree_GJet_CleanVarsGJloose/tree_QCD_HT-700to1000.root");
     tQCD->Add(InputFilePath+"tree_GJet_CleanVarsGJloose/tree_QCD_HT-1000to1500.root");
     tQCD->Add(InputFilePath+"tree_GJet_CleanVarsGJloose/tree_QCD_HT-1500to2000.root");
     tQCD->Add(InputFilePath+"tree_GJet_CleanVarsGJloose/tree_QCD_HT-2000toInf.root");
     ReadTree QCD(tQCD);

     //Reads Data Ntuples
     TChain* tDataGJ = new TChain("tree");
     tDataGJ->Add(InputFilePath+"tree_GJet_CleanVarsGJloose/tree_SinglePhoton_re2015C.root");
     tDataGJ->Add(InputFilePath+"tree_GJet_CleanVarsGJloose/tree_SinglePhoton_re2015D.root");
     tDataGJ->Add(InputFilePath+"tree_GJet_CleanVarsGJloose/tree_SinglePhoton_2015Db.root");
     ReadTree DataGJ(tDataGJ);


     //defines integrated luminocity for the Data 
     double Lumi=2262.;


    double rangeMax=0.02;
    double rangeMin=0.005;
    int nBins=40;

    TH1F *hpromptSR_Scut=new TH1F("hpromptSR_Scut","hpromptSR_Scut",nBins,rangeMin,rangeMax);
    hpromptSR_Scut->SetLineWidth(1);

    TH1F *hpromptPlusnonPromptSR_Scut=new TH1F("hpromptPlusnonPromptSR_Scut","hpromptPlusnonPromptSR_Scut",nBins,rangeMin,rangeMax);
    hpromptPlusnonPromptSR_Scut->SetLineWidth(1);


    TH1F *hpromptSR=new TH1F("hpromptSR","hpromptSR",nBins,rangeMin,rangeMax);
    hpromptSR->SetLineWidth(1);


    TH1F *hnonpromptSR=new TH1F("hnonpromptSR","hnonpromptSR",nBins,rangeMin,rangeMax);
    hnonpromptSR->SetLineWidth(1);

    TH1F *hnonpromptSB=new TH1F("hnonpromptSB","hnonpromptSB",nBins,rangeMin,rangeMax);
    hnonpromptSB->SetLineWidth(1);

    TH1F *hDataSR=new TH1F("hDataSR","hDataSR",nBins,rangeMin,rangeMax);
    hDataSR->SetLineWidth(1);    
  
    TH1F *hDataSB=new TH1F("hDataSB","hDataSB",nBins,rangeMin,rangeMax);
    hDataSB->SetLineWidth(1);
 


 
     

    
     cout<<"max events GJets: "<<tGJets->GetEntries()<<endl; 
     for(int iEv=0;iEv<tGJets->GetEntries();iEv++){//Looping over GJets MC events
     tGJets->GetEntry(iEv);
     if(iEv % 100000==0){cout<<"Event no [GJets] : "<<iEv<<endl;}
     

         if(GJets.BaselineLoose()==true && GJets.isBarrelPhoton()==true && GJets.IchSR()==true && GJets.Prompt()==true ){
           
            
            hpromptSR->Fill(GJets.photon_sigmaIetaIeta->at(GJets.photonIndex()),Lumi*GJets.Weight);

            if(GJets.photon_sigmaIetaIeta->at(GJets.photonIndex()) < 0.0107){
               hpromptSR_Scut->Fill(GJets.photon_sigmaIetaIeta->at(GJets.photonIndex()),Lumi*GJets.Weight);
               hpromptPlusnonPromptSR_Scut->Fill(GJets.photon_sigmaIetaIeta->at(GJets.photonIndex()),Lumi*GJets.Weight);

                 }                

            }


     }//Looping over GJets MC events


    
    for(int iEv=0;iEv<tQCD->GetEntries();iEv++){//Looping over QCD MC events
     tQCD->GetEntry(iEv);
     if(iEv % 100000==0){cout<<"Event no [QCD] : "<<iEv<<endl;}

       if(QCD.BaselineLoose()==true && QCD.isBarrelPhoton()==true  && QCD.nonPrompt()==true ){

            if(QCD.IchSR()==true){
            hnonpromptSR->Fill(QCD.photon_sigmaIetaIeta->at(QCD.photonIndex()),Lumi*QCD.Weight);
                 if(QCD.photon_sigmaIetaIeta->at(QCD.photonIndex()) < 0.0107){
                 hpromptPlusnonPromptSR_Scut->Fill(QCD.photon_sigmaIetaIeta->at(QCD.photonIndex()),Lumi*QCD.Weight);
                 }




               }
            if(QCD.IchSB()==true){
            hnonpromptSB->Fill(QCD.photon_sigmaIetaIeta->at(QCD.photonIndex()),Lumi*QCD.Weight);     

                }



            }



     }//Looping over QCD MC events


    
    for(int iEv=0;iEv<tDataGJ->GetEntries();iEv++){//Looping over Data  events
     tDataGJ->GetEntry(iEv);
     if(iEv % 100000==0){cout<<"Event no [Data GJ] : "<<iEv<<endl;}

     if(DataGJ.PASStriggerGJ()==true  && DataGJ.BaselineLoose()==true && DataGJ.isBarrelPhoton()==true && DataGJ.IchSR()==true  ){//Pass Photon CR criteria for Data


      hDataSR->Fill(DataGJ.photon_sigmaIetaIeta->at(DataGJ.photonIndex()));


      }//Pass 


    if(DataGJ.PASStriggerGJ()==true  && DataGJ.BaselineLoose()==true && DataGJ.isBarrelPhoton()==true && DataGJ.IchSB()==true  ){//

    hDataSB->Fill(DataGJ.photon_sigmaIetaIeta->at(DataGJ.photonIndex()));

   }




      }//Looping over Data events


   double pureMCPurity=hpromptSR_Scut->Integral()/hpromptPlusnonPromptSR_Scut->Integral();

   cout<<"MC only purity: "<<pureMCPurity<<endl;


    f->Write();

     

}
