#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;
class Date {
public:
  Date() {
    year = 0;
    month = 0;
    day = 0;
  }

  Date(const string &str) {
    int numy = 0, numm = 0, numd = 0;
    string daystr, monthstr, yearstr;
    int flag1 = 1;
    bool flag2 = false, flag3 = false;
    int signy = 1, signm = 1, signd = 1;
    for (auto it : str) {
      if (it == '\n') {
        return;
      }
      if (it == '+') {
        if (flag3) {
          cout << "Wrong date format: " << str << endl;
          throw exception();
        }
        flag3 = true;
        continue;
      }
      if (it != '-' && !isdigit(it)) {
        cout << "Wrong date format: " << str << endl;
        throw exception();
      }
      string temp;
      if (it != '-') {
        switch (flag1) {
        case 1:

          numy *= 10;
          temp = it;
          yearstr.push_back(it);
          numy += stoi(temp);
          flag2 = true;

          break;
        case 2:
          numm *= 10;
          temp = it;
          monthstr.push_back(it);
          numm += stoi(temp);
          flag2 = true;
          break;
        case 3:

          numd *= 10;
          temp = it;
          daystr.push_back(it);
          numd += stoi(temp);
          flag2 = true;

          break;
        default:
          break;
        }
      } else {
        if (flag2) {
          switch (flag1) {
          case 1:
            flag1 = 2;
            flag2 = false;
            flag3 = false;
            break;
          case 2:
            flag1 = 3;
            flag2 = false;
            flag3 = false;
            break;
          case 3:
            cout << "Wrong date format: " << str << endl;
            throw exception();
            break;
          default:
            break;
          }
        } else {
          if (!flag2) {
            if (flag1 == 1) {
              signy = -1;
              if (flag3) {
                cout << "Wrong date format: " << str << endl;
                throw exception();
              }
              flag2 = true;
              flag3 = true;
            }
            if (flag1 == 2) {
              signm = -1;
              if (flag3) {
                cout << "Wrong date format: " << str << endl;
                throw exception();
              }
              flag2 = true;
              flag3 = true;
            }
            if (flag1 == 3) {
              signd = -1;
              if (flag3) {
                cout << "Wrong date format: " << str << endl;
                throw exception();
              }
              flag2 = true;
              flag3 = true;
            }
          }
        }
      }
    }
    numy *= signy;
    numm *= signm;
    numd *= signd;
    if ((numy > 9999) || (daystr.empty() || monthstr.empty())) {
      cout << "Wrong date format: " << str << endl;
      throw exception();
    }
    if (numm < 1 || numm > 12) {
      cout << "Month value is invalid: " << numm << endl;
      throw exception();
    }
    if (numd < 1 || numd > 31) {
      cout << "Day value is invalid: " << numd << endl;
      throw exception();
    }
    year = numy;
    month = numm;
    day = numd;
  }
  int GetYear() const { return year; }
  int GetMonth() const { return month; }
  int GetDay() const { return day; }
  map<set<int>, vector<string>> GetDates() { return data; }
  void Add(const string &event) {
    data[{year, month, day}].push_back(event);
    set<string> temp(data[{year, month, day}].begin(),
                     data[{year, month, day}].end());
    data[{year, month, day}].clear();
    for (auto it : temp) {
      data[{year, month, day}].push_back(it);
    }
  }
  void Del(const string &event) {
    if (data.find({year, month, day}) != data.end()) {
      for (size_t i = 0; i < data[{year, month, day}].size(); i++) {
        if (data[{year, month, day}][i] == event) {
          data[{year, month, day}].erase(data[{year, month, day}].begin() + i);
          if (data[{year, month, day}][0] == "" &&
              data[{year, month, day}].empty()) {
            data.erase({year, month, day});
          }
          cout << "Deleted successfully" << endl;
          return;
        }
      }
      cout << "Event not found" << endl;
    }
  }
  void DelDate() {
    if (data.find({year, month, day}) != data.end()) {
      int N = data[{year, month, day}].size();
      data[{year, month, day}].clear();
      data.erase({year, month, day});
      cout << "Deleted " << N << " events" << endl;
      return;
    }
  }
  void FindE() {
    for (auto it : data[{year, month, day}]) {
      cout << it << endl;
    }
  }
  void FindD() {
    size_t counter = 0;
    for (auto it : data[{year, month, day}]) {
      cout << setfill('0') << setw(4) << year;
      cout << "-" << setfill('0') << setw(2) << month;
      cout << "-" << setfill('0') << setw(2) << day << " ";
      cout << it;
      counter++;
      if (counter != data[{year, month, day}].size()) {
        cout << endl;
      }
    }
  }

  bool empty() {
    if (data.size() == 0) {
      return true;
    }
    return false;
  }

private:
  map<set<int>, vector<string>> data;
  int year = 0;
  int month = 0;
  int day = 0;
};

