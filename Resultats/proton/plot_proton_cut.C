#include "plot_func.C"


void plot_proton_cut()
{
TCanvas *c1 = new TCanvas("c1", "Part", 20,20,1500,500);
c1->Divide(2,1);
c1->cd(1);
TGraph* graphstopd = graphdatastop("data_pstar_stop.csv");
graphstopd->Draw("al");
graphstopd->SetLineColor(kRed);
gPad->SetLogx();
gPad->SetLogy();
graphstopd->SetTitle("Stoppping Power ; Energy (keV); Stopping Power (keV cm2/g)");


TGraph* graphstops = graphsimustop("data_001um.root");
graphstops->Draw("same");
graphstops->SetLineColor(kBlack);
TGraph* graphstops1 = graphsimustop("data_1mm.root");
graphstops1->Draw("same");
graphstops->SetLineColor(kGreen);
TGraph* graphstops2 = graphsimustop("data_1cm.root");
graphstops2->Draw("same");
graphstops2->SetLineColor(kBlue);
TGraph* graphstops3 = graphsimustop("data_01mm.root");
graphstops3->Draw("same");
graphstops3->SetLineColor(kPink);
TGraph* graphstops4 = graphsimustop("data_001mm.root");
graphstops4->Draw("same");
graphstops4->SetLineColor(kOrange);
TGraph* graphstops5 = graphsimustop("data_1um.root");
graphstops5->Draw("same");
graphstops5->SetLineColor(kMagenta);

auto legend1 = new TLegend(0.7,0.7,0.9,0.9);
legend1->AddEntry(graphstopd, "PSTAR data");
legend1->AddEntry(graphstops2, "1cm");
legend1->AddEntry(graphstops1, "1mm");
legend1->AddEntry(graphstops3, "100um");
legend1->AddEntry(graphstops4, "10um");
legend1->AddEntry(graphstops5, "1um");
legend1->AddEntry(graphstops, "0.01um");
legend1->Draw();

////////
c1->cd(2);
TGraph* graphlengthd = graphdatalength("data_pstar_length.csv");
graphlengthd->Draw("al");
graphlengthd->SetLineColor(kRed);
gPad->SetLogx();
gPad->SetLogy();
graphlengthd->SetTitle("CSDA ; Energy (keV); CSDA (g/cm2)");

TGraph* graphlengths = graphsimulength("data_001um.root");
graphlengths->Draw("*same");
TGraph* graphlengths1 = graphsimulength("data_1cm.root");
graphlengths1->Draw("*same");

auto legend2 = new TLegend(0.7,0.7,0.9,0.9);
legend2->AddEntry(graphlengthd, "PSTAR data");
legend2->AddEntry(graphlengths, "0.01um");
legend2->AddEntry(graphlengths1, "1cm");
legend2->Draw();

}
