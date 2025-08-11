#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <limits>

using namespace std;

struct Elevator
{
    int id;           // Elevator ID (1 or 2)
    int currentFloor; // Current position
    int targetFloor;  // Destination floor
    bool moving;      // Is elevator moving?
    string direction; // "UP", "DOWN", or "IDLE"

    Elevator(int i)
    {
        id = i;
        currentFloor = 1; // Start at floor 1
        targetFloor = 1;
        moving = false;
        direction = "IDLE";
    }

    void moveOneStep()
    {
        if (!moving)
            return;

        if (currentFloor < targetFloor)
        {
            currentFloor++;
            direction = "UP";
        }
        else if (currentFloor > targetFloor)
        {
            currentFloor--;
            direction = "DOWN";
        }

        if (currentFloor == targetFloor)
        {
            moving = false;
            direction = "IDLE";
            cout << "Elevator " << id << " arrived at floor " << currentFloor << endl;
        }
    }

    void assignTarget(int floor)
    {
        targetFloor = floor;
        if (targetFloor != currentFloor)
        {
            moving = true;
            direction = (targetFloor > currentFloor) ? "UP" : "DOWN";
        }
        else
        {
            moving = false;
            direction = "IDLE";
        }
    }
};

int main()
{
    Elevator e1(1), e2(2);
    const int totalFloors = 11;

    while (true)
    {
        cout << "\n--- Elevator Status ---\n";
        cout << "Elevator 1: Floor " << e1.currentFloor << " | " << e1.direction << endl;
        cout << "Elevator 2: Floor " << e2.currentFloor << " | " << e2.direction << endl;

        cout << "\nEnter your current floor (1-" << totalFloors << ", 0 to quit): ";
        int start;
        cin >> start;
        if (start == 0)
            break;
        if (start < 1 || start > totalFloors)
        {
            cout << "Invalid floor.\n";
            continue;
        }

        cout << "Enter your destination floor (1-" << totalFloors << "): ";
        int dest;
        cin >> dest;
        if (dest < 1 || dest > totalFloors || dest == start)
        {
            cout << "Invalid destination.\n";
            continue;
        }

        // Determine which elevator is closer
        int dist1 = abs(e1.currentFloor - start);
        int dist2 = abs(e2.currentFloor - start);

        Elevator *chosen;
        if (dist1 <= dist2)
            chosen = &e1;
        else
            chosen = &e2;

        cout << "Elevator " << chosen->id << " will come to you.\n";
        chosen->assignTarget(start);

        // Move elevators step by step until request floor reached
        while (e1.moving || e2.moving)
        {
            e1.moveOneStep();
            e2.moveOneStep();
        }

        // Now move chosen elevator to destination
        chosen->assignTarget(dest);
        while (e1.moving || e2.moving)
        {
            e1.moveOneStep();
            e2.moveOneStep();
        }
    }

    cout << "Simulation ended.\n";
    return 0;
}
