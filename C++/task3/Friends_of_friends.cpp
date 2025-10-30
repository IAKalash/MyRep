#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <set>
#include <algorithm>
#include <queue>

using namespace std;

namespace social_net {

    struct Post {
        string time;
        string name;
        string text;
    };

    int read_file(vector<pair<string, vector<string>>> *graph, vector<Post> *posts, string in) {
        ifstream input(in);
        if (!input.is_open()) {
            cerr << "Error opening the file!" << endl;
            return 1;
        }

        string name, line, frname;
        vector<string> friends;

        while (1) {
            friends.clear();
            getline(input, line);

            if (line == "") break;

            istringstream sstr(line);
            sstr >> name;
            while (sstr >> frname) {
                friends.push_back(frname);
            }
            graph->push_back({name, friends});
        }


        string time;
        while (1) {
            input >> time >> name;
            if (input.fail()) break;
            
            Post post;
            post.time = time;
            post.name = name;
            getline(input, post.text);

            posts->emplace_back(post);
        }

        input.close();

        return 0;
    }

    set <string> get_friends (const vector <pair<string, vector<string>>> &graph, const string &name) {
        for (auto g : graph) {
            if (g.first == name) {
                set<string> res(g.second.begin(), g.second.end());
                return res;
            }
        }
        set<string> res;
        return res;
    }

    set <string> get_friends_of_friends (const vector <pair<string, vector<string>>> &graph, const string &name) {
        set<string> friends = get_friends(graph, name);
        set<string> res;
        for (string frnd : friends) {
            res.merge(get_friends(graph, frnd));
        }
        res.erase(name);
        return res;
    }

    vector<Post> get_feed (const vector<pair<string, vector<string>>> &graph, const vector<Post> &all_posts, 
            const set<string> &users) {
        vector<Post> res;

        for (Post post : all_posts) {
            if (users.find(post.name) != users.end()) res.push_back(post);
        }

        sort(res.begin(), res.end(), 
            [](const Post& a, const Post& b) {
                return a.time > b.time; }
            );
        return res;
    }

    void print_feed (const vector<Post> &feed) {
        for (auto post : feed) cout << post.time 
                                    << " " 
                                    << post.name 
                                    << post.text 
                                    << endl;
    }

    int handshakes(const vector<pair<string, vector<string>>> &graph, const string &src, const string &dest) {
        if (src == dest) return 0;
        queue<pair<string, int>> q;
        set<string> visited;
        set<string> neighbours;
        
        q.push({src, 0}); 
        visited.insert(src);

        while (!q.empty())  { 
            auto [curr, dist] = q.front(); 
            q.pop();
            neighbours = get_friends(graph, curr);

            for (string neigh : neighbours) {
                if (neigh == dest) return dist + 1;

                if (visited.find(neigh) == visited.end()) {
                    visited.insert(neigh);
                    q.push({neigh, dist + 1});
                }
            }
        }

        return -1;
    }
}

int main() {

    vector <pair<string, vector<string>>> graph;
    vector<social_net::Post> posts;

    social_net::read_file(&graph, &posts, "text.txt");

    cout << "Friends_feed:" << endl;
    social_net::print_feed(social_net::get_feed(graph, posts, social_net::get_friends(graph, "vasya")));

    cout << endl << "Friends of friends feed:" << endl;
    social_net::print_feed(social_net::get_feed(graph, posts, social_net::get_friends_of_friends(graph, "vasya")));

    cout << endl << social_net::handshakes(graph, "vasya", "boris") << endl;
    
    return 0;
}