#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

// Метод для ввода строки
string ReadLine() {
    string s;
    getline(cin, s);
    return s;
}

// Метод для ввода чисел и строк
int ReadLineWithNumber() {
    int result = 0;
    cin >> result;
    ReadLine();
    return result;
}

// Метод для разбиения строки на слова и записи их в вектор (массив)
vector<string> SplitIntoWords(const string& text) {
    vector<string> words;
    string word;
    for (const char c : text) {
        if (c == ' ') {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        } else {
            word += c;
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }

    return words;
}

// Метод для записи стоп слов в set (массив)
set<string> ParseStopWords(const string& text) {
    set<string> stop_words;
    for (const string& word : SplitIntoWords(text)) {
        stop_words.insert(word);
    }
    return stop_words;
}

// Метод для проверки отсутствия стоп слов в тексте
vector<string> SplitIntoWordsNoStop(const string& text, const set<string>& stop_words) {
    vector<string> words;
    // Проходим по всем словам из текста и проверяем, что их нет в списке стоп-слов
    for (const string& word : SplitIntoWords(text)) {
        if (stop_words.count(word) == 0) {
            words.push_back(word);
        }
    }
    // вернём результат без стоп-слов
    return words;
}

// Метод для добавления в базу данных стов после проверки отсутсвия стоп слов
void AddDocument(vector<vector<string>>& documents, const set<string>& stop_words, const string& document) {
    const vector<string> words = SplitIntoWordsNoStop(document, stop_words);
    documents.push_back(words);
}

// Разбирает text на слова и возвращает только те из них, которые не входят в stop_words
set<string> ParseQuery(const string& text, const set<string>& stop_words) {
    set<string> query_words;
    vector<string> query_w = SplitIntoWordsNoStop(text, stop_words);
    int len = query_w.size();
    for (int i= 0; i < len; i++) {
        query_words.insert(query_w[i]);
    }
    return query_words;
}

// Возвращает true, если среди слов документа (document_words) встречаются слова поискового запроса query_words
bool MatchDocument(const vector<string>& document_words, const set<string>& query_words) {
    int len2 =  document_words.size();
    for (int j = 0; j < len2; j++) {
        if (query_words.count(document_words[j]) > 0) {
            return true;
        }
    }
    return false;
}

// Возвращает массив id документов, подходящих под запрос query
// Стоп-слова исключаются из поиска
vector<int> FindDocuments(const vector<vector<string>>& documents, const set<string>& stop_words, const string& query) {
    vector<int> matched_documents;
    // Взяли текст запроса query и отправили его разбиться и сформироваться в массив слов vector<string>
    // А потом проверили и вернули в set<string> query только те, которые не входят в stop_words
    const set<string> query_words = ParseQuery(query, stop_words);
    // Унас есть слова, которые не входят в stop_words и мы можем осуществить поиск совпадений
    int len3 = documents.size();
    for (int k = 0; k < len3; k++) {
        if (MatchDocument(documents[k], query_words)) {
            matched_documents.push_back(k);
        }
    } 
    // Напишите код функции
    // Воспользуйте вспомогательными функциями ParseQuery, MatchDocument
    // В качестве id документа используйте его индекс в массиве documents

    return matched_documents;
}

int main() {
    // Добавление строки стоп слов - stop_words_joined
    const string stop_words_joined = ReadLine();

    // Сформирвоан массив из стоп слов - stop_words
    const set<string> stop_words = ParseStopWords(stop_words_joined);

    // Создание быза данных
    vector<vector<string>> documents;

    // Определяется количество введенный элементов document_count
    const int document_count = ReadLineWithNumber();

    // Сформирвоан цикл с фиксацией порядковых номеров введенных строк в базу данных documents
    // При направлении втрок в базу данных происходит проверка слов на наличие стоплов stop_words
    for (int document_id = 0; document_id < document_count; ++document_id) {
        AddDocument(documents, stop_words, ReadLine());
    }

    // Ввод поискового запроса
    const string query = ReadLine();

    // сформирован цикл для поиска document_id при сопоставлении посикового запроса с базой данных
    // FindDocuments(documents, stop_words, query) - здесь лежит 4 элемента
    // Соответственно поиск и вывод будет осуществлен при нахождению совпадения
    for (const int document_id : FindDocuments(documents, stop_words, query)) {
        cout << "{ document_id = "s << document_id << " }"s << endl;
    }
}