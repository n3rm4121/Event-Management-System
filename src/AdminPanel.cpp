#include "AdminPanel.h"
#include "Database.h"
#include <iostream>
#include <sqlite3.h>
#include <string>

using namespace std;

void createEvent() {
    sqlite3* db = openDatabase();
    if (!db) return;

    string eventName, eventDuration, eventLocation, eventDate, eventDescription, eventCategory;
    int createdBy;

    cout << "Enter Event Name: ";
    cin.ignore();
    getline(cin, eventName);
    cout << "Enter Event Duration: ";
    getline(cin, eventDuration);
    cout << "Enter Event Location: ";
    getline(cin, eventLocation);
    cout << "Enter Event Date (YYYY-MM-DD): ";
    getline(cin, eventDate);
    cout << "Enter Event Description: ";
    getline(cin, eventDescription);
    cout << "Enter Event Category: ";
    getline(cin, eventCategory);
    cout << "Enter Creator Admin ID: ";
    cin >> createdBy;

    string query = "INSERT INTO events (eventName, eventDuration, eventLocation, eventDate, eventDescription, eventCategory, createdBy) VALUES ('" +
                   eventName + "', '" + eventDuration + "', '" + eventLocation + "', '" + eventDate + "', '" + eventDescription + "', '" + eventCategory + "', " + to_string(createdBy) + ")";

    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
    } else {
        cout << "Event created successfully.\n";
    }

    sqlite3_close(db);
}

void editEvent() {
    sqlite3* db = openDatabase();
    if (!db) return;

    int eventID, createdBy;
    string eventName, eventDuration, eventLocation, eventDate, eventDescription, eventCategory;

    cout << "Enter Event ID to edit: ";
    cin >> eventID;
    cout << "Enter new Event Name: ";
    cin.ignore();
    getline(cin, eventName);
    cout << "Enter new Event Duration: ";
    getline(cin, eventDuration);
    cout << "Enter new Event Location: ";
    getline(cin, eventLocation);
    cout << "Enter new Event Date (YYYY-MM-DD): ";
    getline(cin, eventDate);
    cout << "Enter new Event Description: ";
    getline(cin, eventDescription);
    cout << "Enter new Event Category: ";
    getline(cin, eventCategory);
    cout << "Enter new Creator Admin ID: ";
    cin >> createdBy;

    string query = "UPDATE events SET eventName = '" + eventName + "', eventDuration = '" + eventDuration + "', eventLocation = '" + eventLocation + "', eventDate = '" + eventDate + "', eventDescription = '" + eventDescription + "', eventCategory = '" + eventCategory + "', createdBy = " + to_string(createdBy) + " WHERE eventID = " + to_string(eventID);

    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
    } else {
        cout << "Event updated successfully.\n";
    }

    sqlite3_close(db);
}

void deleteEvent() {
    int eventID;
    cout << "Enter Event ID to delete: ";
    cin >> eventID;

    sqlite3* db = openDatabase();

    string query = "DELETE FROM events WHERE eventID = " + to_string(eventID);
    sqlite3_exec(db, query.c_str(), nullptr, nullptr, nullptr);

    cout << "Event deleted successfully.\n";
    sqlite3_close(db);
}


void viewEventRegistrations() {
    int eventID;
    cout << "Enter Event ID to view registrations: ";
    cin >> eventID;

    sqlite3* db = openDatabase();

    string query = "SELECT userID FROM event_registrations WHERE eventID = " + to_string(eventID);
    
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

    cout << "Users registered for Event ID " << eventID << ":\n";
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        cout << "User ID: " << sqlite3_column_int(stmt, 0) << "\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
