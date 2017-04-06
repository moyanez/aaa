#include <iostream>
#include <vector>
#include <sstream>
#include <cassert>
using namespace std;
char Scale[] = "KFC";
struct temperature
{
    double temp;
    char scale;
};
istream &operator>>(istream& stream, temperature& temp)
{
    cout << "vvedite temperatury \n";
    stream >> temp.temp >> temp.scale;
    return stream;
}
void test_temperature_input()
{
    temperature tempr;
    istringstream iss("10K");
    {iss>>tempr;
    assert (tempr.temp==10);
    assert (tempr.scale=='K');}

    istringstream isf("10F");
    isf>>tempr;
    assert (tempr.temp==10);
    assert (tempr.scale=='F');

    istringstream isc("10C");
    isc>>tempr;
    assert (tempr.temp==10);
    assert (tempr.scale=='C');
}
double convert (double input, char from,char to)
{
       double inputc,inputf,inputk;
       temperature tempr;
       from=tempr.scale;
    if (from=='K')
    {
      inputc=input-273;
      inputf=input*2-459;
    cout<<inputc<<"C\n";
    cout<<inputf<<"F\n";
    }
    if (from=='C')
    {
        inputk=input+273;
        inputf=(input*9/5)+32;
        cout<<inputk<<"K\n";
        cout<<inputf<<"F";
    }
    if (from=='F')
    {
        inputc=(input-32)*5/9;
        inputk=(input-32)*5/9+273;
        cout<<inputc<<"C\n";
        cout<<inputk<<"K";
    }
}


int main()
{
    temperature tempr;
    cout<<tempr.temp;
    cout<<tempr.scale;
    cin>>tempr;
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;

    cerr << "Enter numbers: ";
    vector<double> numbers(number_count);
    for (size_t i = 0; i < number_count; i++) {
        cin >> numbers[i];
    }

    size_t column_count;
    cerr << "Enter column count: ";
    cin >> column_count;

    double min = numbers[0];
    double max = numbers[0];
    for (double number : numbers) {
        if (number < min) {
            min = number;
        }
        if (number > max) {
            max = number;
        }
    }

    vector<size_t> counts(column_count);
    for (double number : numbers) {
        size_t column = (size_t)((number - min) / (max - min) * column_count);
        if (column == column_count) {
            column--;
        }
        counts[column]++;
    }

    const size_t screen_width = 80;
    const size_t axis_width = 4;
    const size_t chart_width = screen_width - axis_width;

    // Можно было бы считать в предыдущем цикле, но так более наглядно.
    size_t max_count = 0;
    for (size_t count : counts) {
        if (count > max_count) {
            max_count = count;
        }
    }
    const bool scaling_needed = max_count > chart_width;

    for (size_t count : counts) {
        if (count < 100) {
            cout << ' ';
        }
        if (count < 10) {
            cout << ' ';
        }
        cout << count << "|";

        size_t height = count;
        if (scaling_needed) {
            // Point: код должен быть в первую очередь понятным.
            const double scaling_factor = (double)chart_width / max_count;
            height = (size_t)(count * scaling_factor);
        }

        for (size_t i = 0; i < height; i++) {
            cout << '*';
        }
        cout << '\n';
    }

    return 0;
}
