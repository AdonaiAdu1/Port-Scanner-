#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main() {
    cout << "=== PORT SCANNER ===" << endl;
    cout << "Enter target IP: ";
    
    string ip;
    cin >> ip;
    
    cout << endl << "Scanning common ports..." << endl << endl;
    
    int ports[] = {21, 22, 23, 25, 53, 80, 110, 143, 443, 993, 995, 3306, 3389, 8080};
    string names[] = {"FTP", "SSH", "Telnet", "SMTP", "DNS", "HTTP", "POP3", "IMAP", "HTTPS", "IMAPS", "POP3S", "MySQL", "RDP", "HTTP-Alt"};
    int total = 14;
    
    int openPorts[14];
    int openCount = 0;
    
    for(int i = 0; i < total; i++) {
        // Create socket
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if(sock < 0) {
            cout << "Socket error" << endl;
            return 1;
        }
        
        // Setup address
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(ports[i]);
        inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);
        
        // Try to connect
        int result = connect(sock, (struct sockaddr*)&addr, sizeof(addr));
        
        cout << "Port " << ports[i] << " (" << names[i] << "): ";
        
        if(result == 0) {
            cout << "OPEN" << endl;
            openPorts[openCount] = ports[i];
            openCount++;
        } else {
            cout << "CLOSED" << endl;
        }
        
        close(sock);
    }
    
    cout << endl << "=== SUMMARY ===" << endl;
    cout << "Total open ports: " << openCount << endl;
    
    if(openCount > 0) {
        cout << "Open ports: ";
        for(int i = 0; i < openCount; i++) {
            cout << openPorts[i];
            if(i < openCount - 1) cout << ", ";
        }
        cout << endl;
        cout << "Recommendation: Close unnecessary ports" << endl;
    } else {
        cout << "No common ports open. Good security!" << endl;
    }
    
    return 0;
}
