#include <stdio.h>
#include <stdlib.h>

#define MAX_SAMPLES 3000

// ----------------------
// Data Structures
// ----------------------

typedef struct {
    float time;        // time in seconds
    double probability; // signal probability (0-1)
} SensorData;

typedef struct {
    int id;                         // sensor ID
    double threshold;               // detection threshold
    SensorData data[MAX_SAMPLES];   // measurement samples
    int object_detection[MAX_SAMPLES]; // binary detection signal
    int sample_count;               // number of samples read
} Sensor;


// ----------------------
// Function Prototypes
// ----------------------

int readSensorFile(const char* filename, Sensor* sensor);
void generateDetection(Sensor* sensor);
void printIntervals(Sensor* sensor);
void printFusion(Sensor* s1, Sensor* s2);


// ----------------------
// Read measurement file
// ----------------------

int readSensorFile(const char* filename, Sensor* sensor) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file %s\n", filename);
        return 0;
    }

    int i = 0;
    while (i < MAX_SAMPLES &&
           fscanf(file, "%f %lf",
                  &sensor->data[i].time,
                  &sensor->data[i].probability) == 2) {
        i++;
    }

    sensor->sample_count = i;

    fclose(file);
    return 1;
}


// ----------------------
// Generate binary detection
// ----------------------

void generateDetection(Sensor* sensor) {
    for (int i = 0; i < sensor->sample_count; i++) {
        if (sensor->data[i].probability > sensor->threshold)
            sensor->object_detection[i] = 1;
        else
            sensor->object_detection[i] = 0;
    }
}


// ----------------------
// Print detection intervals
// ----------------------

void printIntervals(Sensor* sensor) {
    int active = 0;
    float start_time = 0.0;

    for (int i = 0; i < sensor->sample_count; i++) {

        // Start of interval (0 → 1)
        if (!active && sensor->object_detection[i] == 1) {
            active = 1;
            start_time = sensor->data[i].time;
        }

        // End of interval (1 → 0)
        if (active && sensor->object_detection[i] == 0) {
            active = 0;
            float end_time = sensor->data[i - 1].time;
            printf("Start: %.2f s End: %.2f s\n", start_time, end_time);
        }
    }

    // If still active at the end
    if (active) {
        float end_time = sensor->data[sensor->sample_count - 1].time;
        printf("Start: %.2f s End: %.2f s\n", start_time, end_time);
    }
}


// ----------------------
// Print fused intervals
// ----------------------

void printFusion(Sensor* s1, Sensor* s2) {
    int active = 0;
    float start_time = 0.0;

    int min_samples = (s1->sample_count < s2->sample_count)
                      ? s1->sample_count
                      : s2->sample_count;

    for (int i = 0; i < min_samples; i++) {

        int fused = s1->object_detection[i] &&
                    s2->object_detection[i];

        // Start of fused interval
        if (!active && fused) {
            active = 1;
            start_time = s1->data[i].time;
        }

        // End of fused interval
        if (active && !fused) {
            active = 0;
            float end_time = s1->data[i - 1].time;
            printf("Start: %.2f s End: %.2f s\n", start_time, end_time);
        }
    }

    // If still active at end
    if (active) {
        float end_time = s1->data[min_samples - 1].time;
        printf("Start: %.2f s End: %.2f s\n", start_time, end_time);
    }
}


// ----------------------
// Main
// ----------------------

int main() {

    Sensor sensor1 = {1, 0.8};
    Sensor sensor2 = {2, 0.7};

    // Read files
    if (!readSensorFile("sensor1.txt", &sensor1)) return 1;
    if (!readSensorFile("sensor2.txt", &sensor2)) return 1;

    // Generate binary signals
    generateDetection(&sensor1);
    generateDetection(&sensor2);

    // Output results
    printf("\n--- Object Detection Results ---\n\n");

    printf("Sensor 1 detections:\n");
    printIntervals(&sensor1);

    printf("\nSensor 2 detections:\n");
    printIntervals(&sensor2);

    printf("\nFused signal (both sensors):\n");
    printFusion(&sensor1, &sensor2);

    return 0;
}