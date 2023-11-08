#include <iostream>
#include <list>
#include <algorithm>

using namespace std;
class Disk;

int Volume;
Disk* disk;

enum Status{USE, FREE};

class Partition{
public:
    int size;
    int startIndex;
    string name;
    Status status;

    Partition(int size, int startIndex = 0, string name="", Status status=FREE): size(size), startIndex(startIndex), name(name), status(status){}

};

class Disk{
public:
    int volume;
    int availableVolume;
    list<Partition> partitions;

    Disk(int volume): volume(volume), availableVolume(volume){partitions.push_front(Partition(volume));}

    void write(string fileName, int fileSize){
        if(availableVolume < fileSize){
            cout << "diskfull\n";
        }
        else{

            write2(fileName, fileSize);

            if(fileSize != 0){
                write2(fileName, fileSize, true);
            }
        }

    }

    void remove(string removeName){
        for(auto& partition: partitions){
            if(partition.name == removeName){
                availableVolume += partition.size;
                partition.name = "";
                partition.status = FREE;
            }
        }
        combine();
    }

    void compact(){
        int index=0;
        partitions.erase(remove_if(partitions.begin(), partitions.end(), [](auto p){return p.status == FREE;}), partitions.end());
        for(auto& p: partitions){
            p.startIndex = index;
            index += p.size;
        }
        combine();
        partitions.push_back(Partition(availableVolume, volume - availableVolume));
    }

    void show(string fileName){
        bool print = false;
        for(auto p: partitions){
            if(p.name == fileName){
                cout << p.startIndex << " ";
                print = true;
            }
        }
        if(print) cout << endl;
        else cout << "error\n";
    }

    void write2(string fileName, int& fileSize, bool split = false){
        int startIndex=0;
        for(auto current= partitions.begin(); current != partitions.end(); current++){
            if(current->status == FREE){

                if(current->size >= fileSize){
                    if(current->size ==fileSize){
                        assign(*current, fileName);
                    }
                    else{
                        Partition newFile = Partition(fileSize, startIndex, fileName, USE);
                        resize(*current, current->size - fileSize);
                        partitions.insert(current, newFile);
                    }
                    availableVolume -= fileSize;
                    fileSize = 0;
                    break;
                }
                else{
                    if(split){
                        assign(*current, fileName);
                        availableVolume -= current->size;
                        fileSize -= current->size;
                    }
                }
            }
            startIndex += current->size;
        }
    };

    void resize(Partition& p, int newSize){
        p.startIndex = p.startIndex + p.size - newSize;
        p.size = newSize;
    }

    void assign(Partition& p, string fileName){
        p.name = fileName;
        p.status = USE;
    }
    void combine(){
        auto previous = partitions.begin();
        for(auto current = ++partitions.begin(); current != partitions.end(); current++){
            if(previous->name == current->name){
                current->startIndex = previous->startIndex;
                current->size += previous->size;
                partitions.erase(previous);
                previous = current;
            }
            else{
                previous++;
            }
        }
    }
};

void setDisk(){
    cin >> Volume;
    disk = new Disk(Volume);
}

void execute(string command){
    string fileName;
    int fileSize;

    if(command == "write") {
        cin >> fileName >> fileSize;
        disk->write(fileName, fileSize);
    }
    else if(command == "delete") {
        cin >> fileName;
        disk->remove(fileName);
    }
    else if(command == "show") {
        cin >> fileName;
        disk->show(fileName);
    }
    else if(command == "compact") {
        disk->compact();
    }
}

void input(){
    string command;
    do{
        cin >> command;
        execute(command);
    } while(command != "end");
}

int main() {
    setDisk();
    input();
    delete disk;
}
