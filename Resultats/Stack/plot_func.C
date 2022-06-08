#include <math.h>

TGraph* graphdatastop(const char* filename)
{
  ifstream file(filename);
  const int n=115;
  float E[n], N[n];

  for (int i=0; i<n; i++)
      {
        file >> E[i] >> N[i];
      }
  file.close();

  for (int i=0;i<n;i++)
  {
    E[i]=E[i]*1000;
    N[i]=N[i]*1000;

  }

  TGraph* graph = new TGraph(n, E, N);
  return graph;
}

TGraph* graphdatalength(const char* filename)
{
  ifstream file(filename);
  const int n=100;
  float E[n], N[n];

  for (int i=0; i<n; i++)
      {
        file >> E[i] >> N[i];
      }
  file.close();

  for (int i=0;i<n;i++)
  {
    E[i]=E[i]*1000;
  }

  TGraph* graph = new TGraph(n, E, N);
  return graph;
}

TGraphErrors* graphsimustop(const char* filename)
{
  TFile* myFile = new TFile(filename);
  TTree* myTree = (TTree*) myFile->Get("theRunTree");
  TGraphErrors* tprof = new TGraphErrors();

  vector <float> *edep=0;
  vector <float> *e=0;
  vector <float> *l=0;

  myTree->SetBranchAddress("EdepPart", &edep);
  myTree->SetBranchAddress("EPart", &e);
  myTree->SetBranchAddress("LPart", &l);
  int Events = myTree->GetEntries();
  int count=0;
  double initialenergy=0;
  int county=0;
  double ytotal=0;
  int countt=0;
  double std=0;
  vector <double> y;
  double sum=0;

  for (int i=0; i< Events; i++)
  {
    myTree->GetEvent(i);
    if (i==0){initialenergy=e->at(0);}

    if (0.9*round(initialenergy)>round(e->at(0)) || 1.1*round(initialenergy)<round(e->at(0)) || i==Events)
    {
      myTree->GetEvent(i-1);
      tprof->SetPoint(count, e->at(0), ytotal/(county*2.329002));

      sum=0;
      int len=y.size();
      for (int j=0; j<=len; j++)
      {
        sum+=pow(y[j]/2.329002, 2)-pow(ytotal/(county*2.329002),2);
      }
      std=sqrt(sum/county);
      tprof->SetPointError(count, 0, std);
      ytotal=0;
      y.clear();
      county=1;
      count++;
      myTree->GetEvent(i);
      initialenergy=e->at(0);
    }

    else
    {
      double length=0;
      double ee=0;
      length=l->at(0);
      ee=edep->at(0);
      y.push_back(ee/(length));
      ytotal+=ee/(length);
      county++;
    }
  }
  return tprof;
}

TGraph* graphsimulength(const char* filename)
{
  TFile* myFile = new TFile(filename);
  TTree* myTree = (TTree*) myFile->Get("theRunTree");
  TGraph* tprof = new TGraph();
  //myTree->Scan();
  vector <float> *edep=0;
  vector <float> *e=0;
  vector <float> *l=0;

  myTree->SetBranchAddress("EdepPart", &edep);
  myTree->SetBranchAddress("EPart", &e);
  myTree->SetBranchAddress("LPart", &l);

  int Events = myTree->GetEntries();
  int count=0;
  double initialenergy=0;
  int county=0;
  double y=0;
  double length=0;


  for (int i=0; i< Events; i++)
  {
    myTree->GetEvent(i);

    if (i==0){initialenergy=e->at(0);}

    if (0.9*round(initialenergy)>round(e->at(0)) || 1.1*round(initialenergy)<round(e->at(0)))

    {
      myTree->GetEvent(i-1);
      tprof->SetPoint(count, e->at(0), y*2.329002/county);
      county=1;
      y=0;
      count++;
      myTree->GetEvent(i);
      initialenergy=e->at(0);
    }

    else
    {
      for (int j=0; j<e->size(); j++)
       {
         length+=l->at(j);
       }

      y+=length;
      length=0;
      county++;
    }
  }


  return tprof;
}

