# 實習用

此目錄用以存放建立者於2024年大學實習課程，於履歷中提及的代碼之儲存。

此目錄包含下列專案：
- shm1121_1.cpp
- pthread.cpp
- NumProcessingUsingThread.cpp
- AddWithoutOperator.cpp
- SimpleIdleGame_NoSave.cpp



## shm1121_1.cpp
此專案為猜數字遊戲模擬之實作，以兩個Process模擬兩人進行猜數字遊戲的進程。

此專案執行包含兩個參數，分別作為模擬進程之謎底與猜測數字的亂數產生之種子。
### 測試環境
此專案採用Ubuntu Desktop 22.10作為測試環境，並採用GCC作為程式之編譯。



## pthread.cpp
此專案為盧卡斯數（Lucas number）計算之實作。

此專案執行包含至少一個參數，對於每個鍵入之參數，計算其Lucas number的值與位數，同時印出計算其thread之ID。
### 測試環境
此專案採用Ubuntu Desktop 22.10作為測試環境，並採用GCC作為程式之編譯。



## NumProcessingUsingThread.cpp
此專案為多種數列計算（Lucas sequence, Fibonacci sequence, Odd sequence, Tribonacci sequence）之實作。

此專案允許使用者鍵入多筆資料，並依據所選之類型計算。

**範例輸入：**

```
5
1 5
2 3 
3 6
1 4
1 1
```

**輸出結果：**

```
Fibonacci(5) is 5.
Lucas(3) is 4.
Odd(6) is 11.
Fibonacci(4) is 3.
Fibonacci(1) is 1.
```

### 測試環境
此專案採用Windows 11 home 23H2作為測試環境，並採用GCC作為程式之編譯。



## AddWithoutOperator.cpp
此專案為提供多個整數加總且不含"+"之運算符號之實作。

此專案需使用者鍵入資料筆數及每一筆資料（整數型態），並輸出所有資料之加總。

**範例輸入**

```
5
1 0 0 2 3
```

**輸出結果：**

```
6
```

### 測試環境
此專案採用Windows 11 home 23H2作為測試環境，並採用GCC作為程式之編譯。



## SimpleIdleGame_NoSave.cpp
此專案為簡易放置遊戲之實作。

遊戲內容為通過放置及被動收穫資源（coins），並可通過消耗資源升級收穫資源的速度。

**注意：** 本遊戲不支援存檔功能，任何通過本程式進行儲存的遊戲檔案僅於程式執行時生效。

### 測試環境
此專案採用Windows 11 home 23H2作為測試環境，並採用GCC作為程式之編譯。



## 備註
此為建立者初次嘗試建立readme文本，若有不足之處，敬請見諒！
