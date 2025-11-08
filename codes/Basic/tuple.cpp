int main() {
    tuple<int, double, string> myTuple(100, 3.14, "hello world");
    tuple<int, double, string> anotherTuple = make_tuple(100, 18, "Tom");
    cout << get<0>(myTuple) << "\n"; // 取得第一個元素
    auto [a, b, c] = myTuple;
    get<1>(myTuple) = 5.43; // 修改第二個元素的值

    int a;
    double b;
    string c;
    tie(a, b, c) = myTuple;
}