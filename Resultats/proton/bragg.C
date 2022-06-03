#include "plot_func.C"


void bragg()
{
  TCanvas *c1 = new TCanvas("c1", "Proton", 20,20,1500,500);


  TProfile* graphstops0 = graphsimubragg("data.root", 1024, 80000);
  graphstops0->Draw("HIST L");
  graphstops0->SetLineColor(kGreen);
  TProfile* graphstops1 = graphsimubragg("data.root", 4096, 3000);
  graphstops1->Draw("HIST L same");
  graphstops1->SetLineColor(kBlue);
  TProfile* graphstops2 = graphsimubragg("data.root", 8192, 2000);
  graphstops->Draw("HIST L same");
  graphstops->SetLineColor(kBlack);
  TProfile* graphstops3 = graphsimubragg("data.root", 32768, 1000);
  graphstops2->Draw("HIST L same");
  graphstops2->SetLineColor(kRed);
  TProfile* graphstops4 = graphsimubragg("data.root", 65536, 500);
  graphstops3->Draw("HIST L same");
  graphstops3->SetLineColor(kMagenta);

  gPad->SetLogx();

  graphstops0->SetTitle("Bragg pic in Si ; Depth (cm); dE/dx (MeV cm2/mg)");


  auto legend = new TLegend(0.7,0.7,0.9,0.9);
  legend->AddEntry(graphstops0, "1024 keV");
  legend->AddEntry(graphstops1, "4096 keV");
  legend->AddEntry(graphstops2, "8192 keV");
  legend->AddEntry(graphstops3, "32768 keV");
  legend->AddEntry(graphstops4, "65536 keV");
  legend->Draw();
}
