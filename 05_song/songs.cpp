#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
class Song;

int n, k;
vector<Song> songs;

class Song{
public:
    string title;
    char genre;
    int broad;
    double size;
    int download;

    Song(string title, char genre, int broad, double size, int download):
            title(title), genre(genre), broad(broad), size(size), download(download){}
};

ostream& operator <<(ostream& os, Song s){
    os << s.title << "\t" << s.genre << "\t" << s.broad << "\t" << s.size << "\t" << s.download;
    return os;
}

void input(){
    int broad, download;
    string title;
    char genre;
    double size;
    cin >> n >> k;

    for(int i=0; i<n; i++) {
        cin >> title >> genre >> broad >> size >> download;
        songs.push_back(Song(title, genre, broad, size, download));
    }
}

bool songSort(Song a, Song b){

    if(a.broad > b.broad) return true;
    else {
        if(a.broad == b.broad) {
            if(a.download > b.download){
                return true;
            }
            else{
                if(a.download == b.download){
                    if(a.size < b.size) return true;
                }
            }
        }
        return false;
    }
}

void sortSongs(){

    sort(begin(songs), end(songs), songSort);

    vector<Song>::iterator current = songs.begin(), next = current+1, end = songs.end(), diff;
    while(next != end){
        if(current->genre == next->genre){
            auto find = find_if(next, end, [next](auto song){return song.genre != next->genre;});
            if(find != end) {
                Song temp = *find;
                songs.erase(find);
                songs.insert(next, temp);
            }
        }
        current++;
        next++;
    }
}

int main() {

    input();
    sortSongs();

    cout << songs[k-1].title << endl;

    return 0;
}
