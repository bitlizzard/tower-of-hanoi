#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <stack>
#include <cmath>
#include <chrono>

using namespace std;

void printRods(const stack<int>& A, const stack<int>& B, const stack<int>& C) {
    auto printStack = [](const stack<int>& s, const string& name) //lambda function that takes in a stack and labels the rods accordingly. 
        {
            stack<int> temp = s; //temporary storage as stacks do not allow reading access wihtout losing data. 
            vector<int> elements;
            while (!temp.empty()) {
                elements.push_back(temp.top()); // popping values from the top of the stack into the vector.
                temp.pop();// popping the stack as stacks do not allow top-down access.
            }

            cout << name << ":";
            for (int i = elements.size() - 1 ; i >= 0; --i) cout << elements[i] << " ";
            cout << endl; 
        };

    cout << "--Rods--" << endl;
    printStack(A, "A");
    printStack(B, "B");
    printStack(C, "C");
    cout << endl;


};

void MoveDisk( vector<stack<int>>& rods, int source_rod, int destination_rod ) {
    int disknum = rods[source_rod].top();
    rods[source_rod].pop();
    rods[destination_rod].push(disknum);

    cout << "Move disk " << disknum << " from Rod " << char('A' + source_rod) << " to Rod " << char('A' + destination_rod) << endl; //ASCII math to update the disk position on rods
    printRods(rods[0], rods[1], rods[2]);

};



void TowerofHanoi(int n, int source_rod, int auxilary_rod, int destination_rod, vector<stack<int>>& rods)
{
    if (n == 1) {
        MoveDisk(rods, source_rod, destination_rod);
        return;
    }

    TowerofHanoi(n - 1, source_rod, destination_rod, auxilary_rod, rods);
    MoveDisk(rods, source_rod, destination_rod);
    TowerofHanoi(n - 1, auxilary_rod, source_rod, destination_rod, rods);
};

//stacks are being used to represent rods due to the LIFO structure that simulates the disks being removed or placed.
 
void Timetaken(int n, int source_rod, int auxilary_rod, int destination_rod, vector<stack<int>>& rods) {
   
    cout << "Expected number of moves: " << (pow(2, n) - 1) << endl;

    auto start = std::chrono::high_resolution_clock::now();
    TowerofHanoi(n, 0, 1, 2, rods);
    auto end = std::chrono::high_resolution_clock::now();
    auto time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    cout << "Time taken to solve tower of hanoi problem: " << time_elapsed.count() << " milliseconds." << endl;
}

int main()
{
    int n;
    cout << "Input number of disks: ";
    cin >> n;

    vector<std::stack<int>> rods(3);
    for (int i = n; i >= 1; i--) {
        rods[0].push(i);
    }

    Timetaken(n, 0, 1, 2, rods);


    return 0;
}


