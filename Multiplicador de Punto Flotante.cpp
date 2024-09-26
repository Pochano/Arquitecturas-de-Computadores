#include <iostream>
#include <bitset>
#include <cstdint>
#include <limits>


void imprimir_num_flotante(float f) {
    uint32_t bits;
    std::memcpy(&bits, &f, sizeof(bits));
    std::bitset<32> patron_bits(bits);
    std::cout << "Bits: " << patron_bits << "\n";
}

uint32_t obtener_signo(float f) {
    uint32_t bits;
    std::memcpy(&bits, &f, sizeof(bits));
    return (bits >> 31) & 1;
}

uint32_t obtener_exponente(float f) {
    uint32_t bits;
    std::memcpy(&bits, &f, sizeof(bits));
    return (bits >> 23) & 0xFF;
}

uint32_t obtener_mantisa(float f) {
    uint32_t bits;
    std::memcpy(&bits, &f, sizeof(bits));
    return bits & 0x7FFFFF; // "23 bits de la mantisa"
}


float Multiplicacion_flotantes(float a, float b) {
    
    uint32_t signo_a = obtener_signo(a);
    uint32_t signo_b = obtener_signo(b);
    uint32_t exponente_a = obtener_exponente(a);
    uint32_t exponente_b = obtener_exponente(b);
    uint32_t mantisa_a = obtener_mantisa(a);
    uint32_t mantisa_b = obtener_mantisa(b);


    if (a == 0.0f || b == 0.0f) {
        return 0.0f;
    }

    uint32_t sign_result = signo_a ^ signo_b;

    int32_t exp_result = (exponente_a - 127) + (exponente_b - 127) + 127;

    if (exp_result >= 255) {
        std::cout << "Overflow detectado. Retornando infinito.\n";
        return std::numeric_limits<float>::infinity();
    }
    else if (exp_result <= 0) {
        std::cout << "Underflow detectado. Retornando 0.\n";
        return 0.0f; 
    }

    uint64_t mantisa_a_extendida = mantisa_a | 0x800000; 
    uint64_t mantisa_b_extendida = mantisa_b | 0x800000;
    uint64_t resultado_mantisa = (mantisa_a_extendida * mantisa_b_extendida) >> 23;

    
    if (resultado_mantisa & 0x1000000) {
        resultado_mantisa >>= 1;
        exp_result++;
    }

    uint32_t resultado = (sign_result << 31) | (exp_result << 23) | (resultado_mantisa & 0x7FFFFF);
    float resultado_flotante;
    std::memcpy(&resultado_flotante, &resultado, sizeof(resultado_flotante));
    return resultado_flotante;
}

int main() {
    float num1, num2;
    std::cout << "Ingrese el primer numero: ";
    std::cin >> num1;
    std::cout << "Ingrese el segundo numero: ";
    std::cin >> num2;

    std::cout << "\nNumero 1 (bits): ";
    imprimir_num_flotante(num1);
    std::cout << "Numero 2 (bits): ";
    imprimir_num_flotante(num2);

    float result_emulated = Multiplicacion_flotantes(num1, num2);

    std::cout << "\nResultado (bits): ";
    imprimir_num_flotante(result_emulated);

    std::cout << "\nResultado decimal " << result_emulated << std::endl;

    return 0;
}