#include <iostream>
#include <cstdlib> // Для функции rand()
#include <ctime>
#include <cmath>
#include <chrono>
#include <fstream> // Для записи в файл

// Алгоритм перебора
bool isPrimeSequential(unsigned long long n) {
    if (n <= 1) return false; // 0 и 1 не являются простыми числами
    if (n <= 3) return true; // 2 и 3 являются простыми числами
    if (n % 2 == 0) return false; // Четные числа больше 2 не простые

    for (unsigned long long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            return false; // Найден делитель, число не простое
        }
    }
    return true; // Число простое
}

// Алгоритм случайного поиска
bool isPrimeRandom(unsigned long long n, int iterations = 100) {
    if (n <= 1) return false; // 0 и 1 не являются простыми числами
    if (n <= 3) return true; // 2 и 3 являются простыми числами
    if (n % 2 == 0) return false; // Четные числа больше 2 не простые

    // Инициализация генератора случайных чисел
    std::srand(static_cast<unsigned int>(std::time(0)));

    for (int i = 0; i < iterations; ++i) {
        unsigned long long a = 2 + std::rand() % (n - 3); // Случайное число от 2 до n-2
        if (a % n == 0) continue; // Пропускаем, если a делится на n
        if (isPrimeSequential(a) && n % a == 0) {
            return false; // Найден делитель, число не простое
        }
    }
    return true; // Число, вероятно, простое
}

// Функция для возведения в степень по модулю пошаговое
unsigned long long modularExponentiation(unsigned long long base, unsigned long long exp, unsigned long long mod) {
    unsigned long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) { // Если exp нечетное
            result = (result * base) % mod; // Умножаем результат на base и берем модуль
        }
        exp = exp >> 1; // Делим exp на 2
        base = (base * base) % mod; // Возводим base в квадрат и берем модуль
    }
    return result;
}

// Тест Миллера-Рабина
bool millerRabinTest(unsigned long long n, int k) {
    if (n <= 1) return false; // 0 и 1 не являются простыми
    if (n <= 3) return true; // 2 и 3 являются простыми

    // Найдем d такое, что n = 2^r * d + 1
    unsigned long long d = n - 1;
    int r = 0;
    while (d % 2 == 0) {
        d /= 2;
        r++;
    }

    // Выполняем k тестов
    for (int i = 0; i < k; i++) {
        // Генерируем случайное число a в диапазоне [2, n-2]
        unsigned long long a = 2 + rand() % (n - 3); // Изменено на (n - 3), чтобы избежать деления на 0
        // Вычисляем x = a^d mod n
        unsigned long long x = modularExponentiation(a, d, n);

        if (x == 1 || x == n - 1) {
            continue; // Условие выполнено, продолжаем
        }

        bool composite = true;
        for (int j = 0; j < r - 1; j++) {
            x = modularExponentiation(x, 2, n);
            if (x == n - 1) {
                composite = false; // Найдено, что n вероятно простое
                break;
            }
        }

        if (composite) {
            return false; // Найдено, что n составное
        }
    }
    return true; // n вероятно простое
}

// Тестирование определенного числа
void test_number()
{
    unsigned long long number;

    std::cout << "Введите число (до 2^64 - 1): ";
    std::cin >> number;
    int k = 10; // Количество тестов

    // Проверка с помощью последовательного перебора
    if (isPrimeSequential(number)) {
        std::cout << number << " является простым числом (последовательный перебор)." << std::endl;
    } else {
        std::cout << number << " не является простым числом (последовательный перебор)." << std::endl;
    }

    // Проверка с помощью случайного поиска
    if (isPrimeRandom(number)) {
        std::cout << number << " является простым числом (случайный поиск)." << std::endl;
    } else {
        std::cout << number << " не является простым числом (случайный поиск)." << std::endl;
    }

    if (millerRabinTest(number, k)) {
        std::cout << number << " является вероятно простым числом(Миллер)." << std::endl;
    } else {
        std::cout << number << " не является простым числом(Миллер)." << std::endl;
    }
}

// Проверка на время выполнения
void test_zero()
{
// Тест0
    int k = 10; // Количество тестов
    std::cout << "Проверка на простоту больших чисел двумя способами:" << std::endl;

    // Начало замера времени
    auto start_one = std::chrono::high_resolution_clock::now();
    for (unsigned long long number = 30000000; number <= 50000000; number++) {
        isPrimeSequential(number);
    }
    // Конец замера времени
    auto end_one = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_one = end_one -start_one;

    // Начало замера времени
    auto start_two = std::chrono::high_resolution_clock::now();
    for (unsigned long long number = 30000000; number <= 50000000; number++) {
        millerRabinTest(number, k);
    }
    // Конец замера времени
    auto end_two = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_two = end_two - start_two;
    std::cout << "Время выполнения теста перебором: " << duration_one.count() << " секунд." << std::endl;
    std::cout << "Время выполнения теста Миллера: " << duration_two.count() << " секунд." << std::endl;
    // Для больших чисел тест Миллера дает лучший результат
    // Для небольших чисел полный перебор может быть предпочтительным, в то время как для больших чисел лучше использовать тест Миллера-Рабина.
    // Процессор полностью загружает одно ядро. Память не расходуется.
}

