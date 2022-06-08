#include "plot_func.C"


void plot_proton_cut()
{
TCanvas *c1 = new TCanvas("c1", "Proton", 20,20,1500,500);
c1->cd(1);
TGraph* graphstopd = graphdatastop("data_pstar_stop.csv");
graphstopd->Draw("al");
graphstopd->SetLineColor(kRed);
gPad->SetLogx();
gPad->SetLogy();
graphstopd->SetTitle("Stopping Power ; Energy (keV); Stopping Power (keV cm2/g)");


TGraphErrors* graphstops1 = graphsimustop("data_10um_w.root");
graphstops1->Draw("same");
graphstops1->SetLineColor(kBlack);
TGraphErrors* graphstops2 = graphsimustop("data_10um_wo.root");
graphstops2->Draw("same");
graphstops2->SetLineColor(kBlue);


auto legend1 = new TLegend(0.7,0.7,0.9,0.9);
legend1->AddEntry(graphstopd, "PSTAR data");
legend1->AddEntry(graphstops1, "opt4_w_cut_10um");
legend1->AddEntry(graphstops2, "opt4_w0_cut_10um");
legend1->Draw();

////////
TCanvas *c2 = new TCanvas("c2", "Proton", 20,20,1500,500);
c2->cd(1);
TGraph* graphlengthd = graphdatalength("data_pstar_length.csv");
graphlengthd->Draw("al");
graphlengthd->SetLineColor(kRed);
gPad->SetLogx();
gPad->SetLogy();
graphlengthd->SetTitle("CSDA ; Energy (keV); CSDA (g/cm2)");

TGraph* graphlengths = graphsimulength("data_10um_w.root");
graphlengths->Draw("*same");


auto legend2 = new TLegend(0.7,0.7,0.9,0.9);
legend2->AddEntry(graphlengthd, "PSTAR data");
legend2->AddEntry(graphlengths, "opt4_w_cut_10um");
legend2->Draw();

/////
TCanvas *c3 = new TCanvas("c3", "Proton", 20,20,1500,500);
c3->cd(1);
vector <const char*> file;


file.push_back("data_10.root");
file.push_back("data_30.root");
file.push_back("data_100.root");
file.push_back("data_300.root");
file.push_back("data_1000.root");
file.push_back("data_3000.root");
// file.push_back("data_10000.root");
// file.push_back("data_30000.root");


auto graphconvergence = new TGraphErrors();
auto redcurve = new TGraph();


double pt;
double std;
int nb;
int count=0;

for (int i=0;i<file.size();i++)
{
  auto [pt, std, nb] = convergepoint(file.at(i),"data_pstar_stop.csv");
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
