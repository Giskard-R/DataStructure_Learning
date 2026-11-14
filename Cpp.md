# 变量

- $1byte=8bit$

- float类型需在数值后加f或F

- bool类型占1byte

- `sizeof(Type)`返回类型所占字节数

---

# 函数

- 一次定义, 多次声明

- 只有main函数默认`return 0;`

---

# 头文件

- `#pragma once`
  
  - 防止头文件重复包含(头文件保护)

- ```cpp
  #ifndef 宏名 //if not define 执行下方代码
  #define 宏名
  ...
  #endif //结束标识
  ```

- `#include ""`与`#include <>`
  
  - " "在当前目录查找
  
  - < >在系统目录查找

- C的标准库有.h拓展, Cpp的标准库没有, 这种差异是为了区别C与Cpp

---

# 在Visual Studio中调试代码

- 断点: 程序运行到断点时将停止运行

- 调试时确保在debug模式下运行

---

# C++的输入输出

- 头文件`#include<iostream>`
  
  - 一般配合`using namespace std;`

- 输入`cin>>`自动跳过空格, 回车, Tab. 遇到空白停止读取

- `endl`输出换行与刷新缓冲区; `\n`只换行, 不刷新, 效率更高

- 读取整行带空格字符串: `getline(cin, s);`
  
  - `cin`读完数字后会残留换行, 直接`getline`会读空, 需要吃掉换行
  
  ```cpp
  #include<iostream>
  using namespace std;
  #include<string>
  
  int main()
  {
  string s;
  cin.ignore(); //丢弃缓冲区换行
  getline(cin, s);
  }
  ```
  
  - 使用`string`需要包含`#include<string>`

- `std::cout`的格式化输出
  
  - `setw(n)`: 设置输出域宽占n个字符
  
  - `setfill('c')`: 设置填充字符
  
  - `setprecision(n)`: 设置精度
  
  - `fixed`: 固定小数模式
  
  - `hex/oct/dec`: 十六进制/八进制/十进制
  
  - `left/right`: 左对齐/右对齐
  
  - 注意事项:
    
    - `stew()`域宽: 只对紧跟它的一项生效, 用完就失效
    
    - `setfill()`填充字符: 持久有效, 经常与`setw()`搭配
      
      ```cpp
      #include<iostream>
      using namespace std;
      
      int main()
      {
          int a = 12;
          cout << setfill('0') << setw(5) << a << endl;
          //输出: 00012
      }
      ```
    
    - `setprecision()`与`fixed`
      
      - 不加`fixed`: $setprecision(n)=有效数字总位数$
      
      - 加`fixed`: $setprecision(n)=小数点后保留n位小数$
      
      ```cpp
      #include<iostream>
      using namespace std;
      
      int main()
      {
          double pi = 3.1415926;
          cout << setprecision(3) << pi << endl;
          //输出: 3.14
          cout << fixed << setprecision(3) << pi << endl;
          //输出: 3.142
      }
      ```

---

# 引用类型

- 引用就是给现有的变量起个别名, 变量和它的引用指向相同的地址

- 声明引用类型的同时必须初始化

---

# 类

- 类可以包含函数, C语言的结构体不能声明和定义函数, Cpp的结构体可以声明和定义函数
  
  ```cpp
  class Player
  {
  public:
      int x, y;
      int speed;
  
      void Move(int xa, int ya)
      {
          x += xa * speed;
          y += ya * speed;
      }
  };
  
  int main()
  {
      Player Giskard;
      Player.Move(1, -1);
  }
  ```

- 类可以使代码模块化, 增加可读性, 方便后期维护

---

# 类与结构体对比

- 类和结构体的区别: 唯一的区别就是其成员的默认属性, class为private, struct为public

---

# 写一个Cpp类

```cpp
class Log
{
public:
    const int LogLevelError = 0;
    const int LogLevelWarning = 1;
    const int LogLevelInfo = 2; //日志信息追踪
private:
    int m_LogLevel = LogLevelInfo;
public:
    void SetLevel(int level)
    {
        m_LogLevel = level;
    }

    void Warn(const char* message)
    {
        if(m_LogLevel >= LogLevelWarning)
            std::cout << "[WARNING]:" << message << std::endl;
    }

    void Error(const char* message)
    {
        if(m_LogLevel >= LogLevelError)
            std::cout << "[ERROR]:" << message << std::endl;
    }

    void Info(const char* message)
    {
        if(m_LogLevel >= LogLevelInfo)
            std::cout << "[Info]:" << message << std::endl;
    }
};

int main()
{
    Log log;
    //只有警告或更重要的信息, 比如警告或错误才会被打印出来
    log.SetLevel(log.LogLevelInfo);
    log.Error("Hello!");
    log.Warn("Hello!");
    log.Info("Hello!");
    std::cin.get();
}
```

---

# C++中的静态(static)

- 类和结构体外的静态
  
  - static使变量只在当前单元可见, 防止链接时跨单元使用

- 类和结构体中的静态
  
  - static成员变量全局只有一份, 所有对象共用
  
  - static成员变量类内声明, 类外初始化(const static整型除外)
  
  - 调用方式:`对象.函数()`或`类名::函数()`, 不需要new/创建对象
  
  - 静态成员函数没有this指针, 不能操作非静态成员
  
  - 访问权限依然生效: private静态成员外部不能直接访问

- 局部静态(Local Static)
  
  - 生存期基本上相当于整个程序的生存期, 但作用域被限制在函数内

---

# C++的枚举

- 弱类型

- 问题:
  
  - 名字直接暴露到外层作用域
  
  - 可以隐式转int

```cpp
enum Example : ElemType //必须是整数
{
    A, B, C
};
```

- 强类型(推荐)
  - 强作用域: 枚举名字必须带`Example::`, 不会污染外部命名空间
  - 强类型: 禁止隐式转int

```cpp
enum class Example : ElemType
{
    A, B, C
};

int main()
{
    Example c = Example::A;
    int x = static_cast<int>(c);
}
```

- 默认第一个是0, 然后逐个递增

---

# C++构造函数

- 构造函数是一种特殊类型的方法, 在每次实例化对象时运行
  
  ```cpp
  class Entity
  {
  public:
      float x, y;
      Entity()
      {
          x = 0.0f;
          y = 0.0f;
      }
  
      Entity(float a, float b) //方法的重载
      {
          x = a;
          y = b;
      }
  
      void Print()
      {
          std:;cout << x << ', ' << y << std::endl;
      }
  }
  ```

- C++程序有默认构造函数, 如果不希望创建对象可以做如下操作
  
  ```cpp
  class Log
  {
  public:
      Log() = delete;
  }
  
  int main()
  {
      Log i; //不允许
  }
  ```

---

# C++的析构函数

- 构造函数与析构函数在声明和定义时的唯一区别, 就是放在析构函数前面的波浪号
  
  ```cpp
  class Entity
  {
  public:
      float x, y;
      Entity()
      {
          x = 0.0f;
          y = 0.0f;
          std::cout << "Created Entity!" << std::endl;
      }
  
      ~Entity()
      {
          std::cout << "Destroyed Entity!" << std::endl;
  
      }    
  
      void Print()
      {
          std::cout << x << ', ' << y << std::endl;
      }
  };
  
  void Function()
  {
      Entity e;
      e.Print();
  }
  
  int main()
  {
      Function();
      std::cin.get();
  }
  ```
  
  - 只有当主函数退出时, 析构函数才会被调用

