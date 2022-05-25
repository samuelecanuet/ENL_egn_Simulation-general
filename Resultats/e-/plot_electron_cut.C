#include "plot_func.C"


void plot_electron_cut()
{
TCanvas *c1 = new TCanvas("c1", "Proton", 20,20,1500,500);
c1->Divide(2,1);
c1->cd(1);
TGraph* graphstops = graphsimustop("data_1nm.root");
graphstops->Draw("al");
graphstops->SetLineColor(kBlack);
TGraph* graphstops1 = graphsimustop("data_1mm.root");
graphstops1->Draw("same");
graphstops1->SetLineColor(kBlue);

TGraph* graphstopd = graphdatastop("data_estar_stop.csv");
graphstopd->Draw("same");
graphstopd->SetLineColor(kRed);
gPad->SetLogx();
gPad->SetLogy();
graphstopd->SetTitle("Stoppping Power ; Energy (keV); Stopping Power (keV cm2/g)");


auto legend1 = new TLegend(0.7,0.7,0.9,0.9);
legend1->AddEntry(graphstopd, "ESTAR data");
legend1->AddEntry(graphstops, "opt3, cut=1nm");
legend1->AddEntry(graphstops1, "opt3, cut=1mm");
legend1->Draw();

////////
c1->cd(2);
TGraph* graphlengthd = graphdatalength("data_estar_length.csv");
graphlengthd->Draw("al");
graphlengthd->SetLineColor(kRed);
gPad->SetLogx();
gPad->SetLogy();
graphlengthd->SetTitle("CSDA ; Energy (keV); CSDA (g/cm2)");

TGraph* graphlengths = graphsimulength("data_1nm.root");
graphlengths->Draw("*same");

auto legend2 = new TLegend(0.7,0.7,0.9,0.9);
legend2->AddEntry(graphlengthd, "ESTAR data");
legend2->AddEntry(graphlengths, "1nm");

legend2->Draw();

}
