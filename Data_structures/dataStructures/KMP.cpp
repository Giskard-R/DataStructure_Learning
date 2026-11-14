#if 0
#include <iostream>
#include <string>
#include <vector>


// 构建next数组，next[0]=0
std::vector<int> getNext(const std::string& pattern)
{
    int n = pattern.size();
    std::vector<int> next(n, 0);
    int j = 0; // j：最长相等前后缀长度，同时也是前缀指针
    // i从1开始，next[0]固定为0
    for (int i = 1; i < n; i++)
    {
        // 不相等，回退j，直到j=0或者字符相等
        while (j > 0 && pattern[i] != pattern[j])
        {
            j = next[j - 1];
        }
        if (pattern[i] == pattern[j])
        {
            j++;
        }
        next[i] = j;
    }
    return next;
}

// KMP匹配，返回首次匹配的起始下标，找不到返回-1
int kmpSearch(const std::string& text, const std::string& pattern)
{
    std::vector<int> next = getNext(pattern);
    int i = 0; // text指针
    int j = 0; // pattern指针
    int lenT = text.size();
    int lenP = pattern.size();
    while (i < lenT)
    {
        if (text[i] == pattern[j])
        {
            i++;
            j++;
        }
        else if (j > 0)
        {
            // 失配，j回退，核心：next[j-1]
            j = next[j - 1];
        }
        else
        {
            // j=0，第一个字符就不匹配，文本指针后移
            i++;
        }
        if (j == lenP)
        {
            // 匹配成功，返回起始位置
            return i - j;
        }
    }
    return -1;
}

int main()
{
    std::string s = "ababcabcabx";
    std::string p = "abcabx";
    std::vector<int> next = getNext(p);
    std::cout << "next数组：";
    for (int val : next)
    {
        std::cout << val << " ";
    }
    std::cout << "\n";
    int pos = kmpSearch(s, p);
    if (pos != -1)
        std::cout << "匹配起始下标：" << pos << std::endl;
    else
        std::cout << "未找到" << std::endl;
    return 0;
}
#elif 0

#include <vector>
#include <string>
#include <iostream>

class MatchString
{
private:
    std::string m_SString;

    std::vector<int> BuildNext(const std::string& T) const
    {
        const std::string& pattern = T;
        int n = pattern.size();
        std::vector<int> next(n, 0);
        int j = 0;

        for (int i = 1; i < n; i++)
        {
            while (j > 0 && pattern[i] != pattern[j])
            {
                j = next[j - 1];
            }
            if (pattern[j] == pattern[i])
                j++;
            next[i] = j;
        }
        return next;
    }

public:
    MatchString(const std::string& S) :m_SString(S){}

    int KMP(std::string& T) const
    {
        const std::string& S = m_SString;
        std::vector<int> next = BuildNext(T);
        int lenS = S.size();
        int lenT = T.size();
        int i = 0;
        int j = 0;

        while (i < lenS)
        {
            if (T[j] == S[i])
            {
                i++;
                j++;
            }
            else if (j > 0)
            {
                j = next[j - 1];
            }
            else
                i++;
            if (j == lenT)
                return i - j;
        }
        return -1;
    }
};

int main()
{
    std::string mainString;
    std::string matchString;
    
    std::cout << "Input the mainString: ";
    std::getline(std::cin, mainString);
    MatchString string(mainString);
    
    std::cout << "Input the matchString: ";
    std::getline(std::cin, matchString);

    int matchIdx = string.KMP(matchString);
    if (matchIdx != -1)
    {
        std::cout << "Match found, start indx: " << matchIdx << std::endl;
    }
    else
        std::cout << "Failed match.\n";
    std::cin.get();
}

#endif