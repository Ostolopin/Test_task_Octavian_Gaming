Test_task_Octavian_Gaming  – это симулятор слот-машины, реализованный на C++ с использованием OpenGL и GLUT.

Функциональные возможности
Вращение барабанов:
Эмуляция вращения барабанов с возможностью автоцентрирования в зависимости от количества барабанов.

Интерактивный интерфейс:
Управление игрой происходит через графические кнопки (Start, Stop, Credit, Exit), размещённые в полноэкранном режиме. Панель сообщений выводится справа от кнопок и автоматически оборачивает длинные сообщения.

Машина состояний:
Игра разделена на состояния: IdleState (ожидание действия), SpinningState (вращение) и WinState (расчёт выигрыша). Логика выигрыша рассчитывается в зависимости от количества совпадающих символов:

Для двух одинаковых символов – стоимость складывается (2×base);
Для трёх и более – стоимость перемножается (base^count), за исключением символа A, для которого, если его выпадает более двух, выигрывается просто количество повторений.
Кредитная система:
Игрок начинает с фиксированного баланса. Если средств недостаточно для игры, появляется возможность взять кредит (получить 20 евро, долг 50 евро). При выигрыше 50 % суммы автоматически идут на погашение долга.

Структура проекта
1. src/
    main.cpp           # Точка входа, настройка OpenGL и GLUT, главный цикл приложения
    SlotMachine.cpp    # Основной класс SlotMachine, отрисовка интерфейса и элементов игры
    SlotMachine.h
    Button.cpp         # Класс Button для отрисовки кнопок
    Button.h
    Reel.cpp           # Класс Reel для эмуляции вращения барабанов
    Reel.h
    StateMachine.cpp   # Класс StateMachine для управления состояниями игры
    StateMachine.h
    Vec2.h             # Простая структура для векторных координат
    TextUtils.cpp      # Функции для измерения и обёртывания текста
    TextUtils.h
   2. States/            # Папка с реализациями состояний
         IdleState.cpp
         IdleState.h
         SpinningState.cpp
         SpinningState.h
         WinState.cpp
         WinState.h
Зависимости
C++17 – язык программирования.
OpenGL – для рендеринга графики.
FreeGLUT/GLUT – для работы с окном, обработки ввода мыши и клавиатуры.
CMake (версия 3.10 и выше) – для генерации файлов сборки (поддерживаются сборка для Windows (Visual Studio), Linux и т.д.).
В папке x64-release находится собранный проект.
