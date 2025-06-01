### TabView 替换方案

Qt6就取消了TabView控件,从搜索到的解决方案就是TabBar+StackLayout来自己实现,同时,因为StackLayout本身就没有添加子控件的方法所以使用TabBar+StackLayou解决方案就没有了原本TabView的addItem的方法,不过也没什么大影响.

[Alternative to TabView in Qt 6? | Qt Forum](https://forum.qt.io/topic/132653/alternative-to-tabview-in-qt-6/2)

### Qml 图片显示

```
// 注意：添加 file:/// 前缀表示本地文件协议
source: "file:///D:/avatar7.jpg"
//网络连接显示,这点我觉得挺厉害的
source: "https://tse3-mm.cn.bing.net/th/id/OIP-C.HjYIizKCiIsDIj-Dvm-udQAAAA?rs=1&pid=ImgDetMain";

最最重要的是使用qrc来控制图片资源,也是困扰了我几个小时
参考下方链接qt6.4 qml无法使用资源图片_qml image: cannot open:-CSDN博客`

虽然Qt creator 在创建qrc文件时会在cmake中添加到qt_add_qml_module
但是还是缺少一句 set(CMAKE_AUTORCC ON)
如果不设置CMAKE_AUTORCC打开,那么图片就无法正常打开
```

[qt6.4 qml无法使用资源图片_qml image: cannot open:-CSDN博客](https://blog.csdn.net/sunflower_2020/article/details/134861936)