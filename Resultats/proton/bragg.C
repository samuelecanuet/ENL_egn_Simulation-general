#include "plot_func.C"


void bragg()
{
  TCanvas *c1 = new TCanvas("c1", "Proton", 20,20,1500,500);

  string filename = "data_10um_w.root";
  TProfile* graphstops0 = graphsimubragg("data_10um_w.root", 1280, 60000);
  graphstops0->Draw("HIST L");
  graphstops0->SetLineColor(kGreen);
  TProfile* graphstops1 = graphsimubragg("data_10um_w.root", 5120, 3000);
  graphstops1->Draw("HIST L same");
  graphstops1->SetLineColor(kBlue);
  TProfile* graphstops2 = graphsimubragg("data_10um_w.root", 10240, 2000);
  graphstops2->Draw("HIST L same");
  graphstops2->SetLineColor(kBlack);
  TProfile* graphstops3 = graphsimubragg("data_10um_w.root", 20480, 1000);
  graphstops3->Draw("HIST L same");
  graphstops3->SetLineColor(kRed);
  TProfile* graphstops4 = graphsimubragg("data_10um_w.root", 81920, 500);
  graphstops4->Draw("HIST L same");
  graphstops4->SetLineColor(kMagenta);

  gPad->SetLogx();

  graphstops0->SetTitle("Bragg pic in Si ; Depth (cm); dE/dx (MeV cm2/mg)");


  auto legend = new TLegend(0.7,0.7,0.9,0.9);
  legend->AddEntry(graphstops0, "1280 keV");
  legend->AddEntry(graphstops1, "5120 keV");
  legend->AddEntry(graphstops2, "10240 keV");
  legend->AddEntry(graphstops3, "20480 keV");
  legend->AddEntry(graphstops4, "81920 keV");
  legend->Draw();
}
