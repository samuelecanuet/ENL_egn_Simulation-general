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
vector <float> *e;
vector <float> *l;
vector <std::string> *process;

myTree->SetBranchAddress("EdepPart", &edep);
myTree->SetBranchAddress("EPart", &e);
myTree->SetBranchAddress("LPart", &l);
myTree->SetBranchAddress("ProcessPart", &process);

int Events = myTree->GetEntries();

float energy;
string processname;
double y;

float actualenergy=0;  //juste pour comparer la premiere energie
int count_total=0, count_compt=0, count_rayl=0, count_conv=0, count_phot=0, count_event=0; //compte le nb de "process" pour une energie
vector <int> count_list_total;
vector <int> count_list_conv, count_list_rayl, count_list_phot, count_list_compt;// garde le nb d'energie différente dans chaque élément
vector <float> energy_list;
energy_list.push_back(0);
vector <int> event_list;


for (int i=0; i<= Events; i++)
{
			myTree->GetEvent(i);

			processname=process->at(0);


      if (e->at(0) == actualenergy)
      { count_event++;
        if (processname == "conv" || processname == "phot" || processname == "compt" || processname == "Rayl")
        {count_total++;}

        if (processname == "conv")
        {count_conv++;}
        if (processname == "phot")
        {count_phot++;}
        if (processname == "compt")
        {count_compt++;}
        if (processname == "Rayl")
        {count_rayl++;}
      }
      if (e->at(0) != actualenergy || i == Events)
      {
        count_list_total.push_back(count_total);
        count_list_phot.push_back(count_phot);
        count_list_conv.push_back(count_conv);
        count_list_compt.push_back(count_compt);
        count_list_rayl.push_back(count_rayl);
        energy_list.push_back(e->at(0));
        event_list.push_back(count_event);
        actualenergy=e->at(0);
        count_total=0;
        count_phot=0;
        count_conv=0;
        count_compt=0;
        count_rayl=0;
        count_event=0;
      }

}


int tot=0, con=0, com=0, pho=0, ray=0;

float factor;

for (int j=1; j<energy_list.size(); j++)
{
		energy=energy_list[j];
		factor=M/(thinkness*d*Na*event_list[j]*1e-24);

		y=count_list_total[j]*factor;
    simutotal->SetPoint(tot, energy, y);
		simutotal->SetPointError(tot, 0, factor*sqrt(count_list_total[j]));
		tot++;

    y=count_list_phot[j]*factor;
    simuphot->SetPoint(pho, energy, y);
		simuphot->SetPointError(pho, 0, factor*sqrt(count_list_phot[j]));
    pho++;

    y=count_list_conv[j]*factor;
    simuconv->SetPoint(con, energy, y);
		simuconv->SetPointError(con, 0, factor*sqrt(count_list_conv[j]));
		con++;

    y=count_list_compt[j]*factor;
    simucompt->SetPoint(com, energy, y);
		simucompt->SetPointError(com, 0, y*sqrt(count_list_compt[j]));
		com++;

    y=count_list_rayl[j]*factor;
    simurayl->SetPoint(ray, energy, y);
		simurayl->SetPointError(ray, 0, factor*sqrt(count_list_rayl[j]));
		ray++;

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


//////////////
TCanvas *c1 = new TCanvas("c1", "Gamma", 20,20,1500,500);
c1->Divide(3,2);

//Total
TGraph* graphtotal = new TGraph(n, E, TOTAL);
c1->cd(1);
gPad->SetLogx();
gPad->SetLogy();
graphtotal->Draw("al");
simutotal->Draw("*same");
graphtotal->SetLineColor(kRed);
graphtotal->SetTitle("Total");
graphtotal->GetXaxis()->SetTitle("Energy (MeV)");
graphtotal->GetYaxis()->SetTitle("Total Attenuation (g/cm2)");

//Rayleigh effect
TGraph* graphrayl = new TGraph(n, E, RAYL);
c1->cd(2);
gPad->SetLogx();
gPad->SetLogy();
graphrayl->Draw("al");
simurayl->Draw("*same");
graphrayl->SetLineColor(kRed);
graphrayl->SetTitle("Rayleigh effect");


//Compton effect
TGraph* graphcompt = new TGraph(n, E, COMPT);
c1->cd(3);
gPad->SetLogx();
gPad->SetLogy();
graphcompt->Draw("al");
simucompt->Draw("*same");
graphcompt->SetLineColor(kRed);
graphcompt->SetTitle("Compton Effect");


//Photoelectric
TGraph* graphphot = new TGraph(n, E, PHOT);
c1->cd(4);
gPad->SetLogx();
gPad->SetLogy();
graphphot->Draw("al");
simuphot->Draw("*same");
graphphot->SetLineColor(kRed);
graphphot->SetTitle("Photoelectric");

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


energy_list.clear();
count_list_total.clear();
count_list_compt.clear();
count_list_phot.clear();
count_list_rayl.clear();
count_list_conv.clear();

}
