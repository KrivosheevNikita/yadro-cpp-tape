## Tape
Тестовое задание, выполненное  в рамках отбора на стажировку в YADRO.

[Исходное тестовое задание](https://github.com/KrivosheevNikita/yadro-cpp-tape/blob/main/Исходное%20задание.png)

## Сборка
```bash
git clone https://github.com/KrivosheevNikita/yadro-cpp-tape.git
cd yadro-cpp-tape
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
```
## Запуск
```bash
./tape_sorter ../config.json ../input_example.txt ../output.txt
```

## Используемые технологии
- C++20
- CMake

