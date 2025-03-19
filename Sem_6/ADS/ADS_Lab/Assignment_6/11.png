#include "header.h"

int main() {
  int numHubs;
  cout << "Enter number of hubs: ";
  cin >> numHubs;
  vector<LogisticCompany> hubs(numHubs);

  int choice;

  while (true) {
    cout << "\nLogistic Company Menu:" << endl;
    cout << "1. Insert Truck" << endl;
    cout << "2. Display Trucks" << endl;
    cout << "3. Extract Min Priority Truck" << endl;
    cout << "4. Get Min Priority Truck" << endl;
    cout << "5. Decrease Urgency Key" << endl;
    cout << "6. Delete Truck" << endl;
    cout << "7. Send Highest Priority Truck from Each Hub" << endl;
    cout << "8. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1: {
      int hubId, truckId, distance, urgency;
      cout << "Enter Hub ID (0 to " << numHubs - 1 << "): ";
      cin >> hubId;
      if (hubId < 0 || hubId >= numHubs) {
        cout << "Invalid Hub ID." << endl;
        break;
      }
      cout << "Enter Truck ID: ";
      cin >> truckId;
      cout << "Enter Distance: ";
      cin >> distance;
      cout << "Enter Urgency: ";
      cin >> urgency;
      hubs[hubId].insertTruck(truckId, distance, urgency);
      cout << "Truck inserted successfully in Hub " << hubId << "." << endl;
      break;
    }
    case 2: {
      int hubId;
      cout << "Enter Hub ID (0 to " << numHubs - 1 << ") to display: ";
      cin >> hubId;
      if (hubId < 0 || hubId >= numHubs) {
        cout << "Invalid Hub ID." << endl;
        break;
      }
      cout << "Trucks in Hub " << hubId << ":" << endl;
      hubs[hubId].display();
      break;
    }
    case 3: {
      int hubId;
      cout << "Enter Hub ID (0 to " << numHubs - 1 << ") to extract min: ";
      cin >> hubId;
      if (hubId < 0 || hubId >= numHubs) {
        cout << "Invalid Hub ID." << endl;
        break;
      }
      hubs[hubId].extractMin();
      cout << "Min priority truck extracted from Hub " << hubId << "." << endl;
      break;
    }
    case 4: {
      int hubId;
      cout << "Enter Hub ID (0 to " << numHubs - 1
           << ") to get min priority truck: ";
      cin >> hubId;
      if (hubId < 0 || hubId >= numHubs) {
        cout << "Invalid Hub ID." << endl;
        break;
      }
      cout << "Min Priority Truck Urgency in Hub " << hubId << ": "
           << hubs[hubId].getMinPriorityTruck() << endl;
      break;
    }
    case 5: {
      int hubId, targetKey, newKey;
      cout << "Enter Hub ID (0 to " << numHubs - 1 << "): ";
      cin >> hubId;
      if (hubId < 0 || hubId >= numHubs) {
        cout << "Invalid Hub ID." << endl;
        break;
      }
      cout << "Enter current urgency: ";
      cin >> targetKey;
      cout << "Enter new urgency: ";
      cin >> newKey;
      hubs[hubId].decreaseKey(targetKey, newKey);
      cout << "Urgency updated successfully in Hub " << hubId << "." << endl;
      break;
    }
    case 6: {
      int hubId, truckId;
      cout << "Enter Hub ID (0 to " << numHubs - 1 << "): ";
      cin >> hubId;
      if (hubId < 0 || hubId >= numHubs) {
        cout << "Invalid Hub ID." << endl;
        break;
      }
      cout << "Enter Truck ID to delete: ";
      cin >> truckId;
      hubs[hubId].deleteKey(truckId);
      cout << "Truck deleted successfully from Hub " << hubId << "." << endl;
      break;
    }
    case 7: {
      cout << "Sending highest priority truck from each hub..." << endl;
      for (int i = 0; i < numHubs; i++) {
        if (!hubs[i].empty()) {
          int minPriority = hubs[i].getMinPriorityTruck();
          cout << "Hub " << i << " sending truck with urgency: " << minPriority
               << endl;
          hubs[i].extractMin();
        } else {
          cout << "Hub " << i << " is empty." << endl;
        }
      }
      break;
    }
    case 8:
      cout << "Exiting..." << endl;
      return 0;
    default:
      cout << "Invalid choice. Please try again." << endl;
    }
  }
}
