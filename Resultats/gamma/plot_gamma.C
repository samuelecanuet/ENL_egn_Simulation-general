{
gROOT->Reset();
gStyle->SetPalette(1);

TFile* myFile = new TFile("data.root");
TTree* myTree = (TTree*) myFile->Get("theRunTree");
auto tprof = new TProfile("tprof", "Stopping Power", 10000000, 0.005, 10000, 0.01, 10);
auto tconv = new TProfile("tconv", "Stopping Power", 10000000, 0.005, 10000, 0.01, 10);
auto tphot = new TProfile("tphot", "Stopping Power", 1000000, 0.005, 10000, 0.01, 10);
auto tcompt = new TProfile("tcompt", "Stopping Power", 1000000, 0.005, 10000, 0.01, 10);
auto trayl = new TProfile("trayl", "Stopping Power", 100000, 0.005, 10000, 0.01, 10);




vector <float> *edep;
vector <float> *e;
vector <float> *l;
vector <std::string> *process;

float energy;
string processname;
myTree->SetBranchAddress("EdepPart", &edep);
myTree->SetBranchAddress("EPart", &e);
myTree->SetBranchAddress("LPart", &l);
myTree->SetBranchAddress("ProcessPart", &process);

int Events = myTree->GetEntries();

for (int i=0; i< Events; i++)
{
	myTree->GetEvent(i);

	for (int j=0; j<e->size();j++)
	{
		energy=e->at(j);
		processname=process->at(j);
		//total
    tprof->Fill(energy, 1/(l->at(j)*2.329002));
		//Convertion Interne
		if (processname == "conv")
			tconv->Fill(energy, 1/(l->at(j)*2.329002));

		else if (processname == "compt")
			tcompt->Fill(energy, 1/(l->at(j)*2.329002));

		else if (processname == "phot")
			tphot->Fill(energy, 1/(l->at(j)*2.329002));

		else if (processname == "Rayl")
			trayl->Fill(energy, 1/(l->at(j)*2.329002));

		else
			cout<<processname<<endl;
	}
}




////////////

ifstream file("data_gamma.csv");
const int n=81;
//float E[n], RAYL[n], COMPT[n], PHOT[n], CONV[2*n], TOTAL[n];
float E[n], N[n];
for (int i=0; i<n; i++)
    {
      file >> E[i] >> N[i];// >> COMPT[i] >> PHOT[i] >> CONV[2*i] >> CONV[2*i+1] >> TOTAL[i];
    }
file.close();




//////////////
TCanvas *c1 = new TCanvas("c1", "Gamma", 20,20,1500,500);
c1->Divide(3,2);

//Total
TGraph* graphtotal = new TGraph(n, E, TOTAL);
c1->cd(1);
gPad->SetLogx();
gPad->SetLogy();
tprof->Draw("lp");
graphtotal->Draw("same");
graphtotal->SetLineColor(kRed);

tprof->SetLineColor(kBlack);
tprof->GetXaxis()->SetTitle("Energy (MeV)");
tprof->GetYaxis()->SetTitle("Total Attenuation (g/cm2)");


//Rayleigh effect
TGraph* graphrayl = new TGraph(n, E, RAYL);
c1->cd(2);
gPad->SetLogx();
gPad->SetLogy();
graphrayl->Draw();
graphrayl->SetLineColor(kRed);
trayl->Draw("same");
trayl->SetLineColor(kBlack);
trayl->GetXaxis()->SetTitle("Energy (MeV)");
trayl->GetYaxis()->SetTitle("(g/cm2)");

//Compton effect
TGraph* graphcompt = new TGraph(n, E, N);
c1->cd(3);
gPad->SetLogx();
gPad->SetLogy();
graphcompt->Draw();
graphcompt->SetLineColor(kRed);
tcompt->Draw("same");
tcompt->SetLineColor(kBlack);
tcompt->GetXaxis()->SetTitle("Energy (MeV)");
tcompt->GetYaxis()->SetTitle("(g/cm2)");

//Photoelectric
TGraph* graphphot = new TGraph(n, E, PHOT);
c1->cd(4);
gPad->SetLogx();
gPad->SetLogy();
graphphot->Draw();
graphphot->SetLineColor(kRed);
tphot->Draw("same");
tphot->SetLineColor(kBlack);
tphot->GetXaxis()->SetTitle("Energy (MeV)");
tphot->GetYaxis()->SetTitle("(g/cm2)");


//Conversion interne
TGraph* graphconv = new TGraph(2*n, E, CONV);
c1->cd(5);
gPad->SetLogx();
gPad->SetLogy();
graphconv->Draw();
graphconv->SetLineColor(kRed);
tconv->Draw("same");
tconv->SetLineColor(kBlack);
tconv->GetXaxis()->SetTitle("Energy (MeV)");
tconv->GetYaxis()->SetTitle("(g/cm2)");









}