- 析构函数的作用: 如果在构造函数中调用了特定的初始化代码, 你可能想要在析构函数中, 卸载或销毁所有这些东西. 因为如果你不这样做, 你可能会造成内存泄漏.

---

# C++的继承

- 继承的作用: 可以帮助我们避免代码重复
  
  ```cpp
  #include<iostream>
  
  class Entity
  {
  public:
      float X, Y;
  
      void Move(float xa, float ya)
      {
          X += xa;
          Y += ya;
      }
  };
  
  class Player : public Entity //Player继承Entity
  {
      const char* Name;
  
      void PrintName()
      {
          std::cout << Name << std::endl;
      }
  };
  
  int main()
  {
      std::cin.get();
  }
  ```

---

# C++的虚函数

- 虚函数允许我们在子类中重写方法
  
  ```cpp
  #include<iostream>
  #include<string>
  
  class Entity
  {
  public:
      virtual std::string GetName()
      {
          return "Entity"
      }
  };
  
  class Player : public Entity
  {
  private:
      std::string m_Name;
  
  public:
      Player(const std::string& name)
          : m_Name(name) {}
  
      std::string GetName() override //方法重写
      {
          return m_Name;
      }
  };
  
  void PrintName(Entity* entity)
  {
      std::cout << entity->GetName() << std::endl;
  }
  
  int main()
  {
      Entity* e = new Entity();
      PrintName(e);
  
      Player* p = new Player("Giskard");
      PrintName(p);
  
      Entity* entity = p; //实际为子类Player的实例
      std::cout << entity->GetName() << std::endl;
  
      std::cin.get();
  }
  ```

- 虚函数的缺点
  
  - 需要额外的内存来存储v表, 这样我们就可以分配到正确的函数
  
  - 每次调用虚函数时, 我们需要遍历这个表, 来确定要映射到哪个函数, 这是额外的性能损失

---

# C++的接口(纯虚函数)

- 纯虚函数允许我们在基类中定义一个没有实现的函数, 然后强制子类去实现该函数
  
  ```cpp
  #include<iostream>
  #include<string>
  
  class Printable
  {
  public:
      virtual std::string GetClassName() = 0; //接口的定义
  };
  
  class Entity : public Printable
  {
  public:
      virtual std::string GetName()
      {
          return "Entity";
      }
  
      std::string GetClassName() override
      {
          return "Entity";
      }
  };
  
  class Player : public Entity
  {
  private:
      std::string m_Name;
  
  public:
      Player(const std::string& name)
          : m_Name(name) {}
  
      std::string GetName() override //方法重写
      {
          return m_Name;
      }
  
      std::string GetClassName() override
      {
          return "Player";
      }
  
  };
  
  void PrintName(Entity* entity)
  {
      std::cout << entity->GetName() << std::endl;
  }
  
  void Print(Printable* obj)
  {
      std::cout << obj->GetClassName() << std::endl;
  }
  
  int main()
  {
      Entity* e = new Entity();
      PrintName(e);
  
      Player* p = new Player("Giskard");
      PrintName(p);
  
      Print(e);
      Print(p);
  
      std::cin.get();
  
  }
  ```

- 只有在实现了所有纯虚函数之后, 才能够实例化. 

---

# C++的可见性

- 可见性是一个属于面向对象编程的概念, 它指的是类的某些成员或方法实际上有多可见. 可见性是指谁能看到它们, 谁能调用它们.

- 可见性是对程序实际运行方式完全没有影响的东西, 对程序性能或类似的东西也没有影响, 它纯粹是语言中存在的东西, 让你能够写出更好的代码或者帮助你组织代码

- 三个可见性修饰符: `private`, `protected`和`public`
  
  ```cpp
  #include<iostream>
  #include<string>
  
  class Entity
  {
  protected: //本类和层次结构中的所有子类都可以调用
      int X, Y;
      void Print() {}
  public:
      Entity()
      {
          X = 0;
      }
  };
  
  class Player : public Entity
  {
  
  };
  
  int main()
  {
      std::cin.get();
  }
  ```
  
  - `private`: 只有本类和友元可以调用
  
  - `protected`比`private`更可见, 比`public`更不可见, 本类和层次结构中的所有子类都可以调用
  
  - `public`: 都可以调用

---

# C++的数组

- 指针基本上是C++数组工作方式的基础
  
  ```cpp
  #include<iostream>
  
  int main()
  {
      int example[5]; //局部变量是在栈上创建的数组, 在最后的花括号销毁
      int* another = new int[5]; //指针类是在堆上创建的数组, 直到我们程序把它销毁之前, 都处于活动状态
      delete[] anther; //需要用delete主动销毁
  
      std::cin.get();
  }
  ```

- 使用`#include <array>`头文件创建数组
  
  ```cpp
  #include <array>
  
  int main()
  {
      std::array<int, 5> another;
      for(int i = 0;i < another.size();i++) //another.size()返回数组元素个数
          another[i] = 2;
  }
  ```

---

# C++的字符串

- 字符串本质上是一个接一个字符的一组字符, 终止符`\0`
  
  ```cpp
  #include <iostream>
  #include <string>
  
  void PrintString(const std::string& string)
  {
      std::cout << string << std::endl;
  }
  
  int main()
  {
      const char* name0 = "Giskard";
      std::string name1 = "Giskard";
      char name2[] = "Giskard";
      //字符串的拼接
      std::string name = std::string("Giskard") + "hello!";
      //std::string::npos表示空的
      bool contains = name.find("is") != std::string::npos;
      std::cin.get();
  }
  ```
  
  - 当传递一个字符串, 而且是只读的情况下, 确保通过常量引用传递它

---

# C++的字符串字面量

- 字符串字面量: 是在双引号之间的一串字符
  
  ```cpp
  #include <iostream>
  #include <string>
  
  int main()
  {
      using namespace std::string_literals;
      //附加其它字符
      std::string name = "Giskard"s + "hello";
      //R意味着忽略转义字符
      const char* example = R"(Line1
  Line2
  Line3)";
  
      const char* ex = "Line1\n"
          "Line2\n"
          "Line3\n";
  
      const char* name0 = "Giskard";
      //wchar_t表示宽字符
      //定义宽字符时, 前面要加L表示下面的字符串字面量有宽字符组成
      const wchar_t* name1 = L"Giskard"; 
      //2个byte的16bit字符
      const char16_t* name2 = u"Giskard";
      //4个byte的32bit字符
      const char32_t* name3 = U"Giskard";
      std::cout << name << std::endl;
      std::cin.get();
  }
  ```

---

# C++中的CONST

