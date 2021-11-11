#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>

int filesize = 0;

void recursivCreate(int depth, int goal, std::string prefix) {
	std::filesystem::create_directory(prefix.c_str());
	if (depth == goal) {
		for (int i = 0; i < 10; i++) {
			std::string path = prefix;
			path += (i + 48);
			std::ofstream(path).close();
			std::filesystem::resize_file(std::filesystem::path(path), filesize);
		}
		return;
	}
	for (int i = 0; i < 10; i++) {
		std::string path = prefix;
		path += (i + 48);
		path += '\\';
		recursivCreate(depth + 1, goal, path);
	}
}

int main(int argc, char** argv) {
	int depth;

	if (argc > 1)
		depth = atoi(argv[1]);
	else
		depth = 5;
	if (argc > 2)
		filesize = atoi(argv[2]);

	std::filesystem::remove_all("Recursive!\\");
	recursivCreate(1, depth, "Recursive!\\");
}