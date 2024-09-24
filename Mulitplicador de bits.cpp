#include <iostream>
#include <bitset>
#include <cmath>


const int n = 8;

std::bitset<n> Suma_Binaria(std::bitset<n> Cadena_A, std::bitset<n> Cadena_B) {

    return std::bitset<n>(Cadena_A.to_ulong() + Cadena_B.to_ulong());

}

std::bitset<n> Resta_Binaria(std::bitset<n> Cadena_A, std::bitset<n> Cadena_B) {

    return std::bitset<n>(Cadena_A.to_ulong() - Cadena_B.to_ulong());

}


void Corrimiento_Aritmetico_Derecha(std::bitset<n>& Cadena_A, std::bitset<n>& Cadena_Q, bool& Q_1) {

    bool Bit_de_Signo = Cadena_A[n - 1];  
    Q_1 = Cadena_Q[0];  
    Cadena_Q >>= 1; 
    Cadena_Q[n - 1] = Cadena_A[0];  
    Cadena_A >>= 1;  
    Cadena_A[n - 1] = Bit_de_Signo ;  

}

void Multiplicacion_Booth(int Multiplicando, int Multiplicador) {
    std::bitset<n> Cadena_A(0); 
    std::bitset<n> Cadena_M(Multiplicando);
    std::bitset<n> Cadena_Q(Multiplicador);
    bool Q_1 = 0;
    int Contador = n;

    while (Contador > 0) {
       
        if (Cadena_Q[0] == 1 && Q_1 == 0) {
            Cadena_A = Resta_Binaria(Cadena_A, Cadena_M);
        }
        else if (Cadena_Q[0] == 0 && Q_1 == 1) {
            Cadena_A = Suma_Binaria(Cadena_A, Cadena_M);
        }

        Corrimiento_Aritmetico_Derecha(Cadena_A, Cadena_Q, Q_1);

        
        Contador--;
    }

    std::cout << "Resultado final (Cadena_A y Cadena_Q): " << Cadena_A << " " << Cadena_Q << std::endl;

    if (Cadena_A[n - 1] == 0) {
        std::cout << "Resultado en decimal: " << ((Cadena_A.to_ulong() << n) + Cadena_Q.to_ulong()) << std::endl;
    }
}

int main() {
    int Multiplicando = -5;
    int Multiplicador = 4;

    Multiplicacion_Booth(Multiplicando, Multiplicador);

    return 0;
}