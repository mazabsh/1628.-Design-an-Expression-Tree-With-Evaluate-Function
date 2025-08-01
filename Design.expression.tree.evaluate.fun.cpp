#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <stdexcept>
using namespace std;

class Node {
public:
    virtual ~Node() {}
    virtual int evaluate() const = 0;
};

class NumNode : public Node {
    int val;
public:
    NumNode(int _val) : val(_val) {}
    int evaluate() const override {
        return val;
    }
};

class OpNode : public Node {
    char op;
    Node* left;
    Node* right;
public:
    OpNode(char _op, Node* _left, Node* _right) : op(_op), left(_left), right(_right) {}
    int evaluate() const override {
        int l = left->evaluate();
        int r = right->evaluate();
        switch (op) {
            case '+': return l + r;
            case '-': return l - r;
            case '*': return l * r;
            case '/': return l / r;
            default: throw invalid_argument("Unsupported operator");
        }
    }
    ~OpNode() {
        delete left;
        delete right;
    }
};

class TreeBuilder {
public:
    Node* buildTree(vector<string>& postfix) {
        stack<Node*> st;
        for (string& p : postfix) {
            if (isdigit(p[0]) || (p.size() > 1 && p[0] == '-')) {
                st.push(new NumNode(stoi(p)));
            } else {
                Node* right = st.top(); st.pop();
                Node* left = st.top(); st.pop();
                st.push(new OpNode(p[0], left, right));
            }
        }
        return st.top();
    }
};

int main() {
    vector<string> postfix = {"4", "5", "7", "2", "+", "-", "*"};
    TreeBuilder builder;
    Node* root = builder.buildTree(postfix);
    cout << "Result: " << root->evaluate() << endl; // Expected: -12
    delete root;
    return 0;
}
