#include "plot_func.C"


void plot_proton()
{
TCanvas *c1 = new TCanvas("c1", "Proton", 20,20,1500,500);
c1->Divide(2,1);
c1->cd(1);
TGraph* graphstopd = graphdatastop("data_pstar_stop.csv");
graphstopd->Draw("al");
graphstopd->SetLineColor(kRed);
gPad->SetLogx();
gPad->SetLogy();
graphstopd->SetTitle("Stoppping Power ; Energy (keV); Stopping Power (keV cm2/g)");


TGraph* graphstops = graphsimustop("data.root");
graphstops->Draw("*same");
graphstops->SetLineColor(kBlack);


auto legend1 = new TLegend(0.7,0.7,0.9,0.9);
legend1->AddEntry(graphstopd, "PSTAR data");
legend1->AddEntry(graphstops, "opt3, cut=1nm");
legend1->Draw();

////////
c1->cd(2);
TGraph* graphlengthd = graphdatalength("data_pstar_length.csv");
graphlengthd->Draw("al");
graphlengthd->SetLineColor(kRed);
gPad->SetLogx();
gPad->SetLogy();
graphlengthd->SetTitle("CSDA ; Energy (keV); CSDA (g/cm2)");

TGraph* graphlengths = graphsimulength("data.root");
graphlengths->Draw("*same");

auto legend2 = new TLegend(0.7,0.7,0.9,0.9);
legend2->AddEntry(graphlengthd, "PSTAR data");
legend2->AddEntry(graphlengths, "1nm");

legend2->Draw();

}