- `const`更像是一个承诺, 承诺不会修改变量, 但也可以通过其它方式打破承诺去修改变量
  
  ```cpp
  #include <iostream>
  #include <string>
  
  class Entity
  {
  private: 
      int m_X, m_Y;
      mutable int var;
  public:
      //这个方法不会修改任何实际的类, 因此我们不能修改类成员变量
      int GetX() const 
      {
          var = 2; //var为mutable类型, 所以可以在const方法中修改
          return m_X;
      }     
  
      int GetX()
      {
          return m_X;
      }
  };
  
  void PrintEntity(const Entity& e) //同指针一样, 可以改变指向, 不能改变值
  {
      std::cout << e.GetX() << std:;endl;
  }
  
  int main()
  {
      const int MAX_AGE = 90;
  
      const int* a = new int; //可以改变指向, 但不能改变指向的值
      int const* a = new int; //作用同上
      int* const a = new int; //不能改变指向, 但可以改变指向的值
      const int* const a = new int; //不能改变指向, 也不能改变指向的值
  
      *a = 2;
      a = (int*)&MAX_AGE;
      std::cout << *a << std::endl;
  
      std::cin.get();
  }
  ```
  
  - `mutable`这个前缀意味着变量可以被改变

---

# C++的mutable关键字

```cpp
#include <iostream>
#include <string>

class Entity
{
private:
    std::string m_Name;
    mutable int m_DebugCount = 0;
public:
    const std::string& GetName() const 
    {
        m_DebugCount++;
        return m_Name;
    }
};

int main()
{
    const Entity e;
    e.GetName();

    int x = 8;
    auto f = [=]() mutable //使x可以在lambda中直接修改
    {
        x++;
        std::cout << x << std::endl;
    }

    f();

    std::cin.get();
}
```

- `lambda`基本上就像一个一次性的小函数, 你可以写出来并赋值给一个变量

---

# C++的成员初始化列表

- 构造函数初始化列表: 在构造函数中初始化类成员(变量)的一种方式
  
  ```cpp
  #include <iostream>
  #include <string>
  
  class Entity
  {
  private:
      std::string m_Name;
      int m_Score;
  public:
      Entity()
          : m_Name("Unknown"), m_Score(0) {} //需要注意初始化顺序
      /*{
          m_Name = "Unknown";
      }*/        
  
      Entity(const std::string& name)
      {
          m_Name = name;    
      }
  
      const std::string& GetName() const
          : m_Name(name) {}
      /*{
          return m_Name;
      }*/      
  };
  
  int main()
  {
      Emtity e0;
      std::cout << e0.GetName() << std::endl;    
  
      Emtity e1("Giskard");
      std::cout << e1.GetName() << std::endl;
      std::cin.get();
  }
  ```

---

# C++的三元操作符

```cpp
#include <iosream>
#include <string>

static int s_Level = 1;
static int s_Speed = 2;

int main()
{
    if(s_Level > 5)
        s_Speed = 10;
    else
        s_Speed = 5;

    s_Speed = s_Level > 5 ? (s_Level > 10 ? 15 : 10) : 5; //三元操作符的嵌套

    std::string rank = s_Level > 10 ? "Master" : "Beginner";


    std::cin.get();
}
```

- 尽量不要对三元操作符做嵌套

---

# 创建并初始化C++对象

```cpp
#include <iostream>
#include <string>

using String = std::string;

class Entity
{
private:
    String m_Name;
public:
    Entity() : m_name("Unknown") {}
    Entity(const String& name) : m_Name(name) {}

    const String& GetName() const {return m_Name;}
};

int main()
{
    Entity* entity = new Entity("Giskard");
    std::cout << entity.GetName() << std::endl;
    delete entity;
    std::cin.get();
}
```

- 在堆上创建的内存需要手动用`delete`释放

---

# C++的new关键字

```cpp
#include <iostream>
#include <string>

using String = std::string;

class Entity
{
private:
    String m_Name;
public:
    Entity() : m_name("Unknown") {}
    Entity(const String& name) : m_Name(name) {}

    const String& GetName() const {return m_Name;}
};

int main()
{
    int a = 2;
    int* b = new int[50]; // 200 bytes

    Entity* e = new Entity();
    Entity* e = (Entity*)malloc(sizeof(Entity)); //c++中不要用这种方法
    /*
     两行代码的区别:
        new调用了构造函数并分配内存
        malloc仅仅分配内存
    */    

    //不要忘记释放内存
    delete[] b; //数组的释放
    delete e; //释放new的内存
    free(e); //释放malloc的内存    

    std::cin.get();
}
```

---

# C++隐式转换与explicit关键字

```cpp
#include <iostream>
#include <string>

class Entity
{
private:
    std::string m_Name;
    int m_Age;
public:
    Entity(const std::string& name) //m_Age(-1)表示无效的
        : m_Name(name), m_Age(-1) {}

    Entity(int age)
        : m_Name("Unknown"), m_Age(age) {}

};

void PrintEntity(const Entity& entity)
{
    // Printng
}

int main()
{
    PrintEntity(22);
    PrintEntity(Entity("Giskard")); //隐式转换: 将"Giskard"由char[]转换为std::string

    Entity a("Giskard");
    Entity b(19);

    std::cin.get();
}
```

- `explicit`放在构造函数里意味着没有隐式转换
  
  ```cpp
  #include <iostream>
  #include <string>
  
  class Entity
  {
  private:
      std::string m_Name;
      int m_Age;
  public:
      Entity(const std::string& name) //m_Age(-1)表示无效的
          : m_Name(name), m_Age(-1) {}
  
      explicit Entity(int age) //禁止隐式转换
          : m_Name("Unknown"), m_Age(age) {}
  
  };
  
  void PrintEntity(const Entity& entity)
  {
      // Printng
  }
  
  int main()
  {
      PrintEntity(Entity(19)); //需要显式转换调用
      PrintEntity(Entity("Giskard")); 
  
      Entity a("Giskard");
      Entity b(Entity(19)); //需要显式转换调用
  
      std::cin.get();
  }
  ```

---

# C++运算符及其重载

- 重载这个术语本质是给运算符重载赋予新的含义, 或者添加参数, 或者创建允许在程序中定义或更改运算符的行为, 但在Java等语言中不受支持, 在C#中部分支持

```cpp
#include <iostream>
#include <string>

struct Vector2
{
    float x, y;

    Vector2(float x, float y)
        : x(x), y(y) {}

    Vector2 Add(const Vector2& other) const
    {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 operator+(const Vector2& other) const //运算符重载
    {
        return Add(other);
    }

    Vector2 Multiply(const Vector2& other) const
    {
        return Vector2(x * other.x, y * other.y);
    }

    Vector2 operator*(const Vector2& other) const //运算符重载
    {
        return Multiply(other);
    }

    bool operator==(const Vector2& other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Vector2& other) const
    {
        return !(*this == other);
    }
};

std::ostream& oprator<<(std::string& stream, const Vector2& other)
{
    stream << other.x << ", " << other.y;
    return stream;
}

int main()
{
    Vector2 position(4.0f, 4.0f);
    Vector2 speed(0.5f, 1.5f);
    Vector2 powerup(1.1f, 1.1f);

    Vector2 result1 = position.Add(speed.Multiply(powerup));
    Vector2 result2 = position + speed * powerup;    

    if(result1 == result2){}

    std::cout << result << std::endl;
    std::cin.get();
}
```

---