bool operator<(const Date &lhs, const Date &rhs) {
  if (lhs.GetYear() < rhs.GetYear()) {
    if (lhs.GetDay() > rhs.GetDay()) {
      return true;
    }
    if (lhs.GetMonth() > rhs.GetMonth()) {
      return true;
    }
    return true;
  }
  if (lhs.GetMonth() < rhs.GetMonth()) {
    if (lhs.GetDay() > rhs.GetDay()) {
      return true;
    }
    if (lhs.GetYear() > rhs.GetYear()) {
      return false;
    }
    return true;
  }
  if (lhs.GetDay() < rhs.GetDay()) {
    if (lhs.GetMonth() > rhs.GetMonth()) {
      return false;
    }
    if (lhs.GetYear() > rhs.GetYear()) {
      return false;
    }
    return true;
  }
  if (lhs.GetYear() > rhs.GetYear()) {
    if (lhs.GetDay() < rhs.GetDay()) {
      return false;
    }
    if (lhs.GetMonth() < rhs.GetMonth()) {
      return false;
    }
    return false;
  }
  return false;
}
bool operator==(const Date &lhs, const Date &rhs) {
  if (lhs.GetYear() == rhs.GetYear()) {
    if (lhs.GetMonth() == rhs.GetMonth()) {
      if (lhs.GetDay() == rhs.GetDay()) {
        return true;
      }
    }
  }
  return false;
}
class Database {
public:
  void AddEvent(Date &date, const string &event) {
    if (date.GetMonth() > 0 && date.GetDay() > 0 && date.GetMonth() < 13 &&
        date.GetDay() < 32) {
      for (size_t i = 0; i < dates.size(); i++) {
        if (dates[i] == date) {
          date.Add(event);
          dates[i].Add(event);
          return;
        }
      }
      date.Add(event);
      dates.push_back(date);
    }
  }
  void DeleteEvent(Date &date, const string &event) {
    for (size_t i = 0; i < dates.size(); i++) {
      if (dates[i] == date) {
        dates[i].Del(event);
        if (dates[i]
                .GetDates()[{date.GetYear(), date.GetMonth(), date.GetDay()}]
                .empty()) {
          dates.erase(dates.begin() + i);
        }
        return;
      }
    }
    cout << "Event not found" << endl;
  }
  void DeleteDate(Date &date) {
    bool flag = true;
    for (size_t i = 0; i < dates.size(); i++) {
      if (dates[i] == date) {
        dates[i].DelDate();
        dates.erase(dates.begin() + i);
        flag = false;
        break;
      }
    }
    if (flag) {
      cout << "Deleted 0 events" << endl;
    }
  }
  void Finde(Date &date) const {
    for (auto it : dates) {
      if (it == date) {
        it.FindE();
      }
    }
  }

  void Find(Date &date) const {
    for (auto it : dates) {
      if (it == date) {
        it.FindD();
      }
    }
  }

  void Print() const {
    set<Date> temp(dates.begin(), dates.end());
    for (auto it : temp) {
      if (!temp.empty()) {
        if (it.empty()) {
          continue;
        }
        Find(it);
        cout << endl;
      }
    }
  }

private:
  vector<Date> dates;
};

int main() {
  Database db;

  vector<string> commands = {"Add", "Del", "Find", "Print"};

  string command;
  while (getline(cin, command)) {
    int comman = 0, flag = 0;
    string data, event, com;
    if (!command.empty()) {
      for (auto it : command) {
        if (it != ' ') {
          switch (flag) {
          case 0:
            com.push_back(it);
            break;
          case 1:
            data.push_back(it);
            break;
          case 2:
            event.push_back(it);
            break;
          default:
            break;
          }
        } else {
          switch (flag) {
          case 0:
            for (size_t i = 0; i < commands.size(); i++) {
              if (com == commands[i]) {
                comman = i + 1;
                break;
              }
            }
            if (comman == 0) {
              cout << "Unknown command: " << com << endl;
              return 0;
            }
            flag = 1;
            break;
          case 1:
            if (data.empty()) {
              return 0;
            }
            try {
              Date date(data);
            } catch (exception &e) {
              return 0;
            }
            flag = 2;
            break;
          case 2:
            return 0;
            break;
          default:
            break;
          }
        }
      }
      if (data.empty() && com != "Print") {
        cout << "Unknown command: " << com << endl;
        return 0;
      }
      if (data.size() >= 5 && data.empty()) {
        for (size_t i = 0; i < commands.size(); i++) {
          if (com == commands[i]) {
            comman = i + 1;
            break;
          }
        }
        if (comman == 0) {
          cout << "Unknown command: " << com << endl;
          return 0;
        }
        switch (comman) {
        case 1: {
          try {
            Date date1(data);
            if (!event.empty()) {
              db.AddEvent(date1, event);
            }
          } catch (exception &e) {
            return 0;
          }
          break;
        }
        case 2: {
          try {
            Date date1(data);
            if (event.empty()) {
              db.DeleteDate(date1);
            } else {
              db.DeleteEvent(date1, event);
            }
          } catch (exception &e) {
            return 0;
          }

          break;
        }
        case 3: {
          try {
            Date date1(data);
            db.Finde(date1);
          } catch (exception &e) {
            return 0;
          }
          break;
        }
        case 4:
          db.Print();
          break;
        default:
          break;
        }
      }
    }
  }
  return 0;
}
