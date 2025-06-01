# learning_qml
存储学习qml期间的体会

### 使用的是<<Qt Quick核心编程>>

由于此书是Qt5的教学内容,而我使用的是Qt6.8.2,截至目前发现了一些差异

- 书中使用到了QtQuick.Controls.Styles模块,但Qt6 已经删除了此模块.

- 在书中实现槽函数的时候,会出现警告参数event未定义,

  ```c++
  例如书中键盘按钮移动文本例子中:
  Keys.onPressed:{switch(event.key){}event.accepted = true;}
  就会出现event未定义只需要添加  `(event)=>`  就可以取消此警告
  Keys.onPressed:(event)=>{switch(event.key){}event.accepted = true;}
  ```


- 在Main.qml中使用其他qml文件时发现qml文件命名首字母得大写,否则无法识别到(挺疑惑的)
- qml更加贴近于js,qt6貌似也倾向于有具体类型的数据了
- 使用Connections连接信号和槽函数时,qt6书写方式发生改变,直接查看[day02](./day02/day02.md)
- Qt6不再使用Component定义控件的Sytle样式做原型,由于Styles模块已移除且Component已不再用于自定义组件[day03](./day03/day03.md)
- TabView 替换方案[day04](./day04/day04.md)
- Qml 图片显示不出来的问题,简单说一下就是缺少一个选项没开启,官方文档居然没有强调.具体查看[day04](./day04/day04.md)
- Q_ENUMS宏已弃用虽能使用,使用Q_ENUM[day06](./day06/day06.md)
- qsrand()弃用[day06](./day06/day06.md)
- QImage没办法处理带"file:///"前缀的路径[day06](./day06/day06.md)
- 自定义model[day08](./day08/day08.md)



[Qt6 QML Book: A Detailed Guide to Using Qt](https://www.qt.io/product/qt6/qml-book)

[免费编程课程 |Qt Academy 课程目录](https://www.qt.io/academy/course-catalog)

学习进度

##### day_01--2025/4/20 

观看第1~6章,完成初识qml

##### day_02--2025/4/21

完成6~7章结束

##### day_03\day_04\day_05--2025/4/25

8-10章,布局内容没多看,第九章的自定义控件倒是收获很多,对比qtwidget我个人认为更加操作简单,而且官方文档也非常详细的有自定义控件的模板.[自定义 Qt Quick Controls |Qt 快速控制 |Qt 6.9.0 版本](https://doc.qt.io/qt-6/qtquickcontrols-customize.html#creating-a-custom-style).同时在看canvas时想起自己也写过一个验证码的控件,于是自己使用qml复刻了一下,非常期待后面的内容

##### day06-8--2025/5/2

gridView和PathView就没看

findImage:QML多界面切换太多了不想写和改

##### day09 --2025/5/4

结束--后面没怎么写,qt6的变化还是太大了
