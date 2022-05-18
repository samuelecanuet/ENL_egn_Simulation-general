{
gROOT->Reset();
gStyle->SetPalette(1);
//Constantes
double M=28.08550;
double Na=6.0221408e+23;
double d=2.329002;

const float thinkness=100*10e-6;

TFile* myFile = new TFile("data.root");
TTree* myTree = (TTree*) myFile->Get("theRunTree");
TGraph* simutotal = new TGraph();
TGraph* simuconv = new TGraph();
TGraph* simucompt = new TGraph();
TGraph* simuphot = new TGraph();
TGraph* simurayl = new TGraph();


vector <float> *edep;
vector <float> *e;
vector <float> *l;
vector <std::string> *process;

float energy;
string processname;
double y;


myTree->SetBranchAddress("EdepPart", &edep);
myTree->SetBranchAddress("EPart", &e);
myTree->SetBranchAddress("LPart", &l);
myTree->SetBranchAddress("ProcessPart", &process);

int Events = myTree->GetEntries();


float initialenergy=0.;  //juste pour comparer la premiere energie
vector <int> count;    // garde le nb de "process" pour une energie differente dans chaque element

int count_total=0, count_conv=0, count_phot=0, count_compt=0, count_rayl=0;     //compte le nb de "process" pour une energie
vector <int> energy_total, energy_phot, energy_rayl, energy_compt, energy_conv; // garde le nb d'nergie différente dans chaque élément

vector <float> energylist;

for (int i=0; i< Events; i++)
{
			myTree->GetEvent(i);
			processname=process->at(0);
			if (e->at(0) != initialenergy)
				{
        	count.push_back(count_total);
					count.push_back(count_phot);
					count.push_back(count_conv);
					count.push_back(count_compt);
					count.push_back(count_rayl);
					energylist.push_back(e->at(0));
					initialenergy=e->at(0);

					if (processname != "Transportation")
		    		{
							count_total=0;
						}
					else if (e->at(0)==initialenergy)
						{count_total++;}


					if (processname == "conv")
						{
				  		count_conv=0;
	      		}
	      	else if (e->at(0)==initialenergy)
          	{count_conv++;}


					if (processname == "compt")
						{
					  	count_compt=0;
		      	}
	          {count_compt++;}


					if (processname == "phot")
						{
						  count_phot=0;
			      }
			    else if (e->at(0)==initialenergy)
		        {count_phot++;}

					if (processname == "rayl")
						{
							count_rayl=0;
						}
					else if (e->at(0)==initialenergy)
							{count_rayl++;}

		}
}


int tot=0;
int con=0;
int com=0;
int pho=0;
int ray=0;

for (int j=0; j<=energy_total.size(); j++)
{
		energy=energy_total[j];
		y=M*count[j+1]/(thinkness*d*Na*Events*10e-24);
		//total
    simutotal->SetPoint(tot, energy, y);
		tot++;
}

cout<<energy<<endl;
cout<<y<<endl;

for (int j=1; j<energy_phot.size(); j++)
{
		energy=energy_phot[j];
		y=M*count[j+5]/(thinkness*d*Na*10e-24*Events);
		//total
    simuphot->SetPoint(pho, energy, y);
		pho++;
}

for (int j=2; j<energy_conv.size(); j++)
{
		energy=energy_conv[j];
		y=M*count[j+5]/(thinkness*d*Na*10e-24*Events);
		//total
    simucon->SetPoint(con, energy, y);
		con++;
}

for (int j=3; j<energy_compt.size(); j++)
{
		energy=energy_compt[j];
		y=M*count[j+5]/(thinkness*d*Na*10e-24*Events);
		//total
    simucompt->SetPoint(com, energy, y);
		com++;
}

for (int j=4; j<energy_rayl.size(); j++)
{
		energy=energy_ray[j];
		y=M*count[j+5]/(thinkness*d*Na*10e-24*Events);
		//total
    simucompt->SetPoint(ray, energy, y);
		ray++;
}

////////////

ifstream file("data_gamma.csv");
const int n=57;
double E[n], RAYL[n], COMPT[n], PHOT[n], CONVN[n], CONVE[n], TOTAL[n];

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
//graphtotal->Draw("*al");
simutotal->Draw("*al");
graphtotal->SetLineColor(kRed);
graphtotal->SetTitle("Total");
graphtotal->GetXaxis()->SetTitle("Energy (MeV)");
graphtotal->GetYaxis()->SetTitle("Total Attenuation (g/cm2)");

//Rayleigh effect
TGraph* graphrayl = new TGraph(n, E, RAYL);
c1->cd(2);
gPad->SetLogx();
gPad->SetLogy();
graphrayl->Draw("*al");
simurayl->Draw("same");
graphrayl->SetLineColor(kRed);
graphrayl->SetTitle("Rayleigh effect");


//Compton effect
TGraph* graphcompt = new TGraph(n, E, COMPT);
c1->cd(3);
gPad->SetLogx();
gPad->SetLogy();
graphcompt->Draw("*al");
simucompt->Draw("same");
graphcompt->SetLineColor(kRed);
graphcompt->SetTitle("Compton Effect");


//Photoelectric
TGraph* graphphot = new TGraph(n, E, PHOT);
c1->cd(4);
gPad->SetLogx();
gPad->SetLogy();
graphphot->Draw("*al");
simuphot->Draw("same");
graphphot->SetLineColor(kRed);
graphphot->SetTitle("Photoelectric");



//Conversion interne nucléaire
TGraph* graphconvn = new TGraph(n, E, CONVN);
c1->cd(5);
gPad->SetLogx();
gPad->SetLogy();
graphconvn->Draw("*al");
simuconv->Draw("same");
graphconvn->SetLineColor(kRed);
graphconvn->SetTitle("Nuclear Conversion");


//Conversion interne electronique
TGraph* graphconve = new TGraph(n, E, CONVE);
c1->cd(6);
gPad->SetLogx();
gPad->SetLogy();
graphconve->Draw("*al");
simuconv->Draw("same");
graphconve->SetLineColor(kRed);
graphconve->SetTitle("Electronic Conversion");

}
