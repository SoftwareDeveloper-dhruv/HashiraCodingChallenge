Secret Sharing Solver
A simple C++ implementation to solve Shamir's Secret Sharing scheme using basic mathematical operations.
📋 Problem Description
Given a set of points representing shares in Shamir's Secret Sharing scheme, this program reconstructs the original polynomial and finds the constant term (the secret) using elementary mathematics.
🚀 Features

Converts numbers from different bases (binary, hex, etc.) to decimal
Uses basic interpolation to find polynomial coefficients
Automatically processes JSON test case files
Simple, student-friendly code structure
No external libraries required

📁 Files

main.cpp - Main program source code
testcase1.json - First test case with 4 shares
testcase2.json - Second test case with 10 shares

🛠️ Compilation & Usage
Prerequisites

C++ compiler (g++, clang++, etc.)
JSON test case files in the same directory

Compile
bashg++ -o solver main.cpp
Run
bash./solver
The program automatically processes both testcase1.json and testcase2.json files and outputs the secret for each test case.
📊 Expected Output
3
39932017850922179524
📖 How It Works

Base Conversion: Converts share values from various number bases to decimal
Point Collection: Extracts (x, y) coordinate pairs from JSON data
Polynomial Reconstruction: Uses basic mathematical interpolation
Secret Extraction: Evaluates the polynomial at x=0 to find the constant term

🧮 Mathematical Approach
The program uses elementary mathematics to solve the system:

For each point (xi, yi), calculate its contribution to f(0)
Use the formula: weight = Π(0 - xj)/(xi - xj) for j ≠ i
Sum up: secret = Σ(yi × weight)

📝 JSON Input Format
json{
  "keys": {
    "n": 4,
    "k": 3
  },
  "1": {
    "base": "10",
    "value": "4"
  },
  "2": {
    "base": "2",
    "value": "111"
  }
}
Where:

n: Total number of shares
k: Minimum shares needed to reconstruct secret
Numbered entries: Individual shares with base and encoded value

🤝 Contributing
Feel free to fork this repository and submit pull requests for improvements.
📄 License
This project is open source and available under the MIT License.
🎯 Use Cases

Cryptography assignments
Understanding secret sharing schemes
Learning polynomial interpolation
Educational demonstrations
