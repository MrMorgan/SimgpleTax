#include <iostream>
#include <string>
#include <iomanip>

// Values defined in Cents as integers
const int SingleDeduction = 1200000;
const int MarriedJointDeduction = 2400000;
const int HeadDeduction = 1800000;
// Tax rates by bracket
const int Rates[] = {10, 12, 22, 24, 32, 35, 37};
const int SingleBrackets[] = {0, 952500, 3870000, 8250000, 15750000, 20000000, 50000000};
const int MarriedBrackets[] = {0, 1905000, 7740000, 16500000, 31500000, 40000000, 60000000};

int calcTaxes(int taxableIncome, int married){
    const int *bracket;
    int taxOwed = 0;
    if(married) {
        bracket = MarriedBrackets;
    }
    else{
        bracket = SingleBrackets;
    }
    
    for(int i = 1; i < sizeof(bracket) && taxableIncome > 0 ; i++){
        int bracketSize = bracket[i] - bracket[i-1];
        if(taxableIncome < bracketSize){
            taxOwed += (taxableIncome / Rates[i-1]);
        }
        else{
            taxOwed += bracketSize / Rates[i-1];
        }
        taxableIncome -= bracketSize;
    }
    if(taxableIncome > 0){
        taxOwed += (taxableIncome / Rates[sizeof(Rates)-1]);
    }
    return taxOwed;
}

std::string decimalFormat(int cents){
    std::string value = std::to_string(cents);
    value.insert( value.length()-2 , 1,  '.');
    return value;
}


using namespace std;
int main(){
    int grossIncome = 0;
    int married = 0;
    int deduction = SingleDeduction;
    char userInput;
    cout << "What was your 2018 income?" << endl;
    cin >> grossIncome;
    // Convert to cents
    grossIncome *= 100;
    cout << "Are you filing Married Jointly? (Y or N)" << endl;
    cin >> userInput;
    ( userInput ==  'Y') ? married = 1 : married = 0;
    if(married){
        deduction = MarriedJointDeduction;
    }
    else{
        cout << "Are you Head of Household? (Y or N)" << endl;
        cin >> userInput;
        ( userInput ==  'Y') ? deduction = HeadDeduction : deduction = SingleDeduction;
    }
    int netIncome, taxableIncome, taxOwed; 
    cout << "Deduction is: " << decimalFormat(deduction) << endl;
    taxableIncome = (grossIncome < deduction) ? 0 : grossIncome - deduction ; 
    taxOwed = calcTaxes(taxableIncome, married);
    netIncome = taxableIncome - taxOwed + deduction;
    //cout << "Taxable: " << taxableIncome <<" "<< "Net: " << netIncome << " "<< "Tax: " << taxOwed << endl;
    cout << "You will pay $" << decimalFormat(taxOwed) << " in taxes " << endl;
    cout << "Your take home pay after tax will be $" << decimalFormat(netIncome) << endl;
    std::cout << std::setprecision(2) << std::fixed;
    cout << "Your tax rate for the year is %" << (double)100*taxOwed/grossIncome << endl;
}

