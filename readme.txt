mce.cpp部分
struct number:
	vector<short> date中的每一位都代表当前位置上的数字
	uint64_t size带表数字整数的位数
	int pom 带表数字的正负
函数内容:
	bool parse_number(string str, number& num)对number的解析,查看number的格式是否符合,主要是在tui.cpp中有用
	inline number number_get() 从键盘读入number
	inline long long  i_read() 整形快读
	inline long double f_read()浮点型快读
	inline number str_to_number(string str) 将字符串转化为number类型
	inline void  number_out_wt(number outnumber)最基础的number输出
	inline number accurate_to(number number, uint64_t i)将number精确到小数点后i位
	inline void print(number original_number, uint64_t i)输出number精确到小数点后i位的结果
	inline void print(number original_number)同上,默认精确到小数点后30位
	inline number add(number number1, number number2)将两个number相加(若pom不同就是绝对值相减,并且返回时pom为绝对值较大的number的pom)
	inline bool number_greater(number number1, number number2)若number1大于number2返回true,否则返回false
	inline bool number_less(number number1, number number2)若number1小于number2返回true,否则返回false
	inline bool equal(number number1, number number2)若number1等于number2返回true,否则返回false
	inline bool equaltozero(number number)若number1等于0返回true,否则返回false
	inline number multiplication(number number1, number number2)将两个number相乘,默认精度到小数点后100位
	inline number multiplication(number number1, number number2,uint64_t i)同上,默认精度到小数点后i位
	inline number division(number number1, number number2)将两个number相除,默认精度到小数点后100位
	inline number division(number number1, number number2,uint64_t npo) 将两个number相除,默认精度到小数点后npo位
tui.cpp:
	请见代码注释,不是我写的
