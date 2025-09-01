#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

long long baseToDecimal(const string& value, int base) {
    long long result = 0;
    long long power = 1;
    
    for (int i = value.length() - 1; i >= 0; i--) {
        char digit = value[i];
        int digitValue;
        
        if (digit >= '0' && digit <= '9') {
            digitValue = digit - '0';
        } else if (digit >= 'a' && digit <= 'z') {
            digitValue = digit - 'a' + 10;
        } else if (digit >= 'A' && digit <= 'Z') {
            digitValue = digit - 'A' + 10;
        }
        
        result += digitValue * power;
        power *= base;
    }
    
    return result;
}

long long findConstant(const vector<pair<long long, long long>>& points, int k) {
    long long result = 0;
    
    for (int i = 0; i < k; i++) {
        long long xi = points[i].first;
        long long yi = points[i].second;
        
        long long numerator = 1;
        long long denominator = 1;
        
        for (int j = 0; j < k; j++) {
            if (i != j) {
                long long xj = points[j].first;
                numerator *= (0 - xj);
                denominator *= (xi - xj);
            }
        }
        
        result += yi * numerator / denominator;
    }
    
    return result;
}

string extractValue(const string& line, const string& key) {
    size_t pos = line.find("\"" + key + "\":");
    if (pos == string::npos) return "";
    
    pos = line.find("\"", pos + key.length() + 3);
    if (pos == string::npos) return "";
    
    size_t end = line.find("\"", pos + 1);
    if (end == string::npos) return "";
    
    return line.substr(pos + 1, end - pos - 1);
}

int extractNumber(const string& line, const string& key) {
    size_t pos = line.find("\"" + key + "\":");
    if (pos == string::npos) return 0;
    
    pos = line.find(":", pos);
    if (pos == string::npos) return 0;
    
    pos++;
    while (pos < line.length() && (line[pos] == ' ' || line[pos] == '\t')) pos++;
    
    string numStr = "";
    while (pos < line.length() && line[pos] >= '0' && line[pos] <= '9') {
        numStr += line[pos];
        pos++;
    }
    
    return numStr.empty() ? 0 : stoi(numStr);
}

void processJsonFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return;
    }
    
    string line;
    int n = 0, k = 0;
    vector<pair<long long, long long>> points;
    
    while (getline(file, line)) {
        // Extract n and k from keys section
        if (line.find("\"n\":") != string::npos) {
            n = extractNumber(line, "n");
        }
        if (line.find("\"k\":") != string::npos) {
            k = extractNumber(line, "k");
        }
        
        // Extract numbered entries
        for (int i = 1; i <= 20; i++) {
            string key = to_string(i);
            if (line.find("\"" + key + "\":") != string::npos) {
                string currentLine = line;
                string base_str, value_str;
                
                size_t basePos = currentLine.find("\"base\":");
                size_t valuePos = currentLine.find("\"value\":");
                
                if (basePos != string::npos) {
                    base_str = extractValue(currentLine, "base");
                }
                if (valuePos != string::npos) {
                    value_str = extractValue(currentLine, "value");
                }
                
                while ((base_str.empty() || value_str.empty()) && getline(file, currentLine)) {
                    if (base_str.empty()) {
                        base_str = extractValue(currentLine, "base");
                    }
                    if (value_str.empty()) {
                        value_str = extractValue(currentLine, "value");
                    }
                    if (currentLine.find("}") != string::npos && !base_str.empty() && !value_str.empty()) {
                        break;
                    }
                }
                
                if (!base_str.empty() && !value_str.empty()) {
                    int base = stoi(base_str);
                    long long decimalValue = baseToDecimal(value_str, base);
                    points.push_back({i, decimalValue});
                }
            }
        }
    }
    
    file.close();
    
    if (points.size() >= k) {
        vector<pair<long long, long long>> selectedPoints(points.begin(), points.begin() + k);
        cout << findConstant(selectedPoints, k) << endl;
    }
}

int main() {
    // Process both test cases automatically
    processJsonFile("testcase1.json");
    processJsonFile("testcase2.json");
    
    return 0;
}