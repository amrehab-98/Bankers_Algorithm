#include<iostream>
#include<vector>

using namespace std;

bool isSafe(vector<int> &sequence, vector<int> available, vector<vector<int>> need, vector<vector<int>> allocation) {
	int n = need.size();
	int m = available.size();
	vector<int> work = available;

	vector<bool> finish(n, false);

	bool change = false;

	while (true) {
		change = false;
		for (int i = 0; i < n; i++) {
			if (finish[i] == false) {
				bool ok = true;
				for (int j = 0; j < m; j++) {
					if (need[i][j] > work[j]) {
						ok = false;
						break;
					}
				}
				if (ok) {
					finish[i] = true;
					sequence.push_back(i);
					change = true;
					for (int j = 0; j < m; j++) {
						work[j] += allocation[i][j];
					}
				}
			}
		}
		if (!change) {
			break;
		}
	}

	for (int i = 0; i < n; i++) {
		if (finish[i] == false) {
			return false;
		}
	}
	return true;
}

vector<vector<int>> getNeed(vector<vector<int>> max, vector<vector<int>> allocation) {
	int n = max.size();
	int m = max[0].size();
	vector<vector<int>> need(n,vector<int>(m));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			need[i][j] = max[i][j] - allocation[i][j];
		}
	}

	return need;
}

void handleRequest(int process_number, vector<int> request, vector<vector<int>> need, vector<vector<int>> allocation, vector<int> available, vector<int>& sequence) {

	cout << "\n";
	for (int i = 0; i < request.size(); i++) {
		if (request[i] > need[process_number][i]) {
			cout << "Error, process has exceeded its maximum claim";
			return;
		}
	}
	for (int i = 0; i < request.size(); i++) {
		if (request[i] > available[i]) {
			cout << "Not Granted";
			return;
		}
	}
	for (int i = 0; i < request.size(); i++) {
		available[i] -= request[i];
		allocation[process_number][i] += request[i];
		need[process_number][i] -= request[i];
	}

	

	if (isSafe(sequence, available, need, allocation)) {
		
		bool finished = true;
		for (int j = 0; j < allocation[0].size(); j++) {
			if (need[process_number][j] != 0) {
				finished = false;
				break;
			}
		}
		if (!finished) {
			cout << "Yes request can be granted with safe state, Safe state: <P" << process_number << "req,";
			for (int i = 0; i < sequence.size(); i++) {
				cout << "P" << sequence[i];
				if (i != sequence.size() - 1) {
					cout << ",";
				}
			}
			cout << ">";
		}
		else {
			cout << "Yes request can be granted with safe state, Safe state: <P" << process_number << "req,";
			for (int i = 0; i < sequence.size(); i++) {
				if (sequence[i] != process_number) {
					cout << "P" << sequence[i];
					if (i != sequence.size() - 1) {
						cout << ",";
					}
				}
			}
			cout << ">";
		}

	}
	else {
		cout << "Not Granted";
	}

	
}

int main() {
	int n,m;
	cout << "Enter number of Resources: ";
	cin >> m;
	cout << "Enter number of Processes: ";
	cin >> n;
	cout << "\n";
	vector<int> resources(m);
	vector<int> processes(n);

	vector<vector<int>> max(n, vector<int>(m));
	vector<vector<int>> allocation(n, vector<int>(m));
	vector<vector<int>> need(n, vector<int>(m));
	
	vector<int> available(m);
	vector<int> sequence;
	
	//input
	for (int i = 0; i < n; i++) {
		cout << "Enter allocation of P" << i << ": ";
		for (int j = 0; j < m; j++) {
			cin >> allocation[i][j];
		}
	}
	cout << "\n";

	for (int i = 0; i < n; i++) {
		cout << "Enter max of P" << i << ": ";
		for (int j = 0; j < m; j++) {
			cin >> max[i][j];
		}
	}
	cout << "\n";
	cout << "Enter available matrix: ";
	for (int i = 0; i < m; i++) {
		cin >> available[i];
	}
	cout << "\n";
	need = getNeed(max, allocation);
	for (int i = 0; i < need.size(); i++) {
		cout << "Need of P" << i << ": ";
		for (int j = 0; j < need[0].size(); j++) {
			cout << need[i][j] << " ";
		}
		cout << "\n";
	}
	

	cout << "\nChoose Algorithm:\n1. Safety Algorithm\n2. Request Algorithm\n";
	int algorithm;
	cin >> algorithm;
	if (algorithm == 1) {
		cout << "\n";
		if (isSafe(sequence, available, need, allocation))
		{
			cout << "Yes, Safe state: <";
			for (int i = 0; i < sequence.size(); i++) {
				cout << "P" << sequence[i];
				if (i != sequence.size() - 1) {
					cout << ",";
				}
			}
			cout << ">";
		}
		else {
			cout << "Not Safe";
		}
	}
	else if(algorithm==2){
		cout << "Enter number of process making the request: ";
		int process_number;
		cin >> process_number;

		vector<int> request(m);
		cout << "Enter request: ";
		for (int i = 0; i < m; i++) {
			cin >> request[i];
		}
		handleRequest(process_number, request, need, allocation, available, sequence);
	}
	else {
		"Error";
	}
	cout << "\n";
	system("pause");
}