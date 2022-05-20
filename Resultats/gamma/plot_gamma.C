{
gROOT->Reset();
gStyle->SetPalette(1);
//Constantes
double M=28.08550;
double Na=6.0221408e+23;
double d=2.329002;

const float thinkness=0.01;

TFile* myFile = new TFile("data.root");
TTree* myTree = (TTree*) myFile->Get("theRunTree");
TGraphErrors* simutotal = new TGraphErrors();
TGraphErrors* simuconv = new TGraphErrors();
TGraphErrors* simucompt = new TGraphErrors();
TGraphErrors* simuphot = new TGraphErrors();
TGraphErrors* simurayl = new TGraphErrors();

vector <float> *edep;
vector <double> *e;
vector <float> *l;
int process;

myTree->SetBranchAddress("EdepPart", &edep);
myTree->SetBranchAddress("EPart", &e);
myTree->SetBranchAddress("LPart", &l);
myTree->SetBranchAddress("ProcessPart", &process);

int Events = myTree->GetEntries();
double y;
double actualenergy=0;
double emax;
int tot=0, con=0, com=0, pho=0, ray=0;
int proba;
int event=1000000;
float factor=M/(thinkness*d*Na*event*1e-24);
int processmax=5;

myTree->GetEvent(Events-1);
emax=e->at(0)*1000+1;



TH2F *h2 = new TH2F("h2","test",processmax-1,0,processmax,emax,0,emax);

for (int i=0; i<= Events; i++)
{
		myTree->GetEvent(i);
    h2->Fill(process, e->at(0)*1000);
}

for (int i=0; i<=emax;i++)
{
  int probatotal=0;
  for (int j=0;j<=processmax;j++)
  {
    proba=h2->GetBinContent(j, i);
    if (proba != 0)
    {
      probatotal+=proba;
      if (j == processmax-1)
      {
        //cout<<"energy="<<i<<endl;
        y=probatotal*factor;
        //cout<<"sectioneff="<<y<<endl;
        simutotal->SetPoint(tot, i, y);
  		  simutotal->SetPointError(tot, 0, factor*sqrt(probatotal));
  		  tot++;
      }
      if (j == 1)
      {
        y=proba*factor;
        simuconv->SetPoint(con, i, y);
    		simuconv->SetPointError(con, 0, factor*sqrt(proba));
    		con++;
      }

      else if (j == 2)
      {
        y=proba*factor;
        simuphot->SetPoint(pho, i, y);
        simuphot->SetPointError(pho, 0, factor*sqrt(proba));
        pho++;
      }

      else if (j == 3)
      {
        y=proba*factor;
        simucompt->SetPoint(com, i, y);
    		simucompt->SetPointError(com, 0, factor*sqrt(proba));
    		com++;
      }

      else if (j == 4)
      {
        y=proba*factor;
        simurayl->SetPoint(ray, i, y);
    		simurayl->SetPointError(ray, 0, factor*sqrt(proba));
    		ray++;
      }

    }


  }
}





////////////

ifstream file("data_gamma.csv");
const int n=57;
double E[n], RAYL[n], COMPT[n], PHOT[n], CONVN[n], CONVE[n], TOTAL[n], CONV[n];

for (int i=0; i<n; i++)
    {
      file >> E[i] >> RAYL[i] >> COMPT[i] >> PHOT[i] >> CONVN[i] >> CONVE[i] >> TOTAL[i];
    }
file.close();

for (int i=0; i<n; i++)
{
  E[i]=E[i]*1000;
}

//////////////
TCanvas *c1 = new TCanvas("c1", "Gamma", 20,20,1500,500);
c1->Divide(3,2);

//Total
TGraph* graphtotal = new TGraph(n, E, TOTAL);
c1->cd(1);
gPad->SetLogx();
gPad->SetLogy();
graphtotal->Draw("al");
simutotal->Draw("*");
graphtotal->SetLineColor(kRed);
graphtotal->SetTitle("Total");
graphtotal->GetXaxis()->SetTitle("Energy (keV)");
graphtotal->GetYaxis()->SetTitle("Cross Section (barn)");

//Rayleigh effect
TGraph* graphrayl = new TGraph(n, E, RAYL);
c1->cd(2);
gPad->SetLogx();
gPad->SetLogy();
graphrayl->Draw("al");
simurayl->Draw("*same");
graphrayl->SetLineColor(kRed);
graphrayl->SetTitle("Rayleigh effect");
graphtotal->GetXaxis()->SetTitle("Energy (keV)");
graphtotal->GetYaxis()->SetTitle("Cross Section (barn)");


//Compton effect
TGraph* graphcompt = new TGraph(n, E, COMPT);
c1->cd(3);
gPad->SetLogx();
gPad->SetLogy();
graphcompt->Draw("al");
simucompt->Draw("*same");
graphcompt->SetLineColor(kRed);
graphcompt->SetTitle("Compton Effect");
graphtotal->GetXaxis()->SetTitle("Energy (keV)");
graphtotal->GetYaxis()->SetTitle("Cross Section (barn)");


//Photoelectric
TGraph* graphphot = new TGraph(n, E, PHOT);
c1->cd(4);
gPad->SetLogx();
gPad->SetLogy();
graphphot->Draw("al");
simuphot->Draw("*same");
graphphot->SetLineColor(kRed);
graphphot->SetTitle("Photoelectric");
graphphot->GetXaxis()->SetTitle("Energy (keV)");
graphphot->GetYaxis()->SetTitle("Cross Section (barn)");

for (int i=0; i<=n; i++)
{
CONV[i]=CONVN[i]+CONVE[i];
}

//Conversion interne nucléaire
TGraph* graphconvn = new TGraph(n, E, CONV);
c1->cd(5);
gPad->SetLogx();
gPad->SetLogy();
graphconvn->Draw("al");
simuconv->Draw("*same");
graphconvn->SetLineColor(kRed);
graphconvn->SetTitle("Conversion Interne");
graphtotal->GetXaxis()->SetTitle("Energy (keV)");
graphtotal->GetYaxis()->SetTitle("Cross Section (barn)");

}
