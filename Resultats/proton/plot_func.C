TGraph* graphdatastop(const char* filename)
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

TGraph* graphsimustop(const char* filename)
{
  TFile* myFile = new TFile(filename);
  TTree* myTree = (TTree*) myFile->Get("theRunTree");
  TGraph* tprof = new TGraph();

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
  int countt=0;

  for (int i=0; i< Events; i++)
  {
    myTree->GetEvent(i);
    if (i==0){initialenergy=e->at(0);}

    if (0.9*round(initialenergy)>round(e->at(0)) || 1.1*round(initialenergy)<round(e->at(0)) || i==Events)
    {myTree->GetEvent(i-1);
      tprof->SetPoint(count, e->at(0), y/(county*2.329002));
      //cout<<e->at(0)<<"      "<<y/(county*2.329002)<<"     "<<county<<endl;
      y=0;
      county=1;
      count++;
      myTree->GetEvent(i);
      initialenergy=e->at(0);
    }

    else
    {double length=0;
    double ee=0;
      //for (int j=0; j<e->size(); j++)
      //{
      length=l->at(0);
      ee=edep->at(0);
      //}
      y+=ee/(length);
      county++;
      //tprof->SetPoint(countt, e->at(0), y);
      countt++;
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
