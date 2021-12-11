//include header files required in this project
#include "headers.h"
#include <unordered_map>
using namespace std;

class Ranger {
 public:
    int id;
    string name;
    vector<string> seasons;
    vector<string> colors;
    unordered_map<int, string> allies;
    
    Ranger(int id, string name, vector<string> season, vector<string> color, unordered_map<int, string> allies) {
        this->id = id;
        this->name = name;
        this->seasons = season;
        this->colors = color;
        this->allies = allies;
    }
    //default constructor
    Ranger() {
        this->id = 0;
        this->name = "";
    }

};
/**********************************************************/

vector<Ranger> rangers;

void print_all_rangers() {
    for (int i = 0; i < rangers.size(); i++) {
        cout<<"RANGER "<<i;
        cout << "Ranger " << rangers[i].id << ": " << rangers[i].name << endl;
        cout << "Seasons: ";
        for (int j = 0; j < rangers[i].seasons.size(); j++) {
            cout << rangers[i].seasons[j] << " ";
        }
        cout << endl;
        cout << "Colors: ";
        for (int j = 0; j < rangers[i].colors.size(); j++) {
            cout << rangers[i].colors[j] << " ";
        }
        cout << endl;
        cout << "Allies: ";
        for (unordered_map<int, string>::iterator it = rangers[i].allies.begin(); it != rangers[i].allies.end(); ++it) {
            cout << it->first << " "<< it->second << " ";
        }
        cout << endl;
    }
}
int find_id(string name) {
    for (int i = 0; i < rangers.size(); i++) {
        if (rangers[i].name == name) {
            return rangers[i].id;
        }
    }
    return -1;
}

//add nodes (Rangers) to the graph
void add_Ranger(string name, string season, string color) {
    int id = find_id(name);
    if (id == -1) {
        id = rangers.size();
        vector<string> seasons;
        vector<string> colors;
        unordered_map<int, string> allies;
        seasons.push_back(season);
        colors.push_back(color);
        Ranger new_ranger(id, name, seasons, colors, allies);

        rangers.push_back(new_ranger);
    }
    else {
        for (int i = 0; i < rangers.size(); i++) {
            if (rangers[i].id == id) {
                rangers[i].seasons.push_back(season);
                rangers[i].colors.push_back(color);
            }
            else {
                cout<<"RIP"<<endl;
            }
        }
    }
    cout<<"Ranger "<<id<<" added"<<endl;
    cout<<"Ranger size: "<<rangers.size()<<endl;
}

//adding edges (Season in which rangers met) to graph with edge names
void add_edge(int id1, int id2, string season_name) {
    for (int i = 0; i < rangers.size(); i++) {
        if (rangers[i].id == id1) {
            rangers[i].allies[id2] = season_name;
        }
    }
    for (int i = 0; i < rangers.size(); i++) {
        if (rangers[i].id == id2) {
            rangers[i].allies[id1] = season_name;
        }
    }
}

//store graph in file
void store_graph(string filename) {
    ofstream fout(filename);
    for(int i = 0; i < rangers.size(); i++) {
        fout << rangers[i].id << " " << rangers[i].name << " ";
        cout<<"Writing in process";
        for(int j = 0; j < rangers[i].seasons.size(); j++) {
            fout << rangers[i].seasons[j] << ",";
        }
        fout << " ";
        for(int j = 0; j < rangers[i].seasons.size(); j++) {
            fout << rangers[i].colors[j] << ",";
        }
        fout << " ";
        //write allies to file
        for(unordered_map<int, string>::iterator it = rangers[i].allies.begin(); it != rangers[i].allies.end(); it++) {
            fout << it->first << " " << it->second << " ";
        }
        fout << endl;
    }
    fout.close();
}

//function to split string by delimiter
vector<string> split(string str, char delimiter) {
    vector<string> internal;
    stringstream ss(str); // Turn the string into a stream.
    string tok;
    
    while(getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }
    
    return internal;
}

//get graph from file
vector<Ranger> get_graph(string filename) {
    ifstream fin(filename);
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        string id, name, seasons, colors, allies;
        getline(ss, id, ' ');
        getline(ss, name, ' ');
        getline(ss, seasons, ' ');
        getline(ss, colors, ' ');
        getline(ss, allies);
        vector<string> season = split(seasons, ',');
        vector<string> color = split(colors, ',');
        vector<string> ally = split(allies, ',');
        unordered_map<int, string> umap;
        for (int i = 0; i < ally.size(); i++) {
            string s = ally[i];
            string id, season;
            stringstream ss(s);
            getline(ss, id, ':');
            getline(ss, season);
            umap[stoi(id)] = season;
        }
        Ranger new_ranger(stoi(id), name, season, color, umap);
        rangers.push_back(new_ranger);
        cout<<"Reading in process";
    }
    fin.close();
    return rangers;
}

