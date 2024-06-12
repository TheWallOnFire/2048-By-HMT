# 2048 for Window

## Description
This is my version of the legendary game 2048, you can read more about it from [here](https://en.wikipedia.org/wiki/2048_(video_game))
This version of mine is available on WINDOW only, utilizing <windows.h> Library and its functions
Main language: C++
Version: 1.0.0

## Table of Contents (Optional)
- [Feature](#features)
- [Installation](#installation)
- [Test](#tests)


## Features

- Game 2048 on window platform.
- Has friendly GUI.
- Support multiple game at the same time.
- Saving data to slot for future play.
- Show leaderboard and top players.
- Has tutorial
  
## Installation
I use Microsoft Visual Studio to make this app.
The version:


1. Console folder
This folder is used for debugging code.
Build this folder if you want to play game using terminal.

2. Window folder
Main game that inherits from Console folder, with <windows.h> library to create game UI.
Setup guide: Open Properties of this Folder, on top of Dialog, select All Configurations and All Platforms
- On Configuartion Property > General > Configuration Type: select Application (.exe)
- On Configuartion Property > General > C++ Language Standard: select C++ 14
- On Configuartion Property > Advanced > Character Set: select Unicode
Make sure you set to these option before build the project
- On the menu above, select Release and x64
- Press F7 to build project and press F5 to run it
  
3. Unit Test
This folder is for testing the app that I used when making this project.

| Chức năng                                                                                 | Điểm |
|-------------------------------------------------------------------------------------------|------|
| Hiển thị được giao diện kèm chức năng của hai màn hình chính                               | 0.1  |
| Thực hiện được chức năng nhập tên và kiểm tra tính trùng lắp                              | 0.1  |
| Thực hiện được chức năng cài đặt độ lớn của bàn cờ                                        | 0.1  |
| Thực hiện được việc lưu trữ thông tin người chơi                                          | 0.1  |
| Thực hiện được chức năng Resume                                                           | 0.2  |
| Thực hiện được chức năng Exit                                                             | 0.1  |
| Thực hiện được logic trong trò chơi như phát sinh ngẫu nhiên, di chuyển, hiển thị trò chơi, hiển thị điểm, v.v | 1.0  |
| Thực hiện được chức năng undo, undo và redo                                               | 0.2  |
| Hiển thị các thông báo và nội dung tương ứng                                              | 0.1  |
| Tổ chức thành các file rõ ràng                                                            | 0.2  |
| Có sử dụng phương thức đồ hoạ kèm giao diện thân thiện                                    | 0.2  |
| Cài đặt được cách thức mã hoá tệp tin                                                     | 0.2  |
| Cài đặt được chức năng Resume cho năm tài khoản                                           | 0.4  |
## Tests

## Screenshot