# C++的this关键字

- `this`是一个指向当前对象实例的指针, 该方法属于这个对象实例

- `this`是隐含指针, 保存当前调用对象的地址

- 仅在非`static`成员函数内可用; 静态函数内无`this`

- `const`成员函数中`this`是指向`const` 对象的指针, 不能修改成员
  
  ```cpp
  #include <iostream>
  #include <string>
  
  void PrintEntity(const Entity& e);
  
  class Entity
  {
  public:
      int x, y;
  
      Entity(int x, int y)
      {
          this->x = x;
          this->y = y;
  
          Entity& e = *this;
  
          PrintEntity(*this);
      }
  
      int Get()
      {
          const Entity& e = *this;
      }
  };
  
  void PrintEntity(const Entity& e)
  {
      // Print
  }
  
  int main()
  {
  
      std::cin, get();
  }
  ```

---

# C++的对象生存期(栈作用域生存期)

- 当在栈上创建一个变量, 当它超出作用域, 它就会消失
  
  ```cpp
  #include <iostream>
  #include<string>
  
  class Entity
  {
  public:
      Entity()
      {
          std::cout << "Created Entity!" << std::endl;
      }
  
      ~Entity()
      {
          std::cout << "Destroyed Entity!" << std::endl;
      }
  };
  
  class ScopedPtr
  {
  private:
      Entity* m_Ptr;
  public:
      ScopedPtr(Entity* ptr)
          : m_Ptr(ptr)
      {
  
      }
  
      ~ScopedPtr()
      {
          delete m_Ptr;
      }
  };
  
  int main()
  {
      {
          //e是在栈上创建的 ScopedPtr e(new Entity()); 
          ScopedPtr e = new Entity();
      }
  
      std::cin.get();
  }
  ```

---

# C++的智能指针

- 智能指针: 当调用new时, 不需要调用delete

- `unique_ptr`是作用域指针, 是超出作用域时, 它会被销毁然后调用`delete`
  
  - 不能复制`unique_ptr`, 因为这两个指针指向同一内存, 如果其中一个被销毁, 指向的内存也被释放, 那么另一个指针就会指向被释放的内存, 成为悬空指针

- `shared_ptr`: 工作方式是通过引用计数, 引用计数基本上是一种方法, 可以跟踪你的指针有多少个引用, 一旦引用次数为零, 它就被删除了

- `weak_ptr`: 它只是像声明其它东西一样声明, 不会增加`shared_ptr`的引用次数, 用于解决循环引用内存泄露问题
  
  ```cpp
  #include <iostream>
  #include <string>
  #include <memory>
  
  class Entity
  {
  public:
  
      Entity()
      {
          std::cout << "Created Entity!" << std::endl;
      }
  
      ~Entity()
      {
          std::cout << "Destroyed Entity!" << std::endl;
      }
  
      void Print() {}
  
  };
  
  int main()
  {
  
      {
          std::shared_ptr<Entity> e0;
          {
              //unique_ptr中内置explicit关键字,需要用显式转换
              //std::unique_ptr<Entity> entity(new Entity());
              std::unique_ptr<Entity> entity = std::make_unique<Entity>(); //对unique_ptr更安全的写法
  
              std::shared_ptr<Entity> sharedEntity = std::make_shared<Entity>();
              std::weak_ptr<Entity> weakEntity = sharedEntity;
              e0 = sharedEntity;
          }
      }
      std::cin.get();
  
  }
  ```

---

# C++的复制与拷贝构造函数

- 复制需要时间, 如果只需读取的话应该避免复制

- 友元: 将目标函数标记为自己人, 允许访问类的私有变量

```cpp
#include <iostream>
#include <string>

class String
{
private:
    char* m_Buffer;
    unsigned int m_Size;
public:
    String(const char* string)
    {
        m_Size = strlen(string);
        m_Buffer = new char[m_Size + 1];
        memcpy(m_Buffer, string, m_Size + 1);
    }

    //String(const String& other) = delete; 禁止复制
    String(const String& other)
        : m_Buffer(other.m_Buffer),m_Size(other.m_Size)
    {
        //深度拷贝
        std::cout << "Copied string!" << std::endl;

        m_Buffer = new char[m_Size + 1];
        memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
    }

    ~String()
    {
        delete[] m_Buffer;
    }

    char& operator[](unsigned int index)
    {
        return m_Buffer[index];
    }

    friend std::ostream& operator<<(std::ostream& stream, const String& string);

};

std::ostream& operator<<(std::ostream& stream, const String& string)
{
    stream << string.m_Buffer;
    return stream;
}

void PrintString(const String& string)
{
    std::cout << string << std::endl;
}

int main()
{
    String string = "Giskard";
    String second = string;

    second[2] = 'a';

    PrintString(string);
    PrintString(second);

    std::cin.get();
}
```

- 总是使用const引用传递对象

---

# C++的箭头操作符

```cpp
#include <iostream>
#include <string>

struct Vector3
{
    float x, y, z;
};

int main()
{
    //得到x的偏移量
    int offset = (int)&((Vector3*)nullptr)->x;
    std::cout << offset << std::endl;

    std::cin.get();
}
```

---

# C++的动态数组

- 使用动态数组需要包括头文件`#include <vector>`

- 使用`std::vector<ElemType> variable;`来定义动态数组

- 插入元素: `variable.push_back(...);`

- 删除特定元素: `variable.erase(variable.begin() + n);`

- 清除列表: `variable.clear();`
  
  ```cpp
  #include <iostream>
  #include <string>
  #include <vector>
  struct Vertex
  {
      float x, y, z;
  };
  
  std::ostream& operator<<(std::ostream& stream, const Vertex& vertex)
  {
      stream << vertex.x << ", " << vertex.y << ", " << vertex.z;
      return stream;
  }
  
  void Function(const std::vector<Vertex>& vertices)
  {
  
  }
  
  int main()
  {
      std::vector<Vertex> vertices;
      vertices.push_back({ 1,2,3 });
      vertices.push_back({ 4,5,6 });
      Function(vertices);
  
      for (int i = 0; i < vertices.size(); i++)
      {
          std::cout << vertices[i] << std::endl;
      }
  
      vertices.erase(vertices.begin() + 1); //删除指定元素
  
      for (const Vertex& v : vertices)
      {
          std::cout << v << std::endl;
      }
  
      vertices.clear(); //清除vertices列表
  
      std::cin.get();
  } 
  ```

---

# C++的std::vector使用优化

- 使用`variable.emplace_back(...);`插入元素避免复制
  
  ```cpp
  #include <iostream>
  #include <string>
  #include <vector>
  
  struct Vertex
  {
  
      float x, y, z;
  
      Vertex(float x, float y, float z)
          :x(x), y(y), z(z)
      {
  
      }
  
      Vertex(const Vertex& vertex)
          :x(vertex.x), y(vertex.y), z(vertex.z)
      {
          std::cout << "Copied!" << std::endl;
      }
  
  };
  
  int main()
  {
  
      std::vector<Vertex> vertices;
      vertices.reserve(3); //设置容量
  
      /*
      //现在main的栈上构造, 在复制到vector
      //每新增一个元素都会调整长度,然后复制先前的元素,再加入新的元素
      vertices.push_back(Vertex(1,2,3));
      vertices.push_back(Vertex(4,5,6));
      vertices.push_back(Vertex(7,8,9));
      */
  
      //在实际的vector内存中构造对象
      vertices.emplace_back(1, 2, 3);
      vertices.emplace_back(4, 5, 6);
      vertices.emplace_back(7, 8, 9);
  
      std::cin.get();
  
  }
  ```

