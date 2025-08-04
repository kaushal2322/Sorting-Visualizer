#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>
#include <iomanip>

class SortingVisualizer {
private:
    std::vector<int> arr;
    int size;
    int maxVal;
    int delay; // milliseconds

public:
    SortingVisualizer(int n = 20, int delayMs = 100) : size(n), delay(delayMs) {
        generateRandomArray();
    }

    void generateRandomArray() {
        arr.clear();
        arr.resize(size);
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, size);
        
        for (int i = 0; i < size; i++) {
            arr[i] = dis(gen);
        }
        
        maxVal = *std::max_element(arr.begin(), arr.end());
    }

    void display(const std::string& algorithm = "", int step = -1, 
                int highlight1 = -1, int highlight2 = -1) {
        // Clear screen (works on most terminals)
        std::cout << "\033[2J\033[H";
        
        if (!algorithm.empty()) {
            std::cout << "Algorithm: " << algorithm;
            if (step >= 0) std::cout << " | Step: " << step;
            std::cout << "\n\n";
        }

        // Display bars vertically
        for (int row = maxVal; row >= 1; row--) {
            for (int i = 0; i < size; i++) {
                if (arr[i] >= row) {
                    if (i == highlight1) {
                        std::cout << "\033[31m██\033[0m"; // Red for first highlight
                    } else if (i == highlight2) {
                        std::cout << "\033[32m██\033[0m"; // Green for second highlight
                    } else {
                        std::cout << "██";
                    }
                } else {
                    std::cout << "  ";
                }
            }
            std::cout << "\n";
        }
        
        // Display array values
        std::cout << "\n";
        for (int i = 0; i < size; i++) {
            std::cout << std::setw(2) << arr[i];
        }
        std::cout << "\n\n";
        
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }

    // Bubble Sort with visualization
    void bubbleSort() {
        std::cout << "Starting Bubble Sort...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        
        int step = 0;
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                display("Bubble Sort", step++, j, j + 1);
                
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                    display("Bubble Sort", step++, j, j + 1);
                }
            }
        }
        display("Bubble Sort - COMPLETED!");
    }

    // Selection Sort with visualization
    void selectionSort() {
        std::cout << "Starting Selection Sort...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        
        int step = 0;
        for (int i = 0; i < size - 1; i++) {
            int minIdx = i;
            display("Selection Sort", step++, i, minIdx);
            
            for (int j = i + 1; j < size; j++) {
                display("Selection Sort", step++, j, minIdx);
                if (arr[j] < arr[minIdx]) {
                    minIdx = j;
                }
            }
            
            if (minIdx != i) {
                std::swap(arr[i], arr[minIdx]);
                display("Selection Sort", step++, i, minIdx);
            }
        }
        display("Selection Sort - COMPLETED!");
    }

    // Insertion Sort with visualization
    void insertionSort() {
        std::cout << "Starting Insertion Sort...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        
        int step = 0;
        for (int i = 1; i < size; i++) {
            int key = arr[i];
            int j = i - 1;
            
            display("Insertion Sort", step++, i, -1);
            
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                display("Insertion Sort", step++, j, j + 1);
                j--;
            }
            arr[j + 1] = key;
            display("Insertion Sort", step++, j + 1, -1);
        }
        display("Insertion Sort - COMPLETED!");
    }

    // Quick Sort with visualization
    void quickSort() {
        std::cout << "Starting Quick Sort...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        
        int step = 0;
        quickSortHelper(0, size - 1, step);
        display("Quick Sort - COMPLETED!");
    }

private:
    void quickSortHelper(int low, int high, int& step) {
        if (low < high) {
            int pi = partition(low, high, step);
            quickSortHelper(low, pi - 1, step);
            quickSortHelper(pi + 1, high, step);
        }
    }

    int partition(int low, int high, int& step) {
        int pivot = arr[high];
        int i = low - 1;
        
        for (int j = low; j < high; j++) {
            display("Quick Sort", step++, j, high);
            if (arr[j] < pivot) {
                i++;
                std::swap(arr[i], arr[j]);
                display("Quick Sort", step++, i, j);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        display("Quick Sort", step++, i + 1, high);
        return i + 1;
    }

public:
    void menu() {
        int choice;
        
        do {
            std::cout << "\n=== SORTING VISUALIZER ===\n";
            std::cout << "1. Generate New Random Array\n";
            std::cout << "2. Bubble Sort\n";
            std::cout << "3. Selection Sort\n";
            std::cout << "4. Insertion Sort\n";
            std::cout << "5. Quick Sort\n";
            std::cout << "6. Change Array Size\n";
            std::cout << "7. Change Animation Speed\n";
            std::cout << "8. Display Current Array\n";
            std::cout << "0. Exit\n";
            std::cout << "Current Array Size: " << size << " | Speed: " << delay << "ms\n";
            std::cout << "Enter choice: ";
            
            std::cin >> choice;
            
            switch (choice) {
                case 1:
                    generateRandomArray();
                    std::cout << "New random array generated!\n";
                    break;
                case 2:
                    bubbleSort();
                    break;
                case 3:
                    selectionSort();
                    break;
                case 4:
                    insertionSort();
                    break;
                case 5:
                    quickSort();
                    break;
                case 6: {
                    int newSize;
                    std::cout << "Enter new array size (5-50): ";
                    std::cin >> newSize;
                    if (newSize >= 5 && newSize <= 50) {
                        size = newSize;
                        generateRandomArray();
                        std::cout << "Array size changed to " << size << "\n";
                    } else {
                        std::cout << "Invalid size! Please enter between 5 and 50.\n";
                    }
                    break;
                }
                case 7: {
                    int newDelay;
                    std::cout << "Enter animation delay in milliseconds (10-1000): ";
                    std::cin >> newDelay;
                    if (newDelay >= 10 && newDelay <= 1000) {
                        delay = newDelay;
                        std::cout << "Animation speed changed to " << delay << "ms\n";
                    } else {
                        std::cout << "Invalid delay! Please enter between 10 and 1000.\n";
                    }
                    break;
                }
                case 8:
                    display();
                    break;
                case 0:
                    std::cout << "Thanks for using Sorting Visualizer!\n";
                    break;
                default:
                    std::cout << "Invalid choice! Please try again.\n";
            }
            
            if (choice != 0) {
                std::cout << "Press Enter to continue...";
                std::cin.ignore();
                std::cin.get();
            }
            
        } while (choice != 0);
    }
};

int main() {
    SortingVisualizer visualizer;
    visualizer.menu();
    return 0;
}