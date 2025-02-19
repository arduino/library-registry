# FNN (Fuzzy Neural Network) Module Documentation

## Table of Contents
1. [Overview](#overview)
2. [Core Components](#core-components)
3. [Mathematical Foundation](#mathematical-foundation)
4. [Class Reference](#class-reference)
5. [Activation Functions](#activation-functions)
6. [Training Method](#training-methods)
7. [Evaluation Metrics](#evaluation-metrics)
8. [Implementation Guide](#implementation-guide)
9. [Example Usage](#example-usage)

## Overview
The FNN (Fuzzy Neural Network) module implements a hybrid intelligent system that combines neural networks with fuzzy logic principles. This implementation is specifically optimized for Arduino platforms, providing efficient computation while maintaining prediction accuracy.

## Core Components

### Class Structure
```cpp
class FNN {
private:
    std::vector<std::vector<float>> weights;    // Layer weights
    std::vector<float> biases;                  // Layer biases
    std::function<float(float)> activationFunction;  // Activation function
    std::map<std::string, float> fuzzyRules;    // Fuzzy ruleset
    ...
}
```

### Key Features
- Multi-layer neural network architecture
- Customizable activation functions
- Integrated fuzzy rule system
- Gradient descent-based training
- Comprehensive evaluation metrics

## Mathematical Foundation

### 1. Network Architecture

#### Input Layer
- Accepts normalized input vectors
- Dimension: `inputSize` (user-defined)
- Data type: `std::vector<float>`

#### Hidden Layer
Computation formula:

$$
h_j = f( \sum_{i=1}^{n} w_{ji} x_i + b_j)
$$

Where:
- $h_j$: Hidden layer neuron output
- $w_{ji}$: Connection weight
- $x_i$: Input value
- $b_j$: Bias term
- $f$: Activation function

#### Output Layer
Final computation:

$$o = f( \sum_{j=1}^{m} w_j h_j + b_o)$$

Parameters:
- $h_j$: Hidden layer outputs
- $w_j$: Output weights
- $b_o$: Output bias

### 2. Learning Process

#### Loss Function (MSE)

$$
L = \frac{1}{N} \sum_{i=1}^{N} (y_i - \hat{y}_i)^2
$$

Components:
- $y_i$: Expected output
- $\hat{y}_i$: Predicted output
- $N$: Sample size

#### Weight Update Rule

$$
w_{new} = w_{old} - \eta \frac{\partial L}{\partial w}
$$

Where:
- $\eta$: Learning rate
- $\frac{\partial L}{\partial w}$: Loss gradient

## Class Reference

### Constructor
```cpp
FNN(int inputSize = 3, float bias = 0.1, std::function<float(float)> activation = nullptr)
```
Parameters:
- `inputSize`: Number of input neurons
- `bias`: Initial bias value
- `activation`: Activation function (defaults to sigmoid)

### Public Methods

#### `setWeights`
```cpp
void setWeights(const std::vector<float>& newWeights)
```
Purpose: Sets network layer weights
Parameters:
- `newWeights`: Vector of weight values
Validation: Checks dimension compatibility

#### `setBiases`
```cpp
void setBiases(const std::vector<float>& newBiases)
```
Purpose: Sets layer biases
Parameters:
- `newBiases`: Vector of bias values
Validation: Verifies vector size

#### `setFuzzyRules`
```cpp
void setFuzzyRules(const std::map<std::string, float>& rules)
```
Purpose: Defines fuzzy classification rules
Parameters:
- `rules`: Map of linguistic terms to numeric values

### Training Methods

#### `train`
```cpp
void train(const std::vector<std::vector<float>>& inputs,
          const std::vector<std::string>& targets,
          int epochs = 100,
          float learningRate = 0.01)
```
Purpose: Trains the network
Parameters:
- `inputs`: Training data matrix
- `targets`: Expected outputs
- `epochs`: Training iterations
- `learningRate`: Learning rate

## Activation Functions

### 1. Sigmoid

$$
\sigma(x) = \frac{1}{1 + e^{-x}}
$$

Implementation:
```cpp
static float sigmoid(float x) {
    return 1.0 / (1.0 + exp(-x));
}
```
Use case: General classification tasks

### 2. Hyperbolic Tangent

$$
\tanh(x) = \frac{e^x - e^{-x}}{e^x + e^{-x}}
$$

Implementation:
```cpp
static float tanh(float x) {
    return std::tanh(x);
}
```
Use case: Normalized data ranges

### 3. Leaky ReLU

$$
f(x) = \begin{cases} x, & x > 0 \\ \alpha x, & x \leq 0 \end{cases}
$$

Implementation:
```cpp
static std::function<float(float)> leakyRelu(float alpha = 0.01)
```
Use case: Deep networks, preventing dying ReLU

## Evaluation Metrics

### Accuracy
```cpp
float evaluateAccuracy(const std::vector<std::vector<float>>& testInputs,
                      const std::vector<std::string>& expectedOutputs)
```
Calculation:
```
accuracy = (correct_predictions / total_predictions) * 100
```

### Precision
```cpp
float evaluatePrecision(const std::vector<std::vector<float>>& testInputs,
                       const std::vector<std::string>& expectedOutputs)
```
Calculation:
```
precision = (true_positives / (true_positives + false_positives)) * 100
```

## Implementation Guide

### Basic Setup
```cpp
#include "fnn.h"

FNN fnn(6);  // 6 input neurons
```

### Configuration
```cpp
// Weight initialization
fnn.setWeights({0.3, 0.5, 0.2, 0.4, 0.1, 0.6});

// Bias configuration
fnn.setBiases({0.1, 0.2});

// Activation function selection
fnn.setActivationFunction(FNN::sigmoid);

// Fuzzy rule definition
fnn.setFuzzyRules({
    {"Not Suitable", 0.0},
    {"Low", 0.2},
    {"High", 1.0}
});
```

### Training Configuration
```cpp
// Training parameters
int numEpochs = 1000;
float learningRate = 0.01;

// Training data format
std::vector<std::vector<float>> trainingInputs = {
    {4.5, 2.8, 0.9, 3.7, 3.1, 7.9},
    {1.2, 0.6, 0.3, 0.5, 0.2, 0.7}
};
std::vector<std::string> trainingTargets = {"High", "Low"};
```

## Example Usage

### Complete Arduino Implementation
```cpp
#include "fnn.h"

FNN fnn(6);

void setup() {
    Serial.begin(9600);
    
    // Configuration
    fnn.setWeights({0.3, 0.5, 0.2, 0.4, 0.1, 0.6});
    fnn.setBiases({0.1, 0.2});
    fnn.setActivationFunction(FNN::sigmoid);
    
    // Fuzzy rules
    fnn.setFuzzyRules({
        {"Not Suitable", 0.0},
        {"Low", 0.2},
        {"Very Low", 0.4},
        {"Below Average", 0.6},
        {"Above Average", 0.7},
        {"High", 1.0},
        {"Extreme", 1.1}
    });

    // Training data
    std::vector<std::vector<float>> trainingInputs = {
        {4.5, 2.8, 0.9, 3.7, 3.1, 7.9},
        {1.2, 0.6, 0.3, 0.5, 0.2, 0.7},
        {0.4, 0.3, 0.2, 0.6, 0.5, 0.4}
    };
    std::vector<std::string> trainingTargets = {
        "High", "Low", "Not Suitable"
    };

    // Training
    int numEpochs = 1000;
    float learningRate = 0.01;
    
    // Train and evaluate
    for (int epoch = 0; epoch < numEpochs; ++epoch) {
        fnn.train(trainingInputs, trainingTargets, 1, learningRate);
        
        if (epoch % 100 == 0) {
            float accuracy = fnn.evaluateAccuracy(trainingInputs, trainingTargets);
            Serial.print("Epoch: ");
            Serial.print(epoch);
            Serial.print(" Accuracy: ");
            Serial.println(accuracy);
        }
    }
}

void loop() {
    // Prediction example
    std::vector<float> newInput = {4.5, 2.8, 0.9, 3.7, 3.1, 7.9};
    String prediction = fnn.predictFNN(newInput).c_str();
    Serial.println(prediction);
    delay(1000);
}
```

### Performance Optimization
1. Use fixed-point arithmetic where possible
2. Minimize dynamic memory allocation
3. Optimize matrix operations
4. Cache frequently used calculations

## Error Handling
The module includes comprehensive error checking:
1. Input validation
2. Memory allocation verification
3. Dimension compatibility checks
4. Fuzzy rule consistency validation

## Contributing
Contributions are welcome. Please follow the standard pull request process:
1. Fork the repository
2. Create your feature branch
3. Commit your changes
4. Push to the branch
5. Create a Pull Request

## Support
For issues and feature requests, please create an issue in the repository.

## Author
1. GALIH RIDHO UTOMO
