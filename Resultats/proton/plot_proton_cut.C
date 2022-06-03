#include "plot_func.C"


void plot_proton_cut()
{
TCanvas *c1 = new TCanvas("c1", "Proton", 20,20,1500,500);
c1->Divide(2,1);
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
c1->cd(2);
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

}
