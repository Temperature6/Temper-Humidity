import time
import xlsxwriter

start_time = 1627477200  # 2021/07/28 21：00
sleep_time = 1  # 采样间隔(min)
runtime = 24*60  # 运行时间(min)
data_file = "data.txt"
temp_list = []
humidity_list = []
time_list = []


def format_time(sec):
    format_ = "%H:%M"
    time_tuple = time.localtime(sec)
    time_str = time.strftime(format_, time_tuple)
    return time_str


def write_xlsx():
    # 表头
    workbook = xlsxwriter.Workbook('data.xlsx')
    worksheet = workbook.add_worksheet("温湿度数据")
    # 参数1为行，参数2为列
    worksheet.write(0, 0, '时间')
    worksheet.write(0, 1, "温度")
    worksheet.write(0, 2, "湿度")
    # 写入处理后的数据
    for a in range(len(time_list)):  # 时间列
        worksheet.write(a + 1, 0, time_list[a])
    for b in range(len(temp_list)):  # 温度列
        worksheet.write(b + 1, 1, temp_list[b])
    for c in range(len(humidity_list)):  # 湿度列
        worksheet.write(c + 1, 2, humidity_list[c])
    # 关闭文件
    workbook.close()
    return


def process_data(filename):
    f = open(filename)
    origin_data = f.read().split("\n")
    first_ = []
    for i in origin_data:
        if i != '':
            first_.append(i)

    temp = []  # 温度
    hum = []  # 湿度

    for j in first_:
        _i = j.split(",")
        temp.append(int(_i[0]))
        hum.append(int(_i[1]))

    return temp, hum


if __name__ == "__main__":
    s_time = time.time()
    temp_list, humidity_list = process_data("data.txt")
    for k in range(int(runtime / sleep_time)):
        time_list.append(format_time(start_time + k * sleep_time * 60))
    write_xlsx()
    e_time = time.time()
    print("处理完成，用时{0}秒".format(round(e_time - s_time, 2)))
