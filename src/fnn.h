#ifndef FNN_H
#define FNN_H

#include <cmath>
#include <vector>
#include <functional>
#include <map>
#include <string>

class FNN {
private:
    std::vector<std::vector<float>> weights; // Bobot untuk tiap layer
    std::vector<float> biases;              // Bias untuk tiap layer
    std::function<float(float)> activationFunction; // Fungsi aktivasi
    std::map<std::string, float> fuzzyRules; // Aturan fuzzy

    float computeLoss(const std::vector<float>& predicted, const std::vector<float>& expected);

    // Defuzzifikasi
    std::string defuzzify(float fuzzyOutput);

public:
    FNN(int inputSize = 3, float bias = 0.1, std::function<float(float)> activation = nullptr);

    // Set bobot
    void setWeights(const std::vector<float>& newWeights);

    // Set bias
    void setBiases(const std::vector<float>& newBiases);

    // Set fungsi aktivasi
    void setActivationFunction(std::function<float(float)> activation);

    // Set fuzzy rules
    void setFuzzyRules(const std::map<std::string, float>& rules);

    // Prediksi FNN
    std::string predictFNN(const std::vector<float>& inputs);
    
    // Fungsi pelatihan
    void train(const std::vector<std::vector<float>>& inputs, const std::vector<std::string>& targets, int epochs = 100, float learningRate = 0.01);

    // Evaluasi
    // Evaluasi Akurasi
    float evaluateAccuracy(const std::vector<std::vector<float>>& testInputs, const std::vector<std::string>& expectedOutputs);

    // Evaluasi Presisi
    float evaluatePrecision(const std::vector<std::vector<float>>& testInputs, const std::vector<std::string>& expectedOutputs);

    // Fungsi aktivasi yang disediakan
    static float sigmoid(float x);
    static float tanh(float x);
    static std::function<float(float)> leakyRelu(float alpha = 0.01);
    static std::function<float(float)> elu(float alpha = 1.0);
    static float softplus(float x);
};

#endif
