#include <stack>

class MinStack {
private:
    std::stack<int> m_StVal;
    std::stack<int> m_StMin;
public:
    MinStack() {

    }

    void push(int value) {
        m_StVal.push(value);

        if (m_StMin.empty() || value <= m_StMin.top())
            m_StMin.push(value);
    }

    void pop() {
        if (m_StMin.top() == m_StVal.top())
            m_StMin.pop();

        m_StVal.pop();
    }

    int top() {
        return m_StVal.top();
    }

    int getMin() {
        return m_StMin.top();
    }
};
