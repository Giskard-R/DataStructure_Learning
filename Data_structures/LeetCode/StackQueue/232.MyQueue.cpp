#include <stack>

class MyQueue {
private:
    std::stack<int> m_inStack;
    std::stack<int> m_outStack;

    void Transfor()
    {
        if (m_outStack.empty())
        {
            while(!m_inStack.empty())
            {
                int val = m_inStack.top();
                m_inStack.pop();
                m_outStack.push(val);
            }
        }
    }

public:
    MyQueue() {

    }

    void push(int x) {
        m_inStack.push(x);
    }

    int pop() {
        Transfor();
        int val = m_outStack.top();
        m_outStack.pop();
        return val;
    }

    int peek() {
        Transfor();
        return m_outStack.top();
    }

    bool empty() {
        return m_inStack.empty() && m_outStack.empty();
    }
};