# 温湿度记录仪

### 材料

​	Arduino UNO、DT11温湿度传感器、DS1302时钟模块、SD卡读写模块、若干导线

### 用法

​	按代码所示接好线后插电

​	如果上电后灯L一直亮说明SD卡初始化失败

![]( [Temper-Humidity/pic.jpg at main · Temperature6/Temper-Humidity (github.com)](https://github.com/Temperature6/Temper-Humidity/blob/main/pic.jpg) )

### 处理数据

​	将储存卡中的“data.txt”放到DataProcess文件夹里面，运行main.py，获得处理好的电子表格文件

​	（需要安装“xlsxwriter”模块）