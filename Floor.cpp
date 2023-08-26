#include <bits/stdc++.h>

using namespace std;

class Floor {
public:
    int data;
    Floor* next;
};

class Elevator {
private:
    Floor* head;
    bool direction; // true for up, false for down
    int totalWeight ;


public:
    Elevator() : head(nullptr), direction(true) {}
    
    bool isOverweight(int addedWeight) {
        return (totalWeight + addedWeight) > 100;
    }
void add(int no_people, int pos) {
    int go_floor;
    for (int i = 0; i < no_people; i++) {
        cout << "Person " << i+1 << " - Enter the floor where you would like to go: ";
        cin >> go_floor;

        int person_weight;
        cout << "Person " << i+1 << " - Enter the weight of the person: ";
        cin >> person_weight;

        if (pos != go_floor) {
            // Check for weight constraints
            if (isOverweight(person_weight)) {
                cout << "The lift is overweight. Cannot add more people." << endl;
                break;
            }

            Floor* new_node = new Floor;
            new_node->data = go_floor;
            new_node->next = nullptr;
            if (head == nullptr) {
                head = new_node;
            } else {
                Floor* temp1 = head;
                while (temp1->next != nullptr) {
                    temp1 = temp1->next;
                }
                temp1->next = new_node;
            }

            // Update total weight
            totalWeight += person_weight;
        } else {
            std::cout << "You are already on this floor." << std::endl;
        }
    }
}


    void removePeople(int pos) {
        Floor* temp = head;
        Floor* prev = nullptr;
        while (temp != nullptr) {
            if (temp->data == pos) {
                if (prev == nullptr) {
                    head = temp->next;
                    delete temp;
                    temp = head;
                } else {
                    prev->next = temp->next;
                    delete temp;
                    temp = prev->next;
                }
            } else {
                prev = temp;
                temp = temp->next;
            }
        }
    }

    void printList() {
        Floor* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    int countPeople() {
        Floor* temp = head;
        int count = 0;
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }
 bool fetchDirection(int pos) {
        Floor* temp = head;
        bool flag = false;

        if (temp != nullptr) {
            if (temp->next == nullptr) {
                if (temp->data > pos) {
                    direction = true;
                } else {
                    direction = false;
                }

                return direction;
            }

            while (temp->next != nullptr) {
                if (temp->data > pos) {
                    temp = temp->next;
                } else {
                    flag = true;
                    break;
                }
            }

            if (!flag) {
                return true;
            }

            temp = head;
            while (temp->next != nullptr) {
                if (temp->data < pos) {
                    temp = temp->next;
                } else {
                    flag = true;
                    break;
                }
            }

            if (!flag) {
                return false;
            }

            temp = head;
            int up = 0;
            int down = 0;
            while (temp->next != nullptr) {
                if (temp->data > pos) {
                    up++;
                    temp = temp->next;
                } else {
                    down++;
                    temp = temp->next;
                }
            }

            if (up > down) {
                return true;
            } else if (down > up) {
                return false;
            } else {
                return direction;
            }
        } else {
            return direction;
        }
    }

    int fetchTill(bool direction) {
        int ret;
        Floor* temp = head;

        if (temp != nullptr) {
            ret = temp->data;
            if (direction == true) {
                while (temp->next != nullptr) {
                    if (temp->data > ret) {
                        ret = temp->data;
                    }
                    temp = temp->next;
                }
                if (temp->data > ret) {
                    ret = temp->data;
                }
                return ret;
            } else {
                while (temp->next != nullptr) {
                    if (temp->data < ret) {
                        ret = temp->data;
                    }
                    temp = temp->next;
                }
                if (temp->data < ret) {
                    ret = temp->data;
                }
                return ret;
            }
        } else {
            return -1;
        }
    }
};

int main() {
    cout << "----------------------## Floor Navigation System ##------------------------\n";
    
    int h, pos;
    cout << "Enter the height of the building and position of the lift: ";
    cin >> h >> pos;
    
    Elevator elevator;
    int till = -1;
    bool direction = true;
    int people_count;
    int no_people;

    // true - up
    // false - down
    while (true) {
        elevator.removePeople(pos);
        cout << "\n";
        elevator.printList();

        cout << "-------------- FLOOR " << pos << " -------------\n";
        people_count = elevator.countPeople();
       cout << "People in lift: " << people_count << "\n";

        if (people_count == 10) {
            cout << "Lift is full. Skipping the floor.\n";
        } else {
            do {
                cout << "Enter the number of people who want to enter the lift: ";
                cin >> no_people;
                if (no_people + people_count <= 10) {
                    break;
                } else {
                    cout << "The lift is full. Please enter a valid number of people.\n";
                }
            } while (true);

            if (no_people == -1) {
                break;
            } else if (no_people >= 0 && no_people <= h) {
                if (no_people == 0) {
                    cout << "No one wants to enter the lift.\n";
                } else {
                    elevator.add(no_people, pos);
                }
            } else {
                cout << "Invalid input.\n";
            }
        }

        if (till == -1 || till == pos) {
            direction = elevator.fetchDirection(pos);
            till = elevator.fetchTill(direction);
        } else {
            std::cout << " << CHECK SKIPPED TILL FLOOR " << till << " >> ";
        }

        if (direction) {
            if (pos == h) {
                direction = false;
                pos--;
            } else {
                pos++;
            }
        } else {
            if (pos == 0) {
                direction = true;
                pos++;
            } else {
                pos--;
            }
        }

        cout << "\n";
        elevator.printList();
    }

    return 0;
}