void test_one()
{
// Тест1
    int k = 10; // Количество тестов

    std::ofstream outputFile("./execution_times_one.csv"); // Открываем файл для записи
    // Записываем заголовок
    outputFile << "Number,Time" << std::endl;

    std::cout << "Проверка на простоту чисел от 1 до 65537:" << std::endl;
    for (unsigned long long number = 1; number <= 65537; number++) {
        // Начало замера времени
        auto start = std::chrono::high_resolution_clock::now();

        if (millerRabinTest(number, k)) {
            std::cout << number << " является вероятно простым числом." << std::endl;
        } else {
            // std::cout << number << " не является простым числом." << std::endl;
        }
        // Конец замера времени
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        // std::cout << "Время выполнения: " << duration.count()*100000 << " микро секунд." << std::endl;

        // Записываем номер и время выполнения в файл
        outputFile << number << "," << duration.count()*1000000 << std::endl;
    }
    outputFile.close(); // Закрываем файл
}

void test_two()
{
    int k = 10; // Количество тестов

    std::ofstream outputFile("./execution_times_two.csv"); // Открываем файл для записи
    // Записываем заголовок
    outputFile << "Number,Time" << std::endl;

    std::cout << "Проверка на простоту чисел вида 2^N - 1 и 2^N + 1 для N от 16 до 32:" << std::endl;
    for (int N = 16; N <= 32; N++) {
        // Начало замера времени
        auto start = std::chrono::high_resolution_clock::now();

        unsigned long long number1 = (1ULL << N) - 1; // 2^N - 1
        unsigned long long number2 = (1ULL << N) + 1; // 2^N + 1


        // Проверка числа 2^N - 1
        if (millerRabinTest(number1, k)) {
            std::cout << number1 << " (2^" << N << " - 1) является вероятно простым числом." << std::endl;
        } else {
            // std::cout << number1 << " (2^" << N << " - 1) не является простым числом." << std::endl;
        }

        // Проверка числа 2^N + 1
        if (millerRabinTest(number2, k)) {
            std::cout << number2 << " (2^" << N << " + 1) является вероятно простым числом." << std::endl;
        } else {
            // std::cout << number2 << " (2^" << N << " + 1) не является простым числом." << std::endl;
        }

        // Конец замера времени
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        // Записываем номер и время выполнения в файл
        outputFile << N << "," << duration.count()*1000000 << std::endl;
    }
}

void test_three()
{
    int k = 10; // Количество тестов
    // Инициализация генератора случайных чисел
    // Генерация случайного числа в диапазоне [2^32, 2^64 - 1]
    unsigned long long lower_bound = 1ULL << 32; // 2^32 сдвинуть число 1 влево на 2 бита. Каждый сдвиг влево эквивалентен умножению на 2. 32 - количество позиций на сколько мы сдвигаем влево
    unsigned long long upper_bound = ~0ULL; // 2^64 - 1  Здесь ~0ULL создает число, у которого все 64 бита установлены в 1, что эквивалентно 2^64−1.
    unsigned long long random_number = lower_bound + (std::rand() % (upper_bound - lower_bound + 1));

    // Проверка на простоту
    if (millerRabinTest(random_number, k)) {
        std::cout << random_number << " random является вероятно простым числом." << std::endl;
    } else {
        std::cout << random_number << " random не является простым числом." << std::endl;
    }
}

int main() {
    // Инициализация генератора случайных чисел
    std::srand(static_cast<unsigned int>(std::time(0)));

    std::cout << "Введите номер теста от нуля до четырех" << std::endl;
    std::cout << "0 - проверка на время выполнения" << std::endl;
    std::cout << "1 - задание 1" << std::endl;
    std::cout << "2 - задание 2" << std::endl;
    std::cout << "3 - задание 3" << std::endl;
    std::cout << "4 - проверим введенное число" << std::endl;

    int test_numbers;
    std::cin >> test_numbers;
    
    if(test_numbers == 0) test_zero();
    else if(test_numbers == 1) test_one();
    else if(test_numbers == 2) test_two();
    else if(test_numbers == 3) test_three();
    else if(test_numbers == 4) test_number();
    else exit(EXIT_FAILURE);

    return 0;
}