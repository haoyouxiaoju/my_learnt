##### Q_ENUMS宏已弃用虽能使用,使用Q_ENUM

[QObject Class | Qt Core | Qt 6.9.0](https://doc.qt.io/qt-6/qobject.html#Q_ENUM)

[Obsolete Members for QObject | Qt Core | Qt 6.9.0](https://doc.qt.io/qt-6/qobject-obsolete.html#Q_ENUMS)



今天看到了`QColor color() const;`有感const的作用:const此处强调此函数为成员函数,不修改成员变量(非mutable修饰变量),编译器会进行检测是否发生修改

还有其他const修饰的用法

|         声明方式         | 指针是否可变 | 指向数据是否可变 |           典型用法           |
| :----------------------: | :----------: | :--------------: | :--------------------------: |
|        const int         |      -       |    数据不可变    |         定义常量整数         |
| const int* 或 int const* |   指针可变   |    数据不可变    |   函数参数保护数据不被修改   |
|        int* const        |  指针不可变  |     数据可变     | 固定指针地址但仍允许修改数据 |
|     const int* const     |  指针不可变  |    数据不可变    | 完全不可变的指针（较少使用） |

##### qsrand()弃用

Qt 5.10 之前：`qsrand()` 和 `qrand()` 是线程不安全的（共享全局状态）。

Qt 5.10 及之后：**废弃**了这两个函数，建议改用 C++11 的 `<random>` 库（如 `std::mt19937`）。

##### P260的图片处理例子(浮雕效果不行)

```
//例子中还在使用def void(*AlgorithmFunction)(QString,QString)
// 个人倾向于新的特性,使用using和function库来定义函数类型更简明直了
using AlgorithmFunction = std::function<void(QString,QString)>;
```

##### 将例子中的_soften处理函数进行优化

书中的_soften就直接switch()写了9个case每个case再重复x和y的计算

写过一些dfs类的算法题应该就会想到使用[529. 扫雷游戏 - 力扣（LeetCode）](https://leetcode.cn/problems/minesweeper/description/?envType=problem-list-v2&envId=depth-first-search)

`int ds[9] = {-1,0,1,1,1,0,-1,-1,0};int dp[9] = {-1,-1,-1,0,1,1,1,0,0};`来简化代码

```
void __soften(QString sourceFile,QString destFile){
    // 移除 "file:///" 前缀（如果存在）
    if (sourceFile.startsWith("file:///")) {
        sourceFile.remove(0, 8);  // 移除前8个字符（"file:///"）
    }
    // 检查文件是否存在
    if (!QFile::exists(sourceFile)) {
        qDebug() << "File not found:" << sourceFile;
        return;
    }
    QImage image(sourceFile);
    if(image.isNull()){
        qDebug()<<"load"<<sourceFile<<" failed!";
        return;
    }
    int width = image.width();
    int height = image.height();
    int r,g,b;
    QRgb color;
    int xLimit = width -1;
    int yLimit = height -1;
    int ds[9] = {-1,0,1,1,1,0,-1,-1,0};
    int dp[9] = {-1,-1,-1,0,1,1,1,0,0};
    for(int i=1;i<xLimit;++i){
        for(int j=1;j<yLimit;++j){
            r=g=b=0;
            for(int m=0;m<9;m++){
                int s =i+ds[m];
                int p =j+dp[m];
                color = image.pixel(s,p);
                r += qRed(color);
                g += qGreen(color);
                b += qBlue(color);
            }
            r =qMin(255,qMax(0,(int)(r/9.0))) ;
            g =qMin(255,qMax(0,(int)(g/9.0))) ;
            b =qMin(255,qMax(0,(int)(b/9.0))) ;
            image.setPixel(i,j,qRgb(r,g,b));
        }
    }
    image.save(destFile);
}
```

##### 包括实际运行中发现QImage没办法处理带"file:///"前缀的路径,可能或许后续会进行修改吧,毕竟不能让qml和c++的混合编程,qml文件里能识别"file:///"而cpp文件里不能识别

```
 // 移除 "file:///" 前缀（如果存在）
    if (sourceFile.startsWith("file:///")) {
        sourceFile.remove(0, 8);  // 移除前8个字符（"file:///"）
    }
    // 检查文件是否存在
    if (!QFile::exists(sourceFile)) {
        qDebug() << "File not found:" << sourceFile;
        return;
    }
```

