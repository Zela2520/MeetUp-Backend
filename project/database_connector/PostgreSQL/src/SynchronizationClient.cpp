#include "../include/PGConnection.hpp"

#include "../../include/impl/DataBaseConnectorImpl.hpp"

#include <iostream>

namespace DatabaseConnector {
    namespace Synchro {
        std::set<std::string> Contacts(const std::string& user_id) {
            char command[] = "SELECT fk_user_id, nickname "
                             "FROM contacts "
                             "LEFT JOIN user_m "
                             "ON fk_friend_id = user_id "
                             "WHERE fk_user_id = $1";

            const char *arguments[1];

            arguments[0] = user_id.c_str();

            PGresult *res = PQexecParams(PGConnection::GetConnection(), command, 1, NULL, arguments, NULL, NULL, 0);

            if (PQresultStatus(res) != PGRES_TUPLES_OK) {
                printf("command faild: %s\n", PQerrorMessage(PGConnection::GetConnection()));

                PQclear(res);
            }

            std::set<std::string> friends;

            if (PQgetisnull(res, 0, 1))
                return friends;

            int n_rows = PQntuples(res);

            for (int i = 0; i < n_rows; i++) {
                char *user_friend = PQgetvalue(res, i, 1);

                friends.insert(user_friend);
            }

            PQclear(res);

            std::cout << "Полученный обработчиком id: " << arguments[0] << std::endl;
            std::cout << "Количество строк (друзей), которые нашел SQL: " << n_rows << std::endl;
            std::cout << "Количество строк (друзей), добавленных в множество: " << friends.size() << std::endl;

            return friends;
        };

        std::set<event_t> Events(const std::string& user_id, const std::string& date) {
            char command[] = "SELECT description, time_begin, time_end "
                             "FROM event_m "
                             "WHERE (event_date = $1) AND (fk_user_id = $2)";

            const char* arguments[2];

            arguments[0] = date.c_str();
            arguments[1] = user_id.c_str();

            PGresult *res = PQexecParams(PGConnection::GetConnection(), command, 2, NULL, arguments, NULL, NULL, 0);

            if (PQresultStatus(res) != PGRES_TUPLES_OK) {
                printf("command faild: %s\n", PQerrorMessage(PGConnection::GetConnection()));

                PQclear(res);
            }

            std::set<event_t> events;

            if (PQgetisnull(res, 0, 1))
                return events;

            int n_rows = PQntuples(res);
            //  int n_rows = PQnfields(res);

            event_t event;

            for (int i = 0; i < n_rows; i++) {
                event.event_name = PQgetvalue(res, i, 0);
                event.time_begin = PQgetvalue(res, i, 1);
                event.time_end = PQgetvalue(res, i, 2);

                Print_struct::_event_t(event);
                
                events.insert(event);
            }

            PQclear(res);

            return events;
        };

        std::set<std::string> Groups(const std::string &user_id) {
            char command[] = "SELECT fk_user_id, title "
                             "FROM group_members "
                             "LEFT JOIN group_m "
                             "ON fk_group_id = group_id "
                             "WHERE fk_user_id = $1";

            const char *arguments[1];

            arguments[0] = user_id.c_str();

            PGresult *res = PQexecParams(PGConnection::GetConnection(), command, 1, NULL, arguments, NULL, NULL, 0);

            std::set<std::string> groups;

            if (PQgetisnull(res, 0, 1))
                return groups;                // в верхней функции првоерить пустое ли множество, если да то Not found

            int n_rows = PQntuples(res);

            for (int i = 0; i < n_rows; i++) {
                char *Group_name = PQgetvalue(res, i, 1);

                groups.insert(Group_name);
            }

            PQclear(res);

            std::cout << "Полученный обработчиком id: " << arguments[0] << std::endl;
            std::cout << "Количество строк (групп), которые нашел SQL: " << n_rows << std::endl;
            std::cout << "Количество строк (групп), добавленных в множество: " << groups.size() << std::endl;

            return groups;
        }
    }
}