//find shortest path in graph using BFS and return the path with edges
vector<string> find_path(string name1, string name2) {
    int id1 = find_id(name1);
    int id2 = find_id(name2);
    if (id1 == -1 || id2 == -1) {
        return vector<string>(0, "No path found");
    }
    vector<string> path;
    vector<int> visited;
    queue<int> q;
    q.push(id1);
    visited.push_back(id1);
    while (!q.empty()) {
        int id = q.front();
        q.pop();
        if (id == id2) {
            break;
        }
        for (unordered_map<int, string>::iterator it = rangers[id].allies.begin(); it != rangers[id].allies.end(); it++) {
            if (find(visited.begin(), visited.end(), it->first) == visited.end()) {
                q.push(it->first);
                visited.push_back(it->first);
            }
        }
    }
    for (int i = 0; i < visited.size(); i++) {
        if (visited[i] == id2) {
            path.push_back(to_string(visited[i]));
            while (visited[i] != id1) {
                for (unordered_map<int, string>::iterator it = rangers[visited[i]].allies.begin(); it != rangers[visited[i]].allies.end(); it++) {
                    if (it->first == id1) {
                        path.push_back(it->second);
                        break;
                    }
                }
                i--;
            }
            reverse(path.begin(), path.end());
            return path;
        }
    }
    return path;
}


//Find relation between two rangers
void oracle_of_rangers(string name1, string name2) {
    vector<string> path = find_path(name1, name2);
    if (path.size() == 0) {
        cout<< name1 << " and " << name2 <<" are from completely different timelines/universes"<<endl;
        return;
    }
    if (path[0] == "No path found") {
        cout << "Ranger does not exist." << endl;
    }
    else {
        for (int i = 0; i < path.size(); i++) {
            cout << path[i] << " ";
        }
    }
}

//print ranger given id
void print_ranger(int id) {
    for (int i = 0; i < rangers.size(); i++) {
        if (rangers[i].id == id) {
            cout<<"Ranger ID: "<<rangers[i].id<<endl;
            cout<<"Ranger Name: "<<rangers[i].name<<endl;
            cout<<"Ranger Seasons: ";
            for (int j = 0; j < rangers[i].seasons.size(); j++) {
                cout << rangers[i].seasons[j] << " ";
            }
            cout << endl;
            cout<<"Ranger Colors: ";
            for (int j = 0; j < rangers[i].colors.size(); j++) {
                cout << rangers[i].colors[j] << " ";
            }
            cout <<endl;
            cout<<"Ranger Allies: ";
            for (unordered_map<int, string>::iterator it = rangers[i].allies.begin(); it != rangers[i].allies.end(); it++) {
                cout << it->first << " " << it->second << " ";
            }
            cout << endl;
            return;
        }
    }
    cout<<"Ranger does not exist."<<endl;
}

void print_season() {
    cout<<"Power Rangers Season List"<<endl;
    cout<<"1. Season 1: Mighty Morphin Power Rangers (MMPR-1)"<<endl;
    cout<<"2. Season 2: Mighty Morphin Power Rangers (MMPR-2)"<<endl;
    cout<<"3. Season 3: Mighty Morphin Alien Rangers (MMAR)"<<endl;
    cout<<"4. Season 4: Power Rangers Zeo (PRZ)"<<endl;
    cout<<"5. Season 5: Power Rangers Turbo (PRT)"<<endl;
    cout<<"6. Season 6: Power Rangers in Space (PRIS)"<<endl;
    cout<<"7. Season 7: Power Rangers Lost Galaxy (PRLS)"<<endl;
    cout<<"8. Season 8: Power Rangers Lightspeed Rescue (PRLS)"<<endl;
    cout<<"9. Season 9: Power Rangers Time Force (PRTS)"<<endl;
    cout<<"10. Season 10: Power Rangers Wild Force (PRWF)"<<endl;
    // cout<<"11. Season 11: Power Rangers Ninja Storm"<<endl;
    // cout<<"12. Season 12: Power Rangers Dino Thunder"<<endl;
    // cout<<"13. Season 13: Power Rangers S.P.D."<<endl;
    // cout<<"14. Season 14: Power Rangers Mystic Force"<<endl;
    // cout<<"15. Season 15: Power Rangers Operation Overdrive"<<endl;
    // cout<<"16. Season 16: Power Rangers Jungle Fury"<<endl;
    // cout<<"17. Season 17: Power Rangers RPM"<<endl;
    // cout<<"18. Season 18: Power Rangers Samurai"<<endl;
    // cout<<"19. Season 19: Power Rangers Super Samurai"<<endl;
    // cout<<"20. Season 20: Power Rangers Megaforce"<<endl;
    // cout<<"21. Season 21: Power Rangers Super Megaforce"<<endl;
    // cout<<"22. Season 22: Power Rangers Dino Charge"<<endl;
    // cout<<"23. Season 23: Power Rangers Dino Super Charge"<<endl;
    // cout<<"24. Season 24: Power Rangers Ninja Steel"<<endl;
    // cout<<"25. Season 25: Power Rangers Super Ninja Steel"<<endl;
    // cout<<"26. Season 26: Power Rangers Beast Morphers"<<endl;
    // cout<<"27. Season 27: Power Rangers Beast Morphers"<<endl;
    // cout<<"28. Season 28: Power Rangers Dino Fury"<<endl;
    // cout<<"29. Season 29: Power Rangers Dino Fury"<<endl;

}

