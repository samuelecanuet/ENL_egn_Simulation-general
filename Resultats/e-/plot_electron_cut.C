#include "plot_func.C"


void plot_electron_cut()
{
TCanvas *c1 = new TCanvas("c1", "Electron", 20,20,1500,500);
c1->cd(1);

TGraph* graphstopd = graphdatastop("data_estar_stop.csv");
graphstopd->Draw("al");
graphstopd->SetLineColor(kRed);
TGraph* graphstops1 = graphsimustop("data_1um.root");
graphstops1->Draw("same");
graphstops1->SetLineColor(kBlue);
TGraph* graphstops2 = graphsimustop("data_50mm.root");
graphstops2->Draw("same");
graphstops2->SetLineColor(kGreen);

gPad->SetLogx();
gPad->SetLogy();
graphstopd->SetTitle("Stoppping Power ; Energy (keV); Stopping Power (keV cm2/g)");


auto legend1 = new TLegend(0.7,0.7,0.9,0.9);
legend1->AddEntry(graphstopd, "ESTAR data");
legend1->AddEntry(graphstops1, "cut=1um");
legend1->AddEntry(graphstops2, "cut=50mm");

legend1->Draw();


////////
TCanvas *c2 = new TCanvas("c2", "Electron", 20,20,1500,500);
c2->cd(1);
TGraph* graphlengthd = graphdatalength("data_estar_length.csv");
graphlengthd->Draw("al");
graphlengthd->SetLineColor(kRed);
gPad->SetLogx();
gPad->SetLogy();
graphlengthd->SetTitle("CSDA ; Energy (keV); CSDA (g/cm2)");

TGraph* graphlengths = graphsimulength("data_50mm.root");
graphlengths->Draw("*same");

auto legend2 = new TLegend(0.7,0.7,0.9,0.9);
legend2->AddEntry(graphlengthd, "ESTAR data");
legend2->AddEntry(graphlengths, "10um");
legend2->Draw();

////////////
TCanvas *c3 = new TCanvas("c3", "Electron", 20,20,1500,500);
c3->cd(1);
vector <const char*> file;

file.push_back("data_50mm_10.root");
file.push_back("data_50mm_30.root");
file.push_back("data_50mm_100.root");
file.push_back("data_50mm_300.root");
file.push_back("data_50mm_1000.root");
file.push_back("data_50mm_3000.root");
file.push_back("data_50mm_10000.root");
file.push_back("data_50mm_30000.root");


auto graphconvergence = new TGraphErrors();
auto redcurve = new TGraph();


double pt;
double std;
int nb;
int count=0;

for (int i=0;i<file.size();i++)
{
  auto [pt, std, nb] = convergepoint(file.at(i),"data_estar_stop.csv");
  graphconvergence->SetPoint(count, nb, pt);
  cout<<nb<<"      "<<pt<<endl;
  graphconvergence->SetPointError(count, 0, std);
  count++;
}

redcurve->SetPoint(0, 0, 1);
redcurve->SetPoint(1, 10000000000, 1);

gPad->SetLogx();
graphconvergence->Draw("a*");
redcurve->Draw("same");
redcurve->SetLineColor(kRed);
graphconvergence->SetTitle("Convergence ; Nombre d'evenement; Ratio stopping power");
}
