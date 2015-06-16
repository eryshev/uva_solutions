/*
*	ACM-ICPC 3310 Tomato Automata
*	This solution is not accepted.
*/
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <utility>
#include <cstring>

using namespace std;

enum Coms {PASS, DIE, IFGO, LOOP, JUMP};

class Command {
public:
	static long counter;
	static long max_counted;

	int line;
	Coms type;

	Command(int line, Coms type) 
		: line(line), type(type)
	{}

	virtual ~Command() {};

	virtual string to_string() const = 0;
};

vector<Command*> programm;

class Pass: public Command {
public:
	Pass(int line) 
	: Command(line, PASS) {}

	virtual string to_string() const {return "Pass" + std::to_string(line);}
};


class Die: public Command {
public:
	Die(int line) 
	: Command(line, DIE) {}

	virtual string to_string() const {return "Die" + std::to_string(line);}
};


class IfGo: public Command {
public:
	int first, second;

	IfGo(int line, int second) 
	: Command(line, IFGO), first(line + 1), second(second) {}

	virtual string to_string() const {return "IfGo" + std::to_string(line);}
};

class Jump: public Command {
public:
	int to_jump;

	Jump(int line, int to_jump) 
	: Command(line, JUMP), to_jump(to_jump) {}

	virtual string to_string() const {return "Jump" + std::to_string(line);}
};


class Loop: public Command {
public:
	int start, count;

	Loop(int line, int start, int count) 
	: Command(line, LOOP), start(start), count(count) {}

	virtual string to_string() const {return ("Loop" + std::to_string(line));}
};

// vector<pair<int, int>> memo;
// long answer;

bool visited[500];
bool inf;
int prog_len;

long solution(int start, int finish) {
	bool state[500];
	int line = start;

	// printf("%d\n", line + 1);

	if (start >= finish) {
		inf = true;
		return 0;
	}

	if (visited[line]) inf = true;
	else visited[line] = true;

	if (inf) return 0;

	switch (programm[line]->type) {
		case PASS:
			// printf("PASS\n");
			return 1 + solution(line + 1, finish);
			break;
		case JUMP:
			// printf("JUMP\n");
			return 1 + solution(static_cast<Jump*>(programm[line])->to_jump, finish);
			break;
		case IFGO: {
			// printf("IFGO\n");
			memcpy(state, visited, prog_len);
			long sol1 = solution(static_cast<IfGo*>(programm[line])->second, finish);
			memcpy(visited, state, prog_len);
			long sol2 = solution(line + 1, finish);
			memcpy(visited, state, prog_len);
			return 1 + max(sol1, sol2);
			break;
		}
		case  DIE:
			// printf("DIE\n");
			return 1;
			break;
		case  LOOP: {
			// printf("LOOP\n");
			auto loop = static_cast<Loop*>(programm[line]);
			memcpy(state, visited, prog_len);
			memset(visited, false, prog_len);
			long sol1 = solution(loop->start, loop->line);
			memcpy(visited, state, prog_len);
			return loop->count + (loop->count-1) * sol1 + solution(loop->line + 1, finish);
			break;
		}
	}

	return -1;
}

int main() {
	string command, line;
	stringstream is;
	int line_counter, n, m;
	bool die_is_existed;

	while(true) {
		bool has_next = false; 
		die_is_existed = false;
		programm.clear();
		line_counter = 0;
		inf = false;

		while (getline(cin, line))
		{	
			// cout << "line=" << line << endl;
			if (line.empty()) break;
			else is.str(line);

			is >> command;

			// cout << "cmd=" << command << endl;
			has_next = true;
			if (command.compare("pass") == 0) {
				programm.push_back(new Pass(line_counter++));
			} else if (command.compare("die") == 0) {
				die_is_existed = true;
				programm.push_back(new Die(line_counter++));
			} else if (command.compare("ifgo") == 0) {
				is >> n;
				n--;
				programm.push_back(new IfGo(line_counter++, n));
			} else if (command.compare("jump") == 0) {
				is >> n;
				n--;
				programm.push_back(new Jump(line_counter++, n));
			} else if (command.compare("loop") == 0) {
				is >> n >> m;
				n--;
				programm.push_back(new Loop(line_counter++, n, m));
			}  

		}
		if (!has_next) return 0;

		if (!die_is_existed) cout << "infinity" << endl; 
		else {
			// cout << solution(0, int(programm.size())) << endl;
			memset(visited, false, programm.size());
			prog_len = int(programm.size());
			long answer = solution(0, prog_len);
			if (inf) cout << "infinity" << endl; 
			else cout << answer << endl;
		}
	}

	return 0;
}