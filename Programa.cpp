#include <iostream>
#include <unistd.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <sstream>
#include <vector>
#include <thread>
#include <iterator>

using namespace std;

pthread_mutex_t mutex; // Mutex para controlar el acceso a la memoria compartida

template <typename Out> // Funcion para separar los datos de un string

void split(const std::string &s, char delim, Out result) // Funcion para separar los datos de un string
{
	std::istringstream iss(s);
	std::string item;
	while (std::getline(iss, item, delim))
	{
		*result++ = item;
	}
}

std::vector<std::string> split(const std::string &s, char delim)
{
	std::vector<std::string> elems;
	split(s, delim, std::back_inserter(elems));
	return elems;
}

class PingData // Clase para guardar los datos de cada ping
{
private: // Atributos
	string ip;
	int transmitted;
	int received;
	int lost;
	int state;

public:															 // Metodos
	PingData(string ip, int transmitted, int received, int lost) // Constructor
	{
		this->ip = ip;
		this->transmitted = transmitted;
		this->received = received;
		this->lost = lost;
		this->state = this->received > 0;
	}

	string getIp() // Metodo para obtener la ip
	{
		return this->ip;
	}

	int getTransmitted() // Metodo para obtener el numero de paquetes transmitidos
	{
		return this->transmitted;
	}

	int getReceived() // Metodo para obtener el numero de paquetes recibidos
	{
		return this->received;
	}

	int getLost() // Metodo para obtener el numero de paquetes perdidos
	{
		return this->lost * this->transmitted / 100;
	}

	int getState() // Metodo para obtener el estado del ping
	{
		return this->state;
	}
};

void ping(string ping_cmd) // Funcion para ejecutar el ping
{
	pthread_mutex_lock(&mutex);	  // Bloqueamos el mutex
	system(ping_cmd.c_str());	  // Ejecutamos el comando
	pthread_mutex_unlock(&mutex); // Desbloqueamos el mutex
}

int main(int argc, char *argv[])
{

	// Leemos el archivo de entrada
	if (argc < 1 || argc > 3)
	{
		cout << "Uso incorrecto. Solo entregue como argumento el nombre del archivo de IPs." << endl;
		return 0;
	}

	string file_name = argv[1];			// Nombre del archivo de IPs
	int num_ips = 0;					// Cantidad de IPs en el archivo
	int packets = atoi(argv[2]);		// Cantidad de paquetes a enviar
	ifstream infile(file_name.c_str()); // Stream de lectura
	vector<string> ips;					// Vector para almacenar las IPs del archivo

	string line;
	while (getline(infile, line))
	{
		// Leemos la linea
		istringstream iss(line);
		string ip;

		// En caso de haber un error, seguimos leyendo
		if (!(iss >> ip))
		{
			break;
		}

		// Agregamos la IP al vector de IPs
		ips.push_back(ip);
		num_ips++;
	}

	vector<string> ping_cmds;

	// Generamos los comandos de ping
	for (string ip : ips)
	{
		ostringstream cmd_oss;
		cmd_oss << "ping -q -c" << packets << " " << ip << " > logs/" << ip << ".txt";
		string cmd = cmd_oss.str();

		ping_cmds.push_back(cmd);
	}

	pthread_mutex_init(&mutex, NULL); // Inicializamos el mutex

	// Crea todos los hilos
	vector<thread> threads;
	for (string ping_cmd : ping_cmds)
	{
		threads.push_back(thread(ping, ping_cmd)); // Creamos el hilo
	}

	// Espera a que todos los hilos terminen
	for (thread &t : threads)
	{
		t.join();
	}

	pthread_mutex_destroy(&mutex); // Destruye el mutex

	vector<PingData> entries;

	// Se obtienen los datos de los archivos de log
	for (string ip : ips)
	{
		ostringstream ip_file_name_oss;				   // Stream para generar el nombre del archivo de log
		ip_file_name_oss << "./logs/" << ip << ".txt"; // Se guarda en la carpeta logs
		string ip_file_name = ip_file_name_oss.str();  // Nombre del archivo de log
		ifstream infile(ip_file_name.c_str());		   // Stream de lectura

		int line_num = 0;

		// Leemos el archivo de log
		for (string line; getline(infile, line);)
		{
			if (line_num == 3)
			{
				string s = "";
				for (char c : line)
				{
					s += c;
				}

				vector<string> tokens = split(s, ' ');																   // Separamos los datos del string
				PingData pd = PingData(ip, atoi(tokens[0].c_str()), atoi(tokens[3].c_str()), atoi(tokens[5].c_str())); // Creamos un objeto PingData
				entries.push_back(pd);																				   // Agregamos el objeto al vector de objetos

				break;
			}

			line_num++;
		}
	}

	// Se imprime la tabla
	cout << "IP         Trans. Rec. Perd. Estado\n";
	cout << "========================================\n";
	for (PingData entry : entries)
	{
		// Se imprime el reporte de cada IP
		cout << entry.getIp() << "    " << entry.getTransmitted() << "      " << entry.getReceived() << "    " << entry.getLost() << "     " << (entry.getState() ? "UP" : "DOWN") << endl;
	}
	return 0;
}
