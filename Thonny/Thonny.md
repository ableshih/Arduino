Thonny  
```
thonny-3.2.7.exe

[其他 python 程式要關閉 如 Anaconda]
(分 本機模式[關開電就不見] 與 裝置模式[燒到板子裡])


1. 安裝
2. 開啟 Thonny
3. Tools -> Options -> Interpreter (選好板子) -> OK -> 關 開 Thonny
4. Run -> Stop/Restart backend Ctrl+F2 (init 板子)
5. Files區 就會出現 板子裡目前程式

6. 在本地開啟程式 -> Run (就會 直譯 出現效果) [斷電在上電就不見]

7. Files區 板子一開啟只會抓 boot.py (在本區測試成功的程式，複製貼上到 boot.py 關開板子就可)


就是有點 micro-bit 的作法

左邊有 兩區 Files區，This computer區
1. 程式 要從 This computer區 Upload to / (在 三 的小icon點一下)
2. 程式在 MicroPython device 就表示已經燒到板子裡了
3. 硬體要先接好否則會出現錯誤




---
Files
---
MicroPython device
---
程式
---

This computer
```
