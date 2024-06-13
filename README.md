# 2048 for Window

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Configuration](#configuration)
- [Uses](#uses)
- [License](#license)
- [Screenshot](#screenshots)
- [Ratings](#ratings)

## Introduction

This is my version of the legendary game 2048, you can read more about it from [here.](https://en.wikipedia.org/wiki/2048_(video_game))  
This version of mine is available on WINDOW only, utilizing <windows.h> Library and its functions.  
Main language: C++  
Version: 1.0.0 (12/6/2024)  

## Features
These are some features of the app:
- Run on Window platform.
- Has a friendly, modern GUI.
- Support multiple games at the same time.
- Saving data to 5 slots for resuming in the future.
- Show leaderboard and top 20 players.
- Using UNICODE character set instead of ASCII set.

### Prerequisites
- Download Microsoft Visual Studio using version 2022.
- Download the package: Desktop development with C++.
- Download C++14 on your machine (this usually comes with Visual Studio).
  
### Installation
1. Get a copy of the project locally (via GitHub or download ZIP).
2. Navigate to the main folder: There are 3 projects on the solution: Console, Window, and Test2048.
3. Build and run the Window project, the other two can be left alone.

## Configuration
1. Console folder
This folder is used for debugging code.
Build and run this folder if you want to use the terminal.
Keep the basic configuration for the C++ project

2. Window folder
The main game that inherits from the Console, with <windows.h> library to create game UI.

### Setup guide: 
Begin with Set Startup Project and open Properties Dialog by right click on the project:

- On top of Dialog, select All Configurations and All Platforms.
You can change this if you want the Debug and Release Configurations separate.

- On Configuration Property > General > Configuration Type: select Application (.exe).

- On Configuartion Property > General > C++ Language Standard: select C++ 14.

- On Configuartion Property > Advanced > Character Set: select Unicode.
The app uses UNICODE for display text so the Character set must be Unicode.

Make sure you set to these options before building the project.
- On the menu above, select Release and x64.
- Press F7 to build project and press F5 to run it.

## License
This project is licensed under the [MIT License](LICENSE).

## Screenshots
Here is the [link](https://drive.google.com/drive/folders/1-LT1vTy5leWVvDbmZCV2kdO8woZh3bEi)
to screenshots and testting videos

## Ratings

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
