/**
 * @file main.c
 * @brief Software Emulation of the Hardware-Level Moore Finite State Machine
 * @author Facundo Nicolas Castro (Treetech)
 * 
 * NOTE: The physical vehicle runs 100% on pure digital logic hardware (JK Flip-Flops & Gates).
 * This file serves as a software behavioral simulation of that physical circuit.
 */

#include <stdio.h>
#include <stdbool.h>

// --- Definición de Entradas de Sensores (SI | SD) ---
typedef enum {
    WALL_FRONT = 0x00,  // 00: Detecta pared enfrente
    WALL_LEFT  = 0x01,  // 01: Detecta pared a la izquierda
    WALL_BOTH  = 0x03,  // 11: Vía muerta / Esquina
    WALL_RIGHT = 0x02   // 10: Detecta pared a la derecha / Vía libre
} SensorsInput_t;

// --- Estados de la Máquina de Moore (Q0 Q1) ---
typedef enum {
    STATE_A = 0, // Avanzar (00)
    STATE_B = 1, // Girar a la izquierda (01)
    STATE_C = 2, // Girar a la derecha (10)
    STATE_D = 3  // Parar (11 - No usado)
} FSMState_t;

// Simulación de las lecturas físicas de los sensores
SensorsInput_t read_sensors_emulation(void) {
    return WALL_RIGHT; // Emulación de un paso: pared a la derecha
}

// Emulación de las ecuaciones booleanas de salida hacia los motores
void evaluate_hardware_outputs(FSMState_t state) {
    unsigned char mi = 0;
    unsigned char md = 0;

    // Ecuaciones booleanas obtenidas de los Mapas de Karnaugh:
    // MI = Q1'  y  MD = Q0'
    unsigned char q1 = (state >> 0) & 0x01;
    unsigned char q0 = (state >> 1) & 0x01;

    mi = !q1;
    md = !q0;

    printf("[Hardware Out] Estado: %d | Motores -> MI: %d, MD: %d (", state, mi, md);
    if (mi && md)       printf("AVANZAR)\n");
    else if (!mi && md) printf("GIRAR IZQUIERDA)\n");
    else if (mi && !md) printf("GIRAR DERECHA)\n");
    else                printf("PARAR)\n");
}

int main(void) {
    // Estado inicial: Estado A (00)
    FSMState_t current_state = STATE_A;
    
    printf("--- Emulación de Circuito Lógico Secuencial (FSM) ---\n");

    // El bucle emula los flancos de reloj (CLOCK) que sincronizan los Flip-Flops JK
    for (int clock_tick = 0; clock_tick < 5; clock_tick++) {
        
        // 1. Las salidas dependen únicamente del estado actual (Máquina de Moore)
        evaluate_hardware_outputs(current_state);

        // 2. Captura de señales eléctricas de los sensores (SI, SD)
        SensorsInput_t inputs = read_sensors_emulation();

        // 3. Lógica de próximo estado (Emulación de la tabla de transición implementada con compuertas)
        switch (current_state) {
            case STATE_A:
                if (inputs == WALL_FRONT || inputs == WALL_LEFT) current_state = STATE_B;
                else if (inputs == WALL_BOTH)                  current_state = STATE_C;
                else if (inputs == WALL_RIGHT)                 current_state = STATE_A;
                break;

            case STATE_B:
                if (inputs == WALL_RIGHT)                      current_state = STATE_A;
                else                                          current_state = STATE_B; 
                break;

            case STATE_C:
                if (inputs == WALL_FRONT || inputs == WALL_LEFT) current_state = STATE_B;
                else if (inputs == WALL_BOTH)                  current_state = STATE_C;
                else if (inputs == WALL_RIGHT)                 current_state = STATE_A;
                break;

            default:
                current_state = STATE_A;
                break;
        }
    }

    return 0;
}
