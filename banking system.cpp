#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Account{
  private:
    string AccountCode;
    string Name;
    string Surname;
    float Balance;
  public:
    Account(){}
    Account(string AccountCode0, string Name0, string Surname0, float Balance0 = 0){
      AccountCode = AccountCode0;
      Name = Name0;
      Surname = Surname0;
      Balance = Balance0;
    }
    string getCode(){return AccountCode;}
    string getName(){return Name;}
    string getSurname(){return Surname;}
    float getBalance(){return Balance;}
    void setAccountCode(string code){AccountCode = code;}
    void setName(string name){Name = name;}
    void setSurname(string surname){Surname = surname;}
    void setBalance(float bal){Balance = bal;}
    friend ofstream & operator<<(ofstream &ofs, Account &acc);
    friend ostream & operator<<(ostream &ofs, Account &acc);
    friend ifstream & operator>>(ifstream &ofs, Account &acc);
    friend istream & operator>>(istream &ofs, Account &acc);
};
istream & operator>>(istream &ofs, Account &acc){
  string AccountCode;
  string Name;
  string Surname;
  float Balance;
  ofs >> AccountCode >> Name >> Surname >> Balance;
  acc.setAccountCode(AccountCode);
  acc.setName(Name);
  acc.setSurname(Surname);
  acc.setBalance(Balance);
}
ifstream & operator>>(ifstream &ofs, Account &acc){
  string AccountCode;
  string Name;
  string Surname;
  float Balance;
  ofs >> AccountCode >> Name >> Surname >> Balance;
  acc.setAccountCode(AccountCode);
  acc.setName(Name);
  acc.setSurname(Surname);
  acc.setBalance(Balance);
}
ofstream & operator<<(ofstream &ofs, Account &acc){
  ofs << acc.getCode() << " " << acc.getName() << " " << acc.getSurname() << " " << acc.getBalance() << endl;
}
ostream & operator<<(ostream &ofs, Account &acc){
  ofs << acc.getCode() << " " << acc.getName() << " " << acc.getSurname() << " " << acc.getBalance() << endl;
}
vector<Account> accs;
void FindByID(string ID){
  for(int i = 0; i < accs.size();i++){
    if(ID == accs[i].getCode()){
      cout << "Balance of this account: "<<accs[i].getBalance()<<endl;
      return;
    }
  }
  cout << "Account not found.\n\n";
}
void SaveData(){
  ofstream ofs("banking.txt");
  ofs << accs.size()<<endl;
  for(int i = 0; i < accs.size();i++){
    ofs << accs[i];
  }
  ofs.close();
}
void LoadData(){
  ifstream ifs;
  ifs.open("banking.txt");
  accs.clear();
  Account acc;
  int x;
  ifs >> x;
  for(int i = 0; i < x;i++){
    ifs >> acc;
    accs.push_back(acc);
  }
  ifs.close();
}
bool isUnique(string s){
if(s.size() == 0)return false;
  LoadData();
  for(int i = 0; i < accs.size();i++){
    if(s == accs[i].getCode())return false;
  }
  return true;
}
string gen(){
  string s;
  srand(time(NULL));
  while(!isUnique(s)){
    s.clear();
    for(int i =0;i < 10;i++){
      int x = rand() % 10;
      s+=(char)x+'0';
    }
  }
  return s;
}
void OpenAccount(){
  cout << "Please enter Name:\n";
  string n;
  cin >> n;
  cout << "Enter Surname:\n";
  string s;
  cin >> s;
  cout << "Enter starting balance:\n";
  float bal;
  cin >> bal;
  Account acc(gen(), n, s, bal);
  accs.push_back(acc);
  SaveData();
}
void ShowBalance(){
  cout << "Enter ID of Account:\n";
  string m;
  cin >> m;
  FindByID(m);
}
void Deposit(){
  cout << "Enter ID of Account:\n";
  string s;
  cin >> s;
  cout << "How much to deposit?\n";
  float b;
  cin >> b;
  for(int i = 0; i < accs.size();i++){
    if(s == accs[i].getCode()){
      accs[i].setBalance(accs[i].getBalance()+b);
      cout << "Deposited.\n\n";
      SaveData();
      return;
    }
  }
  cout << "Account not found.\n";
}
void Withdraw(){
  cout << "Enter ID of Account:\n";
  string s;
  cin >> s;
  cout << "How much to withdraw?\n";
  float b;
  cin >> b;
  for(int i = 0; i < accs.size();i++){
    if(s == accs[i].getCode()){
      accs[i].setBalance(accs[i].getBalance()-b);
      cout << "Withdrawn.\n\n";
      SaveData();
      return;
    }
  }
  cout << "Account not found.\n";
}
void CloseAccount(){
  cout << "Enter ID of Account:\n";
  string s;
  cin >> s;
  vector<Account> ac;
  for(int i = 0; i < accs.size();i++){
    if(s != accs[i].getCode()){
      ac.push_back(accs[i]);
    }
  }
  accs = ac;
  SaveData();
  LoadData();
  cout << "Account deleted\n";
}
void ShowAccounts(){
  LoadData();
  cout << "All accounts:\n";
  for(int i = 0; i < accs.size();i++){
      cout << accs[i];
  }
  cout << endl;
  return;
}
int main(){
  LoadData();
  while(1){
    int x;
    cout << "\nHello, welcome dear User! Choose an option:\n1. Open an account\n2. Show Balance\n3. Deposit\n4. Withdraw\n5. Close an account\n6. Show all accounts\n7. Quit\n";
    cin >> x;
    switch(x){
      case 1: OpenAccount();break;
      case 2: ShowBalance();break;
      case 3: Deposit();break;
      case 4: Withdraw();break;
      case 5: CloseAccount();break;
      case 6: ShowAccounts();break;
      case 7: cout << "Thank you for using our services. Goodbye!\n";return 0;
    }
  }
}
