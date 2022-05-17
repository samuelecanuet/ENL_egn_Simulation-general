{
gROOT->Reset();
gStyle->SetPalette(1);

TFile* myFile = new TFile("data.root");
TTree* myTree = (TTree*) myFile->Get("theRunTree");
auto tprof = new TProfile("tprof", "Stopping Power", 100000, 0.005, 100, 1, 1000);

vector <float> *edep;
vector <float> *e;
vector <float> *l;

myTree->SetBranchAddress("EdepPart", &edep);
myTree->SetBranchAddress("EPart", &e);
myTree->SetBranchAddress("LPart", &l);

int Events = myTree->GetEntries();

for (int i=0; i< Events; i++)
	{
	myTree->GetEvent(i);

	for (int j=0; j<edep->size();j++)
		{
		tprof->Fill(e->at(j), edep->at(j)/(l->at(j)*2.329002));

		}
	}

const int a=1500;
float El[a], Ll[a];
float eventlength;
for (int i=0; i< a; i++)
{
	myTree->GetEvent(i);
        eventlength=0;
        El[i]=e->at(0);

	for (int j=0; j<edep->size();j++)
          { eventlength+=l->at(j);}
         Ll[i]=2.329002*eventlength;
}
TGraph* graphl = new TGraph(a, El, Ll);


////////////

ifstream file("data_pstar_stop.csv");
const int n=100;
float E[n], N[n];

for (int i=0; i<n; i++)
    {
      file >> E[i] >> N[i];
    }
file.close();

TGraph* graphstop = new TGraph(n, E, N);
graphstop->SetLineColor(kRed);

////////////
ifstream fileL("data_pstar_length.csv");
const int b=100;
float E1[b], L[b];

for (int i=0; i<b; i++)
    {
      fileL >> E1[i] >> L[i];
    }
fileL.close();

TGraph* graphL = new TGraph(b, E1, L);
graphL->SetLineColor(kRed);


//////////////
TCanvas *c1 = new TCanvas("c1", "Part", 20,20,1500,500);
c1->Divide(2,1);

c1->cd(1);
tprof->Draw("lp");
gPad->SetLogx();
gPad->SetLogy();
tprof->GetXaxis()->SetTitle("Energy (MeV)");
tprof->GetYaxis()->SetTitle("Stopping Power (MeV cm2/g)");
graphstop->Draw("same");

c1->cd(2);
gPad->SetLogx();
gPad->SetLogy();
graphl->Draw("AL*");
graphl->SetTitle("CSDA ; Energy (MeV); CSDA (g/cm2)");
graphL->Draw("same");





}