---

# C++中使用库(静态链接)

- 头文件引用: 引号先检查相对路径, 如果没有找到相对main.cpp文件的东西, 就会去找编译器

- 如果在vs中和实际解决方案一起编译, 使用引号" "; 如果是外部的库, 不在vs中和实际方案一起编译使用尖括号< >来表示它实际上是外部的

```cpp
#include <iostream>
#include <GLFW/glfw3.h>


int main()
{
  int a = glfwInit();
  std::cout << a << std::endl;

  std::cin.get();
}
```

---

# C++中使用动态库

- 静态链接与动态链接的区别: 动态链接是链接发生在运行时; 静态链接是链接发生在编译时.

```cpp
#include <iostream>
#include <GLFW/glfw3.h>


int main()
{
    int a = glfwInit();
    std::cout << a << std::endl;

    std::cin.get();
}
```

---

# C++中创建与使用库

```cpp
//Engine.h
#pragma once

namespace engine
{
    void PrintMessage();
}
```

```cpp
//Engine.cpp
#include "Engine.h"
#include <iostream>

namespace engine
{
    void PrintMessage()
    {
        std::cout << "Hello World!" << std::endl;
    }
}
```

```cpp
//Application.cpp
#include "Engine.h"
#include <iostream>


int main()
{
    engine::PrintMessage();
    std::cin.get();
}
```

---

# C++中如何处理多返回值

- 使用结构体实现多返回值
  
  ```cpp
  #include <iostream>
  #include <string>
  
  struct Entity
  {
      std::string x;
      std::string y;
  };
  
  Entity Init(std::string x, std::string y)
  {
  
      return { x,y };
  
  }
  
  std::ostream& operator<<(std::ostream& stream,const Entity& entity)
  {
  
      stream << entity.x << ", " << entity.y;
      return stream;
  
  }
  
  int main()
  {
  
      Entity entity;
      entity = Init("Hello", "World!");
  
      std::cout << entity << std::endl;
  
      std::cin.get();
  
  }
  ```

---

# C++的模板(templates)

- 模板函数只有在被调用的时候才会被创建

- 模板的优缺点:

- 优点: 提高代码的复用性, 减少代码重复

- 缺点: 可能增加编译时间, 错误信息可能难以理解

- 创建模板函数

```cpp
#include <iostream>
#include <string>


template<typename T> //创建模板
void Print(T value)
{
    std::cout << value << std::endl;
}


int main()
{
    Print(5);
    Print("Hello");
    Print(5.5f);

    std::cin.get();
}
```

- 创建模板类
  
  ```cpp
  #include <iostream>
  #include <string>
  
  template<typename T,int N>
  class Array
  {
  private:
      T m_Array[N];
  public:
      int GetSize() const
      {
          return N;
      }
  
  };
  
  int main()
  {
  
      Array<std::string,5> array;
      std::cout << array.GetSize() << std::endl;
  
      std::cin.get();
  
  }
  ```

---

# C++的堆(heap)与栈(stack)内存的比较

- 在堆上分配内存是比较复杂的过程, 在栈上分配内存更像是CPU的指令. 所以栈的内存分配更快

- 在堆上分配的内存, 如果不是智能指针的话, 一定要记得使用`delete`释放内存

---

# C++的宏

```cpp
#include <iostream>
#include <string>

#if PR_DEBUG == 1
#define LOG(x) std::cout << x << std::endl
#elif defined(PR_RELEASE)
#define LOG(x)
#endif 

int main()
{
  LOG("Hello!");

  std::cin.get();
}
```

```cpp
#include <iostream>
#include <string>

// 反斜杠转义为换行
#define MAIN int main() \
{\
    std::cin.get();\
}

MAIN
```

---

# C++的auto关键字

- 短类型尽量不用`auto`, 长类型可以用
  
  ```cpp
  #include <iostream>
  #include <string>
  #include <vector>
  
  std::string GetName()
  {
      return "Giskard";
  }
  
  int main()
  {
      auto a = GetName();
      std::vector<std::string> strings;
      strings.emplace_back("Apple");
      strings.emplace_back("Orange");
  
      for (auto i : strings)
          std::cout << i << std::endl;
  
      std::cin.get();
  }
  ```

---

# C++的静态数组

```cpp
#include <iostream>
#include <array>

void PrintArray(const std::array<int, 3>& data)
{
    for (int i : data)
    {
        std::cout << i;
        if (i != data.size())
            std::cout << ", ";
    }
    std::cout << std::endl;
}

int main()
{
    std::array<int, 3> data;

    for (int i = 0;i < data.size();i++)
    {
        data[i] = i + 1;
    }

    PrintArray(data);

    std::cin.get();
}
```

---

# C++的函数指针

```cpp
#include <iostream>

void HelloWorld()
{
    std::cout << "Hello,World!" << std::endl;
}

int main()
{
    //不用auto的方法
    typedef void(*HelloWorldFun)();
    HelloWorldFun fun = HelloWorld;
    fun();

    /*
    auto fun = HelloWorld;
    fun();
    */

    std::cin.get();
}
```

```cpp
#include <iostream>
#include <vector>

void PrintValue(int value)
{
    std::cout << "Value: " << value << std::endl;
}

//void(*fun)(int)为接收函数的形参
void ForEach(const std::vector<int>& values, void(*fun)(int))
{
    for (int i : values)
        fun(i);
}

int main()
{
    std::vector<int> values = { 1,2,3,4,5 };
    ForEach(values, PrintValue);

    std::cin.get();
}
```

```cpp
#include <iostream>
#include <vector>

void ForEach(const std::vector<int>& values, void(*fun)(int))
{
    for (int i : values)
        fun(i);
}

int main()
{
    std::vector<int> values = { 1,2,3,4,5 };
    //传入lambda函数
    ForEach(values, [](int value) {std::cout << "Value: " << value << std::endl;});

    std::cin.get();
}
```

---

# C++的lambda

- 只要有一个函数指针, 就可以在C++中使用lambda
  
  ```cpp
  #include <iostream>
  #include <vector>
  #include <functional>
  #include <algorithm>
  
  void ForEach(const std::vector<int>& values,const std::function<void(int)>& fun)
  {
      for (int i : values)
          fun(i);
  }
  
  int main()
  {
      std::vector<int> values = { 1,2,3,4,5 };
      auto it = std::find_if(values.begin(), values.end(), [](int value) {return value > 3;});
      std::cout << *it << std::endl;
  
      int a = 5;
      auto lambda = [&a](int value) {std::cout << "Value: " << a << std::endl;};
      ForEach(values, lambda);
  
      std::cin.get();
  }
  ```

---

# 为什么不使用using namespace std;

- 如果引入其它命名空间, 可能会使可读性受到影响, 增加维护难度

