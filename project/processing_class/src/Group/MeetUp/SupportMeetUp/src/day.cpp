#include "day.hpp"

Day::Day() {
    this->storage = new uint8_t[NUMBER_CHUNKS] { 0 };
    this->size = NUMBER_CHUNKS;
}

Day::Day(const Day& other) {
    this->storage = new uint8_t[other.size];

    for (size_t i = 0; i < other.size; i++) {
        this->storage[i] = other.storage[i];
    }
}

Day::~Day() {
    delete [] storage;
}

uint8_t* Day::GetStorage() const {
    return storage;
}

size_t Day::GetSize() const{
    return size;
}

bool Day::IntervalIs(const uint8_t &number) const{
    return storage[number / BITS] >> (number % BITS) & 1;
}

void Day::Print() const {
    for (size_t i = 0; i < 96; i++) {
        if (IntervalIs(i)) {
            std::cout << "interval number " << std::setw(2) << i << " there is an event" << std::endl;
        } else {
            std::cout << "interval number " << std::setw(2) << i << " no event" << std::endl;
        }
    }
}

void Day::ShowDay() const{
    for (size_t i = 0; i < NUMBER_CHUNKS; i++) {
        std::cout << '[' << i << ']' << storage[i] << std::endl;
    }
}

void Day::UnionDays(Day& added_day) {
    for (size_t i = 0; i < NUMBER_CHUNKS; i++) {
        storage[i] |= added_day.GetStorage()[i];
    }
}

void Day::InversionDay() {
    for (size_t i = 0; i < NUMBER_CHUNKS; i++) {
        storage[i] = ~ storage[i];
    }
}

void Day::InsertEvent(Event& event) {
    /* TODO : реализовать конструктор копирования для event
     * тогда можно написать:
     * while (event.GetBegin().GetNumberInterval() <= event.GetEnd().GetNumberInterval())
     *
     * подумать над проблемой перевода uint8_t в size_t
    */
    uint8_t begin = event.GetBegin().GetNumberInterval();

    // std::cout << "begin = " << int(begin) << std::endl;

    uint8_t end = event.GetEnd().GetNumberInterval() - 1;

    // std::cout << "end = " << int(end) << std::endl;

    while (begin <= end) {
        storage[begin / BITS] |= ((uint8_t)1 << (begin % BITS));
        begin ++;
    }
}

//void Day::EraseEvent(Duration& begin_time, Duration& end_time) {
//    uint8_t begin = begin_time.GetNumberInterval();
//
//    uint8_t end = end_time.GetNumberInterval();
//    while (begin <= end) {
//        storage[begin / BITS] &= ~((uint8_t)1 << (begin % BITS));
//
//        begin++;
//    }
//}

void Day::Free() {
    for (int i = 0; i < NUMBER_CHUNKS; i++) {
        storage[i] = 0;
    }
}


    /*
    vector<set<event_t>> GetData(group_t) {

        необходимо получить массив занятых временных интервалов
        всех членов группы
    }

    set<meetup> GetMeetUps(vector<set<event_t>>) {
        Day free_day;

        for (auto member: mebmers) {
            Day user_day;

            for (auto event: events) {
                user_day.InsertEvent(begin, end);
            };

            free_day.UnionDays(user_day);
        };

        free_day.InvertDay();

        set<meetup> res = free_day.SeachMeetUps();
    };


    process(const ParserObject& request_body) {
        ParserObject res;

        group_t group

        for (auto gr: request_body.groups) {
            group = gr;
        }

        res = GetMeetUps(GetData(group));

        return res;
    }

    */


    // (TODO) : реализовать метод, который бегаю по дню, и метод создает set<meetup>