TProfile* graphsimubragg(const char* filename, float energy, int bin)
{

  TFile* myFile = new TFile(filename);
  TTree* myTree = (TTree*) myFile->Get("theRunTree");

  vector <float> *edep=0;
  vector <float> *e=0;
  vector <float> *l=0;
  vector <double> *z=0;

  myTree->SetBranchAddress("EdepPart", &edep);
  myTree->SetBranchAddress("EPart", &e);
  myTree->SetBranchAddress("LPart", &l);
  myTree->SetBranchAddress("z", &z);
  int Events = myTree->GetEntries();
  double ytotal=0;
  bool valid=false;

  auto tprof = new TProfile("tprof", "Bragg pic of proton in Si", bin, 0, 2.5);
  for (int i=0; i<=Events; i++)
  {
    myTree->GetEvent(i);
    if (energy==e->at(0))
    {
      valid=true;
    }
  }
  if (valid==true)
  {
    for (int i=0; i<=Events; i++)
    {
      myTree->GetEvent(i);
      if (e->at(0)==energy)
      {
        double ee=0;
        double zpos=0;
        double length=0;
        for (int j=0; j<z->size()-1; j++)
        {
          length=l->at(j);
          ee=edep->at(j);
          zpos=z->at(j);
          ytotal=ee*0.001/length;
          tprof->Fill(zpos, ytotal/(2.3*1000));
        }
      }
    }

  }
  else
  {
    cout<<"ENERGY NOT FOUND"<<endl;
  }
  return tprof;
}

tuple<double, double, int> convergepoint(const char* filename, const char* datafilename)
{
  TFile* myFile = new TFile(filename);
  TTree* myTree = (TTree*) myFile->Get("theRunTree");

  vector <float> *edep=0;
  vector <float> *e=0;
  vector <float> *l=0;

  myTree->SetBranchAddress("EdepPart", &edep);
  myTree->SetBranchAddress("EPart", &e);
  myTree->SetBranchAddress("LPart", &l);

  int Events = myTree->GetEntries();
  int count=0;
  double initialenergy=0;
  int county=0;
  double ytotal=0;
  int countt=0;
  double std=0;
  vector <double> y;
  double sum=0;
  vector <double> ylist, elist, stdlist;

  for (int i=0; i< Events; i++)
  {
    myTree->GetEvent(i);
    if (i==0){initialenergy=e->at(0);}

    if (0.9*round(initialenergy)>round(e->at(0)) || 1.1*round(initialenergy)<round(e->at(0)) || i==Events)
    {
      myTree->GetEvent(i-1);
      ylist.push_back(ytotal/(county*2.329002));
      elist.push_back(e->at(0));
      sum=0;
      int len=y.size();
      for (int j=0; j<=len; j++)
      {
        sum+=pow(y[j]/2.329002, 2)-pow(ytotal/(county*2.329002),2);
      }
      std=sqrt(sum/county);
      stdlist.push_back(std);
      ytotal=0;
      y.clear();
      county=1;
      myTree->GetEvent(i);
      initialenergy=e->at(0);
    }

    else
    {
      double length=0;
      double ee=0;
      length=l->at(0);
      ee=edep->at(0);
      y.push_back(ee/(length));
      ytotal+=ee/(length);
      county++;
    }
  }

  ifstream file(datafilename);
  const int n=115;
  float E[n], N[n];

  for (int i=0; i<n; i++)
      {
        file >> E[i] >> N[i];
      }
  file.close();

  for (int i=0;i<n;i++)
  {
    E[i]=E[i]*1000;
    N[i]=N[i]*1000;

  }

  double sum1=0, sumstd=0, std1;
  vector <double> finallist;

  for (int i=0;i<elist.size();i++)
  {
    for (int j=0;j<n;j++)
    {
      if (elist.at(i)==E[j])
      {
        finallist.push_back(ylist.at(i)/N[j]);
      }
    }
  }
  for (int j=0; j<finallist.size(); j++)
  {
    sum1+=finallist.at(j);
  }
  for (int j=0; j<finallist.size(); j++)
  {
    sumstd+=pow(finallist.at(j), 2)-pow(sum1/finallist.size(),2);
  }
  std1=sqrt(sumstd/elist.size());
return {sum1/finallist.size(), std1, Events/(finallist.size()+1)};

}