---

# C++的名称空间

- 名称空间的主要目的是避免命名冲突

- `::`为空间访问符
  
  ```cpp
  #include <iostream>
  #include <string>
  
  namespace apple
  {
      void print(const char* text)
      {
          std::cout << text << std::endl;
      }
  
      void print_again(const char* text)
      {
          std::cout << text << std::endl;
      }
  }
  
  namespace orange
  {
      void print(const char* text)
      {
          std::string temp = text;
          std::reverse(temp.begin(), temp.end());
          std::cout << temp << std::endl;
      }
  }
  
  int main()
  {
      using apple::print;
      namespace a = apple;
  
      print("Hello!");
      a::print_again("Hello!");
      orange::print("Hello!");
  
      std::cin.get();
  }
  ```

---

# C++的线程

```cpp
#include <iostream>
#include <thread>
#include <chrono>

static bool s_Finished = false;

void Dowork()
{
    using namespace std::literals::chrono_literals;

    std::cout << "Started thread id = " << std::this_thread::get_id() << std::endl;

    while (!s_Finished)
    {
        std::cout << "Working...\n";
        std::this_thread::sleep_for(1s);
    }
}

int main()
{
    std::thread worker(Dowork);

    std::cin.get();
    s_Finished = true;

    worker.join();
    std::cout << "Finished." << std::endl;

    std::cin.get();
}
```

---

# C++的计时

```cpp
#include <iostream>
#include <thread>
#include <chrono>

struct Timer
{
    std::chrono::steady_clock::time_point start, end;
    std::chrono::duration<float> duration;

    Timer()
    {
        start = std::chrono::high_resolution_clock::now();
    }

    ~Timer()
    {
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;

        float ms = duration.count() * 1000.0f;
        std::cout << "Timer took " << ms << "ms " << std::endl;
    }
};

void Function()
{
    Timer timer;

    for (int i = 0; i < 100; i++)
    {
        std::cout << "Hello" << std::endl;
    }
}

int main()
{
    Function();

    std::cin.get();
}
```

---

# C++的多维数组

```cpp
#include <iostream>


int main()
{
    //分配50个int*, 用空间来存储这50个int指针
    int** a2d = new int* [50];
    for (int i = 0; i < 50; i++)
    {
        a2d[i] = new int[50];
    }

    for (int i = 0; i < 50; i++)
    {
        delete[] a2d[i];
    }
    delete a2d;

    int*** a3d = new int** [50];
    for (int i = 0; i < 50; i++)
    {
        a3d[i] = new int* [50];
        for (int j = 0; j < 50; j++)
        {
            a3d[i][j] = new int[50];
        }
    }

    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            delete[] a3d[i][j];
        }
        delete[] a3d[i];
    }
    delete a3d;

    std::cin.get();
}
```

---

# C++的排序

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main()
{
    std::vector<int> values = { 2, 4, 5, 1, 3 };
    std::sort(values.begin(), values.end(), std::greater<int>());
    for (int value : values)
    {
        std::cout << value << std::endl;
    }
    std::cout << "---------------------------------------" << std::endl;
    std::sort(values.begin(), values.end(), [](int a, int b) {
        if (a == 1) //把1放前面
            return true;
        if (b == 1)
            return false;
        return a > b;
        });

    for (int value : values)
    {
        std::cout << value << std::endl;
    }

    std::cin.get();
}
```

---

# C++的类型双关

- 类型双关: 用一种类型的内存, 解释成另一种类型去读写.
  
  ```cpp
  #include <iostream>
  
  struct Entity
  {
      int x, y;
  
      int* Getpositions()
      {
          return &x;
      }
  };
  
  int main()
  {
      Entity e = { 5,8 };
  
      int* position = (int*)&e;
      int* position1 = e.Getpositions();
  
      std::cout << position[0] << ", " << position[1] << std::endl;
      std::cout << *position1 << std::endl;
  
      std::cin.get();
  }
  ```

---

# C++的联合体

```cpp
#include <iostream>

struct Vector2
{
    float x, y;
};

struct Vector4
{
    union {
        struct
        {
            float x, y, z, w;
        };
        struct 
        {
            Vector2 a, b;
        };
    };

};

void PrintVector2(const Vector2& vector)
{
    std::cout << vector.x << ", " << vector.y << std::endl;
}

