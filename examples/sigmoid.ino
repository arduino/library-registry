#include "fnn.h"

FNN fnn(6); // Neural network dengan 6 input

void setup() {
    Serial.begin(9600);

    // Set bobot, bias, dan fungsi aktivasi
    fnn.setWeights({0.3, 0.5, 0.2, 0.4, 0.1, 0.6});
    fnn.setBiases({0.1, 0.2}); // Menambahkan biases untuk hidden dan output layer
    fnn.setActivationFunction(FNN::sigmoid); // Mencoba fungsi aktivasi yang lebih cocok untuk klasifikasi

    // Aturan fuzzy (perhatikan bahwa Anda perlu menyesuaikan output dengan label)
    fnn.setFuzzyRules({
        {"Tidak sesuai", 0.0},
        {"Sedikit", 0.2},
        {"Sangat Belum", 0.4},
        {"Belum Banyak", 0.6},
        {"Sedikit Banyak", 0.7},
        {"Banyak", 1.0},
        {"Extrem", 1.1}
    });

    // Data pelatihan
    std::vector<std::vector<float>> trainingInputs = {
        {4.5, 2.8, 0.9, 3.7, 3.1, 7.9},
        {1.2, 0.6, 0.3, 0.5, 0.2, 0.7},
        {0.4, 0.3, 0.2, 0.6, 0.5, 0.4},
        {5.1, 2.4, 1.2, 4.1, 3.2, 6.5},  
        {3.3, 1.7, 0.6, 3.4, 2.3, 6.1}
    };
    std::vector<std::string> trainingTargets = {"Banyak", "Sedikit", "Tidak sesuai", "Sedikit Banyak", "Banyak"};

    // Data testing
    std::vector<std::vector<float>> testInputs = {
        {4.5, 2.8, 0.9, 3.7, 3.1, 7.9},
        {1.2, 0.6, 0.3, 0.5, 0.2, 0.7},
        {0.4, 0.3, 0.2, 0.6, 0.5, 0.4}
    };
    std::vector<std::string> testTargets = {"Banyak", "Sedikit", "Tidak sesuai"};

    int numEpochs = 1000;
    float learningRate = 0.01;

    // Melatih model
    for (int epoch = 0; epoch < numEpochs; ++epoch) {
        fnn.train(trainingInputs, trainingTargets, numEpochs, learningRate); // Latih model

        if (epoch % 100 == 0) { // Evaluasi setiap 100 epoch
            float accuracy = fnn.evaluateAccuracy(testInputs, testTargets);
            float precision = fnn.evaluatePrecision(testInputs, testTargets);
            Serial.print("Epoch: ");
            Serial.print(epoch);
            Serial.print(" | Akurasi: ");
            Serial.print(accuracy);
            Serial.print("% | Presisi: ");
            Serial.print(precision);
            Serial.println("%");
        }
    }

    // Prediksi setelah pelatihan
    Serial.println("Hasil Prediksi setelah Pelatihan:");
    for (size_t i = 0; i < testInputs.size(); ++i) {
        String result = fnn.predictFNN(testInputs[i]).c_str(); // Prediksi hasil
        Serial.print("Input ke-");
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.println(result);
    }
}

void loop() {
    // Tidak ada loop untuk contoh ini
}
