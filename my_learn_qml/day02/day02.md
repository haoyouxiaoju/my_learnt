##### 在连接槽函数和信号时[Connections的Qt6官方文档地址](https://doc.qt.io/qt-6/qml-qtqml-connections.html)

```
//如此编写会出现clr没有定义,虽然只是一个info但还是要减少此类消息的出现
//即cmd中会出现`Parameter "clr" is not declared. Injection of parameters into signal handlers is deprecated. Use JavaScript functions with formal parameters instead.`
Connections{
        target:blueLoader.item;
        onColorPicked:{
            colorText.color = clr;
        }
}
//
//Qt6中对于Connections的连接应该时需要以function的形式 即
Connections{
        target:redLoader.item;
        function onColorPicked(clr){
            colorText.color = clr;
        }
}
```

还有另一个链接方式,个人更偏向此种写法,和Qt Widget的信号与槽函数链接方式比较相似

```
Component.onCompleted: {
        redLoader.item.colorPicked.connect(setTextColor);
        blueLoader.item.colorPicked.connect(setTextColor);
}
function setTextColor(clr){
        colorText.color = clr;
}
```



##### 在Qml中new Array()的警告

```
property var dynamicObjects : new Array();
//书中使用到了new一个数组,但是在Qt6.8中使用会出现
//Do not use "Array" as a constructor.
//For more information,see the "Checking Code Syntax" documentation

//推荐的写法
roperty var dynamicObjects :Array();
roperty var dynamicObjects : [];
```

[从 JavaScript 动态创建 QML 对象 |Qt Qml |Qt 6.9.0](https://doc.qt.io/qt-6/qtqml-javascript-dynamicobjectcreation.html)

[QML 类型系统 |Qt Qml |Qt 6.9.0 版本](https://doc.qt.io/qt-6/qtqml-typesystem-topic.html)

[Array（） 构造函数 - JavaScript |MDN 系列](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array/Array)



##### 书中P151，使用到了数组的slice但是不起效果

```
//书中P151，使用到了数组的slice但是不起效果，在数组大小为1时能正常获取数组最后一个元素
//从参考文档中查看也没发现有具体问题,这里提醒一下slice(-1,1)复制出的时[-1,1)左闭右开的区间,
//所以正常item应该时俩个元素 -1,0 
var item = rootItem.dynamicObjects.slice(-1,1)
item[0].destroy();

//推荐
var item = rootItem.dynamicObjects.slice(-1)
或
var item = rootItem.dynamicObjects.pop()
```

[Array.prototype.pop（） - JavaScript |MDN 系列](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array/pop)

[Array.prototype.slice（） - JavaScript |MDN 系列](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array/slice)
