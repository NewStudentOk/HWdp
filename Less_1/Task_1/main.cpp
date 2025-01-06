#include <iostream>
#include "sql_select_query_builder.h"

int main() {
    SqlSelectQueryBuilder query_builder;
    query_builder.AddColumn("name").AddColumn("phone");
    query_builder.AddFrom("students");
    query_builder.AddWhere("id", "42").AddWhere("name", "John");

    std::string query = query_builder.BuildQuery();
    std::string example = "SELECT name, phone FROM students WHERE id=42 AND name=John;";

    if (query == example)
    {
        std::cout << "Query is:\n" << query << std::endl << "Everything is fine!" << std::endl;
    }
    else
    {
        std::cout << "Something wrong! True query is:\n" << example << std::endl;
    }
    return 0;
}
