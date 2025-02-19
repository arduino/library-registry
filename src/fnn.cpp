#include "fnn.h"
#include <Arduino.h>

// Konstruktor
FNN::FNN(int inputSize, float bias, std::function<float(float)> activation)
    : weights(2, std::vector<float>(inputSize, 0.0)), biases(2, bias), activationFunction(activation) {
    if (!activationFunction) {
        activationFunction = sigmoid; // Default fungsi aktivasi adalah sigmoid
    }
}

// Set bobot
void FNN::setWeights(const std::vector<float>& newWeights) {
    if (newWeights.size() == weights[0].size()) {
        weights[0] = newWeights;
    }
}

// Set bias
void FNN::setBiases(const std::vector<float>& newBiases) {
    if (newBiases.size() == biases.size()) {
        biases = newBiases;
    }
}

// Set fungsi aktivasi
void FNN::setActivationFunction(std::function<float(float)> activation) {
    activationFunction = activation;
}

// Set fuzzy rules
void FNN::setFuzzyRules(const std::map<std::string, float>& rules) {
    fuzzyRules = rules;
}

// Fungsi aktivasi: Sigmoid
float FNN::sigmoid(float x) {
    return 1.0 / (1.0 + exp(-x));
}

// Fungsi aktivasi: Tanh
float FNN::tanh(float x) {
    return std::tanh(x);
}

// Fungsi aktivasi: Leaky ReLU
std::function<float(float)> FNN::leakyRelu(float alpha) {
    return [alpha](float x) { return (x > 0) ? x : alpha * x; };
}

// Fungsi aktivasi: ELU
std::function<float(float)> FNN::elu(float alpha) {
    return [alpha](float x) { return (x > 0) ? x : alpha * (exp(x) - 1); };
}

// Fungsi aktivasi: Softplus
float FNN::softplus(float x) {
    return log(1 + exp(x));
}

// Defuzzifikasi
std::string FNN::defuzzify(float fuzzyOutput) {
    for (const auto& rule : fuzzyRules) {
        if (fuzzyOutput <= rule.second) {
            return rule.first;
        }
    }
    return "Undefined";
}

// Compute Loss
float FNN::computeLoss(const std::vector<float>& predicted, const std::vector<float>& expected) {
    float loss = 0.0f;
    for (size_t i = 0; i < predicted.size(); ++i) {
        loss += pow(predicted[i] - expected[i], 2);
    }
    return loss / predicted.size();
}

// Train
void FNN::train(const std::vector<std::vector<float>>& inputs, const std::vector<std::string>& targets, int epochs, float learningRate) {
    for (int epoch = 0; epoch < epochs; ++epoch) {
        for (size_t i = 0; i < inputs.size(); ++i) {
            float hiddenSum = biases[0];
            for (size_t j = 0; j < weights[0].size(); ++j) {
                hiddenSum += inputs[i][j] * weights[0][j];
            }
            float hiddenOutput = activationFunction(hiddenSum);

            float outputSum = hiddenOutput * weights[1][0] + biases[1];
            float output = activationFunction(outputSum);

            float outputError = fuzzyRules[targets[i]] - output;
            weights[1][0] += learningRate * outputError * hiddenOutput;
            biases[1] += learningRate * outputError;

            float hiddenError = outputError * weights[1][0];
            for (size_t j = 0; j < weights[0].size(); ++j) {
                weights[0][j] += learningRate * hiddenError * inputs[i][j];
            }
            biases[0] += learningRate * hiddenError;
        }
    }
}

// Predict
std::string FNN::predictFNN(const std::vector<float>& inputs) {
    float hiddenSum = biases[0];
    for (size_t j = 0; j < weights[0].size(); ++j) {
        hiddenSum += inputs[j] * weights[0][j];
    }
    float hiddenOutput = activationFunction(hiddenSum);

    float outputSum = hiddenOutput * weights[1][0] + biases[1];
    float output = activationFunction(outputSum);

    return defuzzify(output);
}
// Evaluasi Akurasi
float FNN::evaluateAccuracy(const std::vector<std::vector<float>>& testInputs, const std::vector<std::string>& expectedOutputs) {
    int correctPredictions = 0;

    for (size_t i = 0; i < testInputs.size(); ++i) {
        std::string predictedOutput = predictFNN(testInputs[i]);
        if (predictedOutput == expectedOutputs[i]) {
            correctPredictions++;
        }
    }

    float accuracy = (float)correctPredictions / testInputs.size();
    return accuracy * 100.0f; // Hasil dalam persen
}

// Evaluasi Presisi
float FNN::evaluatePrecision(const std::vector<std::vector<float>>& testInputs, const std::vector<std::string>& expectedOutputs) {
    int truePositives = 0;
    int falsePositives = 0;

    for (size_t i = 0; i < testInputs.size(); ++i) {
        std::string predictedOutput = predictFNN(testInputs[i]);

        if (predictedOutput == expectedOutputs[i]) {
            truePositives++;
        } else if (fuzzyRules.find(predictedOutput) != fuzzyRules.end()) {
            falsePositives++;
        }
    }

    if (truePositives + falsePositives == 0) {
        return 0.0f; // Hindari pembagian dengan nol
    }

    float precision = (float)truePositives / (truePositives + falsePositives);
    return precision * 100.0f; // Hasil dalam persen
}
