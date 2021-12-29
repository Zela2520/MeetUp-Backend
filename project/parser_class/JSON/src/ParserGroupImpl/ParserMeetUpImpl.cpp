#include <ParserMeetUpImpl.hpp>

ParserObject ParserMeetUpImpl::StrToObject(const std::string& parser_str) const {
    // {"create_group":{"title":"Texnosrac","members":["56"]}};

    nlohmann::json j = nlohmann::json::parse(parser_str);

    nlohmann::json::iterator it = j.begin();

    nlohmann::json value = j[it.key()];

    group_t group;

    {
        if (value.contains("group_id"))
        {
            group.group_id = value["group_id"].get<std::string>();
        }

        if (value.contains("title"))
        {
            group.title = value["title"].get<std::string>();
        }

        if (value.contains("members")) {
            for (auto &element_in : value["members"])
            {
                group.members.insert(element_in.get<std::string>());
            }
        }
    }

    ParserObject res;

    std::set<group_t> groups;

    groups.insert(group);

    res = groups;

    //  Отладка
    if (GLOBAL_KEY_TEST_PARSER) {
        Print_struct::from_client(parser_str);
        for (std::set<group_t>::iterator it = groups.begin(); it != groups.end(); ++it) {
            Print_struct::_group_t(*it);
        }
    }

    return res;
}

std::string ParserMeetUpImpl::ObjectToStr(const std::string type_response, const ParserObject& other) const {
    // {"add_event":{["user_id":"56","event_name":"breakfast","event_date":"01:06:2000", "description":"2132", "time_begin":"15:45", "time_end":"16:00"]}} TODO: Отредачить

    nlohmann::json j;

    std::string res;

    if (other.error.empty()) {
        j[type_response] = "Error get meetup";

        res = j.dump();

        return res;
    }

    std::set<meetup_t> meetups = other.meetups;

    nlohmann::json json_events;

    if (!meetups.empty())
    {
        for (auto& meetup: meetups)
        {
            nlohmann::json json_event;

            if (!meetup.meetup_name.empty())
                json_event["meetup_name"] = meetup.meetup_name;

            if (!meetup.time_begin.empty())
                json_event["time_begin"] = meetup.time_begin;

            if (!meetup.time_end.empty())
                json_event["time_end"]   = meetup.time_end;

            if (!meetup.description.empty())
                json_event["description"] = meetup.description;

            if (!meetup.date.empty())
                json_event["meetup_date"] = meetup.date;

            json_events.push_back(json_event);
        }
    }

    res = j.dump();

    //  Отладка
    if (GLOBAL_KEY_TEST_PARSER) {
        for (std::set<meetup_t>::iterator it = meetups.begin(); it != meetups.end(); ++it) {
            Print_struct::_meetup_t(*it);
        }
        Print_struct::from_processing(res);
    }

    return res;
}
