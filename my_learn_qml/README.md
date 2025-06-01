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
