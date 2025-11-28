#include <iostream>
#include <fstream>
using namespace std;

struct Mars {
    char name[20];
    float distance;   // millions km
    float temperature;
};

struct Spacecraft {
    char name[50];
    float maxSpeed;       // km/h
    float payload;        // kg
    int daysWithoutCharge;
    float maxDistance;    // millions km
    float maxTemp;        // C
};

// 2. Зчитування з файлу spacecraft.txt
void loadSpacecrafts(Spacecraft* arr, int& count) {
    ifstream fin("spacecraft.txt");

    if (!fin.is_open()) {
        cout << "Error: cannot open spacecraft.txt" << endl;
        count = 0;
        return;
    }

    count = 0;

    while (true) {
        fin >> arr[count].name
            >> arr[count].maxSpeed
            >> arr[count].payload
            >> arr[count].daysWithoutCharge
            >> arr[count].maxDistance
            >> arr[count].maxTemp;

        if (fin.fail())
            break;

        count++;
    }

    fin.close();
}

// 3. Вивід усіх апаратів
void showAll(Spacecraft* arr, int count) {
    cout << "Available spacecrafts:" << endl << endl;

    for (int i = 0; i < count; i++) {
        cout << i + 1 << ") " << arr[i].name << endl;
        cout << "   Max speed: " << arr[i].maxSpeed << " km/h" << endl;
        cout << "   Payload: " << arr[i].payload << " kg" << endl;
        cout << "   Days without charge: " << arr[i].daysWithoutCharge << endl;
        cout << "   Max distance: " << arr[i].maxDistance << " million km" << endl;
        cout << "   Max temperature: " << arr[i].maxTemp << " C" << endl;
        cout << endl;
    }
}

// 4. Вибір НАЙКРАЩОГО (найшвидшого) апарата, що підходить
int chooseBestCraft(Spacecraft* arr, int count, float distance, float temp) {
    int bestIndex = -1;
    float bestSpeed = 0.0f;

    for (int i = 0; i < count; i++) {
        bool okDistance = arr[i].maxDistance >= distance;
        bool okTemp = arr[i].maxTemp >= temp;

        if (okDistance && okTemp) {
            if (bestIndex == -1 || arr[i].maxSpeed > bestSpeed) {
                bestIndex = i;
                bestSpeed = arr[i].maxSpeed;
            }
        }
    }

    return bestIndex;
}

// 5. Час польоту
float travelTime(float distance, float speed) {
    float km = distance * 1000000.0f; // millions km -> km
    return km / speed;                // hours
}

// 6. Перевірка вантажу
bool canDeliver(Spacecraft craft, float cargo) {
    return cargo <= craft.payload;
}

int main() {
    // 1. Структура Mars (для порядку, хочемо мати об’єкт)
    Mars mars = { "Mars", 225.0f, -60.0f };

    Spacecraft arr[100];
    int count = 0;

    loadSpacecrafts(arr, count);

    cout << "Loaded spacecrafts: " << count << endl << endl;

    if (count == 0) {
        cout << "No spacecrafts loaded. Check spacecraft.txt location and format." << endl;
        return 0;
    }

    showAll(arr, count);

    // Параметри місії від користувача
    float dist, temp;
    cout << "Enter mission distance (millions km): ";
    cin >> dist;

    cout << "Enter mission average temperature (C): ";
    cin >> temp;

    int idx = chooseBestCraft(arr, count, dist, temp);

    if (idx == -1) {
        cout << "No suitable spacecraft found." << endl;
        return 0;
    }

    cout << endl << "Chosen spacecraft:" << endl;
    cout << arr[idx].name << endl;

    cout << "Max speed: " << arr[idx].maxSpeed << " km/h" << endl;
    cout << "Payload: " << arr[idx].payload << " kg" << endl;
    cout << "Days without charge: " << arr[idx].daysWithoutCharge << endl;
    cout << "Max distance: " << arr[idx].maxDistance << " million km" << endl;
    cout << "Max temperature: " << arr[idx].maxTemp << " C" << endl;

    float hours = travelTime(dist, arr[idx].maxSpeed);
    cout << endl << "Travel time (hours): " << hours << endl;

    float cargo;
    cout << "Enter cargo weight (kg): ";
    cin >> cargo;

    if (canDeliver(arr[idx], cargo))
        cout << "This spacecraft CAN deliver the cargo." << endl;
    else
        cout << "This spacecraft CANNOT deliver the cargo." << endl;

    return 0;
}
