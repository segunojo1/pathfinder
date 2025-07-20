#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cstdlib>
#include <sstream>

using namespace std;

// -----------------------------
// Encapsulation & Abstraction
// -----------------------------
class QueryParser {
private:
    string rawQuery;
    map<string, string> params;

    string urlDecode(const string& str) {
        string decoded;
        for (size_t i = 0; i < str.length(); ++i) {
            if (str[i] == '+') decoded += ' ';
            else if (str[i] == '%' && i + 2 < str.length()) {
                int val;
                sscanf(str.substr(i + 1, 2).c_str(), "%x", &val);
                decoded += static_cast<char>(val);
                i += 2;
            } else {
                decoded += str[i];
            }
        }
        return decoded;
    }

public:
    QueryParser(const string& query) : rawQuery(query) {
        size_t pos = 0, amp, eq;
        while (pos < rawQuery.length()) {
            amp = rawQuery.find("&", pos);
            eq = rawQuery.find("=", pos);
            if (eq != string::npos) {
                string key = rawQuery.substr(pos, eq - pos);
                string value = (amp == string::npos)
                    ? rawQuery.substr(eq + 1)
                    : rawQuery.substr(eq + 1, amp - eq - 1);
                params[key] = urlDecode(value);
            }
            if (amp == string::npos) break;
            pos = amp + 1;
        }
    }

    map<string, string> getParams() const {
        return params;
    }
};

// ------------------
// Inheritance + Styling Renderer
// ------------------
class ResultRenderer {
public:
    virtual void render(const string& recommendation, const vector<int>& scores, bool tie) {
        cout << "Content-type: text/html\n\n";
        cout << R"====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>🌟 Pathfinder Result</title>
    <link href="https://fonts.googleapis.com/css2?family=Inter:wght@400;600&display=swap" rel="stylesheet">
    <style>
        body {
            font-family: 'Inter', sans-serif;
            background: url('https://images.unsplash.com/photo-1558024920-b62b376f8e48?auto=format&fit=crop&w=1350&q=80') no-repeat center center fixed;
            background-size: cover;
            margin: 0;
            padding: 0;
        }
        .container {
            max-width: 600px;
            margin: 80px auto;
            background: rgba(255, 255, 255, 0.9);
            padding: 30px 40px;
            border-radius: 16px;
            box-shadow: 0 8px 20px rgba(0,0,0,0.2);
        }
        h1 {
            text-align: center;
            color: #2c3e50;
        }
        ul {
            padding-left: 20px;
        }
        li {
            margin-bottom: 10px;
        }
        strong {
            color: #27ae60;
        }
        a {
            display: inline-block;
            margin-top: 30px;
            background: #2980b9;
            color: white;
            padding: 12px 24px;
            border-radius: 8px;
            text-decoration: none;
            transition: background 0.3s;
        }
        a:hover {
            background: #1e6aa7;
        }
    </style>
</head>
<body>
<div class="container">
    <h1>🌟 Pathfinder Recommendation</h1>
)====";

        cout << "<p>Scores:</p><ul>";
        cout << "<li>Science: " << scores[0] << "</li>";
        cout << "<li>Commercial: " << scores[1] << "</li>";
        cout << "<li>Art: " << scores[2] << "</li></ul>";

        if (tie)
            cout << "<p>You seem to enjoy many subjects! You could explore <strong>Science</strong>, <strong>Commercial</strong>, or <strong>Art</strong>.</p>";
        else if (recommendation.empty())
            cout << "<p>No answers were submitted. Please go back and try again.</p>";
        else
            cout << "<p>Your recommended class is: <strong>" << recommendation << "</strong></p>";

        cout << "<a href='/pathfinder/public_html/index.html'>🔙 Try Again</a>";
        cout << "</div></body></html>";
    }

    virtual ~ResultRenderer() {}
};

// ------------------
// Polymorphism Option ,, inheritance
// ------------------
class JSONRenderer : public ResultRenderer {
public:
    void render(const string& recommendation, const vector<int>& scores, bool tie) override {
        cout << "Content-type: application/json\n\n";
        cout << "{";
        cout << "\"science\":" << scores[0] << ",";
        cout << "\"commercial\":" << scores[1] << ",";
        cout << "\"art\":" << scores[2] << ",";
        cout << "\"recommendation\":\"" << (tie ? "Multiple interests" : recommendation) << "\"";
        cout << "}";
    }
};

// ------------------
// App Controller
// ------------------
class PathfinderApp {
private:
    vector<string> categories = {"Science", "Commercial", "Art"};
    vector<int> scores = {0, 0, 0};

public:
    void run() {
        string query = getenv("QUERY_STRING") ? getenv("QUERY_STRING") : "";
        QueryParser parser(query);
        map<string, string> data = parser.getParams();

        for (int i = 1; i <= 5; ++i) {
            string key = "q" + to_string(i);
            if (data.count(key)) {
                if (data[key] == "a") scores[0]++;
                else if (data[key] == "b") scores[1]++;
                else if (data[key] == "c") scores[2]++;
            }
        }

        int maxScore = scores[0], bestIndex = 0;
        bool tie = false;

        for (int i = 1; i < scores.size(); ++i) {
            if (scores[i] > maxScore) {
                maxScore = scores[i];
                bestIndex = i;
                tie = false;
            } else if (scores[i] == maxScore && maxScore > 0) {
                tie = true;
            }
        }

        string recommendation = (maxScore == 0) ? "" : categories[bestIndex];

        ResultRenderer* renderer = new ResultRenderer();
        renderer->render(recommendation, scores, tie);
        delete renderer;
    }
};

int main() {
    PathfinderApp app;
    app.run();
    return 0;
}