int main()
{
    Vector4 vector = { 1.0f,2.0f,3.0f,4.0f };
    PrintVector2(vector.a);
    PrintVector2(vector.b);
    vector.z = 500.0f;
    std::cout << "--------------------------------------" << std::endl;
    PrintVector2(vector.a);
    PrintVector2(vector.b);

    std::cin.get();
}
```

---

# C++的虚析构函数

- 如果一个类要拓展子类, 那么一定要声明析构函数是虚函数
  
  ```cpp
  #include <iostream>
  
  class Base
  {
  public:
      Base()
      {
          std::cout << "Base Constructor\n";
      }
      virtual ~Base()
      {
          std::cout << "Base Destructor\n";
      }
  };
  
  class Derived : public Base
  {
  public:
      Derived()
      {
          std::cout << "Derived Constructor\n";
      }
  
      ~Derived() override
      {
          std::cout << "Derived Destructor\n";
      }
  };
  
  int main()
  {
      Base* base = new Base();
      delete base;
      std::cout << "---------------------------------------\n";
      Derived* derived = new Derived();
      delete derived;
      std::cout << "---------------------------------------\n";
      Base* poly = new Derived();
      delete poly;
  
      std::cin.get();
  }
  ```

---

# C++的类型转换

- 四种主要的cast
  
  - `static_cast`
    
    - 静态类型转换, 会做一些其它的编译时检查, 检查这种转换是否真的可能
  
  - `reinterpret_cast`
    
    - 把这段内存重新解释成别的东西, 即内存的类型双关
  
  - `dynamic_cast`
    
    - 用于继承之间的转换, 需要依赖虚函数
  
  - `const_cast`
    
    - 移除或添加变量的const限定
  
  ```cpp
  #include <iostream>
  
  class Base
  {
  public:
      Base() {}
      virtual ~Base(){}
  };
  
  class Derived : public Base
  {
  public:
      Derived(){}
      ~Derived(){}
  };
  
  class AnotherClass : public Base
  {
  public:
      AnotherClass(){}
      ~AnotherClass(){}
  };
  
  int main()
  {
      int value = 2;
      float a = static_cast<float>(value);
  
      Base* base = new Derived();
      Derived* ac = dynamic_cast<Derived*>(base);
  
      std::cin.get();
  }
  ```

---

# 现代C++中的安全以及如何教授

- 安全编程: 希望降低崩溃, 内存泄漏, 非法访问等问题

- 根据实际需求选择原始指针或智能指针

---

# C++的预编译头文件

- 不要将频繁更改的文件放入预编译头文件中

- 使用预编译头文件操作
  
  - 创建头文件
    
    ```cpp
    //pch.h
    #pragma once
    
    #include <iostream>
    #include <algorithm>
    #include <functional>
    #include <memory>
    #include <thread>
    #include <utility>
    
    // Data structures
    #include <string>
    #include <stack>
    #include <deque>
    #include <array>
    #include <vector>
    #include <set>
    #include <map>
    #include <unordered_set>
    #include <unordered_map>
    
    // Windows API
    #include <Windows.h>
    ```
  
  - 创建包含头文件的.cpp文件
    
    ```cpp
    //pch.cpp
    #include "pch.h"
    ```
    
    - 在属性\c/c++\预编译头中选择"创建"
      
      ![](C:\Users\35055\Pictures\Screenshots\屏幕截图%202026-09-08%20174239.png)
  
  - 在调用头文件的.cpp文件选择"使用", 并将预编译头文件改为头文件名
    
    ```cpp
    //main.cpp
    #include "pch.h"
    
    int main()
    {
        std::cout << "Hello, World!\n";
    }
    ```
    
    ![](C:\Users\35055\Pictures\Screenshots\屏幕截图%202026-09-08%20174711.png)

---

# C++的dynamic_cast

- 基类需要至少有一个虚函数
  
  ```cpp
  #include <iostream>
  #include <string>
  
  class Entity
  {
  public:
      virtual void PrintName() {}
  };
  
  class Player : public Entity
  {
  public:
  
  };
  
  class Enemy : public Entity
  {
  public:
  
  };
  
  int main()
  {
      Player* player = new Player();
      Entity* actullyPlayer = player;
      Entity* actullyEnemy = new Enemy();
  
      //可以转换, 但返回nullptr
      Player* p0 = dynamic_cast<Player*>(actullyEnemy);
  
      Player* p1 = dynamic_cast<Player*>(actullyPlayer);
  }
  ```

---

# C++的基准测试

- debug需要进行许多调试, release会去除任何多余的东西
  
  ```cpp
  #include <iostream>
  #include <memory>
  #include <chrono>
  #include <array>
  
  class Timer
  {
  private:
      std::chrono::high_resolution_clock::time_point m_StartTimepoint;
  
  public:
      Timer()
      {
          m_StartTimepoint = std::chrono::high_resolution_clock::now();
      }
  
      ~Timer()
      {
          Stop();
      }
  
      void Stop()
      {
          auto EndTimepoint = std::chrono::high_resolution_clock::now();
  
          //这里的time_since_epoch()是自时间起始点到现在的时长
          auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
          auto end = std::chrono::time_point_cast<std::chrono::microseconds>(EndTimepoint).time_since_epoch().count();
  
          auto duration = end - start;
          double ms = duration * 0.001;
  
          std::cout << duration << "us(" << ms << "ms)\n";
      }
  };
  
  int main()
  {
      int value = 0;
      {
          Timer timer;
          for (int i = 0; i < 1000000; i++)
              value += 2;
      }
  
      std::cout << value << std::endl;
  
      struct Vector2
      {
          float x, y;
      };
  
      std::cout << "Make shared\n";
      {
          std::array<std::shared_ptr<Vector2>, 1000> sharedPtrs;
          Timer timer;
          for (int i = 0; i < sharedPtrs.size(); i++)
          {
              sharedPtrs[i] = std::make_shared<Vector2>();
          }
      }
  
      std::cout << "Make new shared\n";
  
      {
          std::array<std::shared_ptr<Vector2>, 1000> sharedPtrs;
          Timer timer;
          for (int i = 0; i < sharedPtrs.size(); i++)
          {
              sharedPtrs[i] = std::shared_ptr<Vector2>(new Vector2);
          }
      }
  
      std::cout << "Make unique\n";
  
      {
          std::array<std::unique_ptr<Vector2>, 1000> sharedPtrs;
          Timer timer;
          for (int i = 0; i < sharedPtrs.size(); i++)
          {
              sharedPtrs[i] = std::make_unique<Vector2>();
          }
      }
  
      //visual studio专门仅用于windows的函数
      //它所做的是在这里中断编译
      __debugbreak();
  }
  ```

---

# C++的结构化绑定

```cpp
#include <iostream>
#include <tuple> //元组 
#include <string>

std::tuple<std::string, int> CreatePerson()
{
    return { "Giskard",19 };
}

int main()
{
    //C++11
    auto person = CreatePerson();
    std::string name1 = std::get<0>(person);
    int age1 = std::get<1>(person);

    //C++11
    std::string name2;
    int age2;
    std::tie(name2, age2) = CreatePerson();

    // C++17特性, 结构化绑定
    auto [name3, age3] = CreatePerson();
}
```

---

# 如何处理OPTIONAL数据

```cpp
#include <iostream>
#include <fstream>
#include <optional> //C++17

std::optional<std::string> ReadFileAsString(const std::string& filepath)
{
    std::ifstream stream(filepath);
    if (stream)
    {
        std::string result;
        // read file
        stream.close();
        return result;
    }

    return {};
}

int main()
{
    std::optional<std::string> data = ReadFileAsString("data.txt");

    std::string value = data.value_or("Not present");
    std::cout << value << std::endl;
    if (data)
    {
        std::cout << "File read successfully!\n";
    }
    else
    {
        std::cout << "File could not be opened!\n";
    }

    std::cin.get();
}
```

---

# 单一变量存放多种数据类型的数据(C++17)

```cpp
#include <iostream>
#include <variant>

enum class ErrorCode
{
    None, Notfound, NoAccess
};

std::variant<std::string> ReadFileAsString()
{
    return {};
}

int main()
{
    std::variant<std::string, int> data;

    std::cout << sizeof(int) << '\n';
    std::cout << sizeof(std::string) << '\n';
    std::cout << sizeof(data) << '\n';

    data = "Giskard";
    std::cout << std::get<std::string>(data) << '\n';

    if (auto* value = std::get_if<std::string>(&data))
    {
        std::string& v = *value;
    }
    else
    {

    }

    data = 2;
    std::cout << std::get<int>(data) << '\n';

    std::cin.get();
}
```

---

# 如何存储任意类型的数据(C++17)

- 没用的东西
  
  ```cpp
  #include <iostream>
  #include <any>
  
  int main()
  {
  
      std::any data;
      data = 2;
      data = "Giskard";
      data = std::string("Giskard");
  
      auto string = std::any_cast<std::string>(data);
  
      std::cin.get();
  
  }
  ```
  
  ---

# 如何让C++字符串更快

```cpp
#include <iostream>
#include <string>

static uint32_t s_AlloCount = 0;

void* operator new(size_t size)
{
  s_AlloCount++; //计算分配次数
  std::cout << "AllocCount " << size << " bytes\n"; //打印分配大小
  return malloc(size);
}

void PrintName(std::string_view name)
{
  std::cout << name << std::endl;
}

