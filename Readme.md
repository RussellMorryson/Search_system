# **Задание**

## Напишите реализацию поиска по базе документов. 
Используйте следующий алгоритм:

- Взять очередной документ из базы документов. Вы уже знаете, что это вектор слов документа.
- Добавить индекс документа в результаты поиска, если среди слов этого документа встречаются слова из поискового запроса.
- Повторить эти действия для оставшихся документов.

Так как в базе документов не содержатся стоп-слова, лучше сразу исключить их из поискового запроса.

## **Сигнатура функции поиска должны выглядеть так:**

    // Возвращает массив id документов, подходящих под запрос query
    // Стоп-слова исключаются из поиска
    vector<int> FindDocuments(const vector<vector<string>>& documents, const set<string>& stop_words, const string& query) {
        // Напишите код функции
    }

## Вам также понадобятся вспомогательные функции: ##
- ParseQuery — разбирает текст запроса на слова, исключая из них стоп-слова.
- MatchDocument — проверяет, подходит ли документ под критерии поискового запроса.

# Используйте эти функции, чтобы реализовать функцию FindDocuments. #
## **Их сигнатуры:**

    // Разбирает text на слова и возвращает только те из них, которые не входят в stop_words
    set<string> ParseQuery(const string& text, const set<string>& stop_words) {
        // Напишите код функции
    }

    // Возвращает true, если среди слов документа (document_words)
    // встречаются слова поискового запроса query_words
    bool MatchDocument(const vector<string>& document_words, const set<string>& query_words) {
        // Напишите код функции
    } 
## Функция main из заготовки кода считывает стоп-слова, документы и поисковый запрос. Затем она выводит результаты поиска: id документов, соответствующих поисковому запросу.

## **Требования**

- Разные слова могут встречаться в одних и тех же документах. 
- Верните результат поиска без повторов.
- Не меняйте сигнатуру FindDocuments.

### Пример использования функций
    int main() {
        // Считываем стоп-слова
        const string stop_words_joined = ReadLine();
        const set<string> stop_words = ParseStopWords(stop_words_joined);

        // Считываем документы
        vector<vector<string>> documents;
        const int document_count = ReadLineWithNumber();
        for (int document_id = 0; document_id < document_count;     ++document_id) {
          AddDocument(documents, stop_words, ReadLine());
     }

      // Ищем документы по поисковому 
      const string query = ReadLine();
      for (const int document_id : FindDocuments(documents, stop_words,   query)) {
          cout << "{ document_id = "s << document_id << " }"s << endl;
       }
    } 
### Формат ввода и вывода

- В первой строке ввода содержатся стоп-слова, разделённые пробелами. 
- Следующая строка ввода содержит целое число N, задающее количество документов.
- В каждой из последующих N строк — текст документа, в котором слова разделяются одним пробелом. Последняя строка ввода содержит текст поискового запроса, где слова разделяются одним пробелом.

### Программа должна вывести id документов, соответствующих поисковому запросу, как это показано ниже. id выводятся в порядке возрастания.
**Пример ввода:**

    a an on the in is has been are with for from have be was
    4
    a small curly guinea pig with grey hair has been found
    a young 50 year old crocodile wants to make friends
    a strange brown creature was seen in the box of oranges
    a strange animal with big ears is building a house for its friends

    cheburashka with big ears likes oranges 

**Пример вывода:**

    { document_id = 2 }
    { document_id = 3 } 

## Под запрос "cheburashka with big ears likes oranges" подходят два документа:

- Документ "a strange brown creature was seen in the box of oranges" с id=2
- Документ "a strange animal with big ears is building a house for its friends" с id=3
- Слово "with" — стоп-слово. Оно не участвует в поиске. Поэтому документ "a small curly guinea pig with grey hair has been found" не будет найден.

# **Подсказка**

1. Чтобы разобрать запрос пользователя в ParseQuery, извлеките из текста запроса слова функцией SplitIntoWordsNoStop и сохраните их в результирующее множество.

2. В функции MatchDocument верните true, если хотя бы одно из слов документа входит во множество слов поискового запроса. Если ни одно слово не входит, верните false.
3. В функции FindDocuments сначала разберите поисковый запрос, используя ParseQuery. Затем в цикле переберите все документы и соберите id тех из них, которые подходят под критерии поискового запроса. 

- Чтобы проверить документ на соответствие запросу, используйте MatchDocument.
- Чтобы компактно объявить тип переменной, укажите вместо её типа ключевое слово auto. 
- Компилятор автоматически определит тип этой переменной. 

Обычно auto применяют, когда название типа слишком длинное:

    vector<vector<string>> documents;
    ...
    // for (const vector<string>& document : documents) 
    for (const auto& document : documents) {
        // Внутри цикла document имеет тип const vector<string>&
    }

    auto n = 42;   // n имеет тип int
    const auto k = 45.5; // k имеет тип const double 