void opt1() {
    string name;
    cout<<"Enter Ranger Name: ";
    cin>>name;
    cout<<"Enter season: ";
    string season;
    cin>>season;
    string color;
    cout<<"Enter color: ";
    cin>>color;
    add_Ranger(name, season, color);
}

void opt2() {
    string name1, name2;
    cout<<"Enter Ranger 1 Name: ";
    cin>>name1;
    cout<<"Enter Ranger 2 Name: ";
    cin>>name2;
    int id1 = find_id(name1);
    int id2 = find_id(name2);
    string season;
    cout<<"Enter season: ";
    cin>>season;
    add_edge(id1, id2, season);
}

void opt3() {
    string name1, name2;
    cout<<"Enter Ranger 1 Name: ";
    cin>>name1;
    cout<<"Enter Ranger 2 Name: ";
    cin>>name2;
    oracle_of_rangers(name1, name2);
}

void opt4() {
    int id;
    cout<<"Enter Ranger ID: ";
    cin>>id;
    print_ranger(id);
}

void opt5() {
    store_graph("rangers.txt");
}

void opt6() {
    get_graph("rangers.txt");
}



//menu for user
void menu() {
    int choice;
    string name,color,season;
    int id,id2;
    vector<string> seasons;
    vector<string> colors;
    cout<<"\n\n\t\t\tWelcome to Oracle of Rangers"<<endl;
    cout<<"\t\t\t\tMain Menu"<<endl;
    cout<<"1. Add a new Ranger"<<endl;
    cout<<"2. Add a new Season connecting Rangers"<<endl;
    cout<<"3. Find the shortest connection between two Rangers"<<endl;
    cout<<"4. Print a Ranger's information"<<endl;
    cout<<"5. Store ranger information in file"<<endl;
    cout<<"6. Get ranger information from a file"<<endl;
    cout<<"7. Print all the seasons"<<endl;
    /*cout<<"8. Print all rangers in a particular season"<<endl;*/
    cout<<"8. Exit"<<endl;
    cin>>choice;
    switch (choice) {
        case 1: opt1();
            break;
        case 2:
            opt2();
            break;
        case 3:
            opt3();
            break;
        case 4:
            opt4();
            break;
        case 5:
            opt5();
            break;
        case 6:
            opt6();
            break;
        case 7:
            print_season();
            break;
        case 8:
            exit(0);
            break;
        default:
            cout<<"Invalid choice"<<endl;
            break;
    }

}

/*void ranger_list(){
    cout<<"Enter the number of the season you want to see the list of the Power Rangers"<<endl;
    int season;
    cin>>season;
    switch (season)
    {
    case 1: cout<<"Mighty Morphin Power Rangers"<<endl;
            cout<<"1. Red: Jason Lee Scott"<<endl;
            cout<<"2. Yellow: Trini Kwan"<<endl;
            cout<<"3. Black: Zack Taylor"<<endl;
            cout<<"4. Pink: Kimberly Hart"<<endl;
            cout<<"5. Blue: Billy Cranston"<<endl;
            cout<<"6. Green: Tommy Oliver"<<endl;
            break;
    case 2: cout<<"Mighty Morphin Power Rangers"<<endl;
            cout<<"1. Red: Rocky DeSantos"<<endl;
            cout<<"2. Yellow: Aisha Campbell "<<endl;
            cout<<"3. Black: Adam Park"<<endl;
            cout<<"4. Pink: Katherine \"Kat\" Hillard"<<endl;
            cout<<"5. Blue: Billy Cranston"<<endl;
            cout<<"6. White: Tommy Oliver"<<endl;
            break;
    case 3: cout<<"Mighty Morphin Alien Rangers"<<endl;
            cout<<"1. Red: Aurico "<<endl;
            cout<<"2. Yellow: Tideus "<<endl;
            cout<<"3. Black: Corcus "<<endl;
            cout<<"4. White: Delphine "<<endl;
            cout<<"5. Blue: Cestro "<<endl;
            break;
    case 4: cout<<"Power Rangers Zeo"<<endl;
            cout<<"1. Red: Tommy Oliver "<<endl;
            cout<<"2. Yellow: Tanya Sloan"<<endl;
            cout<<"3. Gold: Jason Lee Scott "<<endl;
            cout<<"4. Pink: Katherine \"Kat\" Hillard"<<endl;
            cout<<"5. Blue: Rocky DeSantos"<<endl;
            cout<<"6. Green: Adam Park"<<endl;
            break;
    
    default:
        break;
    }
}
*/

int main()
{
    do
    {
        menu();
    } while (1);
    return 0;
}