int main()
{
  const char* name = "Giskard Reventlov";

#if 0
  std::string firstname = name.substr(0, 7);
  std::string lastname = name.substr(8, 16);
#else
  std::string_view firstname(name, 7);
  std::string_view lastname(name + 8, 16);
#endif

  PrintName(firstname);
  PrintName(lastname);

  std::cout << s_AlloCount << " alloctions\n";

  std::cin.get();
}
```

---

# C++的单例模式

- 单例是一个类的单一实例
  
  ```cpp
  #include <iostream>
  
  class Random //不能在外部被实例化
  {
  public:
      Random(const Random&) = delete; //禁止拷贝
  
      static Random& Get()
      {
          static Random s_Instance;
          return s_Instance;
      }
  
      static float Float()
      {
          return Get().IFloat();
      }
  
  private:
      Random() {}
  
      float IFloat()
      {
          return m_RandomGenerator;
      }
  
      float m_RandomGenerator = 0.5f;
  
  };
  
  int main()
  {
  
      float num = Random::Float();
      std::cout << num << std::endl;
  
      std::cin.get();
  
  }
  ```

---

# 跟踪内存分配的简单方法

```cpp
#include <iostream>
#include <memory>

struct AllocationMetrics
{
    uint32_t TotalAllocated = 0;
    uint32_t TotalFreed = 0;

    uint32_t CurrentUsage()
    {
        return TotalAllocated - TotalFreed;
    }
};

static AllocationMetrics s_AllocationMetrics;

void* operator new(size_t size)
{
    s_AllocationMetrics.TotalAllocated += size;

    return malloc(size);
}

void operator delete(void* memory,size_t size)
{
    s_AllocationMetrics.TotalFreed += size;

    free(memory);
}

struct Object
{
    int x, y, z;
};

void PrintMemoryUsage()
{
    std::cout << "Memory Usage: " << s_AllocationMetrics.CurrentUsage() << " bytes\n";
}

int main()
{
    PrintMemoryUsage();
    std::string string = "Giskard";
    PrintMemoryUsage();
    {
        std::unique_ptr<Object> obj = std::make_unique<Object>();
        PrintMemoryUsage();
    }
    PrintMemoryUsage();
    std::cin.get();
}
```

---

# C++的左值与右值

- 左值是有某种存储支持的变量, 右值是临时值

- 左值引用仅仅接受左值, 除非是用`const`, 右值引用只接受右值
  
  ```cpp
  #include <iostream>
  
  void PrintName(const std::string& name)
  {
      std::cout << "[lvalue]" << name << std::endl;
  }
  
  void PrintName(const std::string&& name)
  {
      std::cout << "[rvalue]" << name << std::endl;
  }
  
  int main()
  {
      std::string firstName = "Giskard";
      std::string lastName = "Reventlov";
  
      std::string fullName = firstName + lastName;
  
      PrintName(fullName);
      PrintName(firstName + lastName);
  
      std::cin.get();
  }
  ```

---

# C++的参数计算顺序

```cpp
#include <iostream>

void PrintSum(int a, int b)
{
    std::cout << a << " + " << b << " = " << a + b << std::endl;
}

int main()
{
    int value = 0;
    PrintSum(value++, value++); //未定义行为

    std::cin.get();
}
```

---

# C++移动语义

```cpp
#include <iostream>

class String
{
public:
    String(const char* string)
    {
        std::cout << "Created!\n";
        m_Size = strlen(string);
        m_Data = new char[m_Size];
        memcpy(m_Data, string, m_Size);
    }

    String(const String& other)
    {
        std::cout << "Copied!\n";

        m_Size = other.m_Size;
        m_Data = new char[m_Size];
        memcpy(m_Data, other.m_Data, m_Size);
    }

    String(String&& other) noexcept
    {
        std::cout << "Moved!\n";

        m_Size = other.m_Size;
        m_Data = other.m_Data;
        memcpy(m_Data, other.m_Data, m_Size);

        other.m_Size = 0;
        other.m_Data = nullptr;
    }

    ~String()
    {
        std::cout << "Destroyed!\n";
        delete[] m_Data;
    }

    void Print()
    {
        for (uint32_t i = 0; i < m_Size; i++)
        {
            std::cout << static_cast<char>(m_Data[i]);
        }
        std::cout << '\n';
    }

private:
    uint32_t m_Size;
    char* m_Data;
};

class Entity
{
public:
    Entity(const String& name)
        :m_Name(name)
    {

    }

    Entity(String&& name)
        :m_Name(std::move(name))
    {

    }

    void PrintName()
    {
        m_Name.Print();
    }

private:
    String m_Name;
};

int main()
{
    Entity entity = String("Giskard");
    entity.PrintName();

    std::cin.get();
}
```

---

# std::move与移动赋值操作符

```cpp
#include <iostream>

class String
{
public:
    String(const char* string)
    {
        std::cout << "Created!\n";
        m_Size = strlen(string);
        m_Data = new char[m_Size];
        memcpy(m_Data, string, m_Size);
    }

    String(const String& other)
    {
        std::cout << "Copied!\n";

        m_Size = other.m_Size;
        m_Data = new char[m_Size];
        memcpy(m_Data, other.m_Data, m_Size);
    }

    String(String&& other) noexcept
    {
        std::cout << "Moved!\n";

        m_Size = other.m_Size;
        m_Data = other.m_Data;
        memcpy(m_Data, other.m_Data, m_Size);

        other.m_Size = 0;
        other.m_Data = nullptr;
    }

    String& operator=(String&& other) noexcept
    {
        std::cout << "Moved!\n";

        if(this!=&other)
        {
            delete[] m_Data;

            m_Size = other.m_Size;
            m_Data = other.m_Data;
            memcpy(m_Data, other.m_Data, m_Size);

            other.m_Size = 0;
            other.m_Data = nullptr;
        }

        return *this;
    }

    ~String()
    {
        std::cout << "Destroyed!\n";
        delete[] m_Data;
    }

    void Print()
    {
        for (uint32_t i = 0; i < m_Size; i++)
        {
            std::cout << static_cast<char>(m_Data[i]);
        }
        std::cout << '\n';
    }

private:
    uint32_t m_Size;
    char* m_Data;
};

class Entity
{
public:
    Entity(const String& name)
        :m_Name(name)
    {

    }

    Entity(String&& name)
        :m_Name(std::move(name))
    {

    }

    void PrintName()
    {
        m_Name.Print();
    }

private:
    String m_Name;
};

int main()
{
    /*Entity entity = String("Giskard");
    entity.PrintName();*/

    String apple = "Apple";
    String dest = std::move(apple);

    std::cout << "Apple: ";
    apple.Print();
    std::cout << "Dest: ";
    dest.Print();

    std::cin.get();
}
```

---

# 自己写C++数据结构(Array数组)

```cpp
#include <iostream>
#include <array>

template<typename T, size_t S>
class Array
{
public:
    //constexpr允许函数在编译时调用
    constexpr int Size() const { return S; }

    T& operator[](size_t index) {
        if (!(index < S))
        {
            __debugbreak();
        }
        return m_Data[index];
    }
    const T& operator[](size_t index) const { return m_Data[index]; }

    T* Data() { return m_Data; }

    const T* Data() const { return m_Data; }
private:
    T m_Data[S];
};


int main()
{
    int size = 5;
    Array<int, 5> data;

    const auto& arrayReference = data;

    //数组填充
    memset(data.Data(), 0, data.Size() * sizeof(int));

    //编译阶段判断条件
    static_assert(data.Size() < 10, "Size is too large!");

    for (size_t i = 0; i < data.Size(); i++)
    {
        std::cout << data[i] << std::endl;
    }

    std::cin.get();
}
```
