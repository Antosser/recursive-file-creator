#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>
#include <thread>

int filesize = 0;
int filecount = 10;
char characters[16] = { 48,49,50,51,52,53,54,55,56,57,97,98,99,100,101,102 };
long long done = 0;
long long max = 1;

void printPercent();
void recursivCreate(int depth, int goal, std::string prefix);

int main(int argc, char** argv) {
	int depth = 6;
	bool defdepth = false;
	bool deffilesize = false;
	std::string name;
	bool defname = false;

	for (int i = 1; i < argc; i++) {
		std::string cparameter = argv[i];
		if (!cparameter._Starts_with("-")) {
			if (!defname) {
				defname = true;
				name = cparameter;
			}
			else if (!defdepth) {
				defdepth = true;
				depth = stoi(cparameter);
			}
			else if (!deffilesize) {
				deffilesize = true;
				filesize = stoi(cparameter);
			}
			else {
				std::cout << "Unexpected argument: " << cparameter << std::endl;
				exit(1);
			}
			continue;
		}
		if (cparameter == "-c") {
			i++;
			if (i == argc) {
				std::cout << "Expected an argument\n";
				exit(1);
			}
			filecount = atoi(argv[i]);
			continue;
		}
	}

	//std::cout << depth << ", " << filesize << ", " << filecount << std::endl;
	for (int i = 0; i < depth; i++) {
		max *= filecount;
	}
	std::thread(printPercent).detach();

	std::filesystem::remove_all("Recursive!\\");
	recursivCreate(1, depth, "Recursive!\\");
	std::cout << "100%\n";
}

void recursivCreate(int depth, int goal, std::string prefix) {
	std::filesystem::create_directory(prefix.c_str());
	if (depth == goal) {
		for (int i = 0; i < filecount; i++) {
			std::string path = prefix;
			for (int j = 0; j < 4; j++) {
				path += characters[((char*)&i)[3 - j] >> 4 & 15];
				path += characters[((char*)&i)[3 - j] & 15];
			}
			std::ofstream(path).close();
			std::filesystem::resize_file(std::filesystem::path(path), filesize);
			done++;
		}
		return;
	}
	for (int i = 0; i < filecount; i++) {
		std::string path = prefix;
		for (int j = 0; j < 4; j++) {
			path += characters[((char*)&i)[3 - j] >> 4 & 15];
			path += characters[((char*)&i)[3 - j] & 15];
		}
		path += '\\';
		recursivCreate(depth + 1, goal, path);
	}
}

void printPercent() {
	while (true) {
		std::cout << float(done) / max * 100 << "%\n";
		//std::cout << done << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
}