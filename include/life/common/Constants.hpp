#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <configure.h>

#include <life/common/Types.hpp>

DV_LIFE_OPEN_NAMESPACE

static constexpr int ENUM_INVALID = -1;

/* Costanti I/O */

/**
 * NOTE NIC 08/04/2020: gestione cancali I/O
 * ci sono alcuni I/O che possono non essere gestiti attraverso I/O fisici
 * ma attraverso altre ingressi che chiamo I/O virtuali
 * (esempio Abort del CN, puo' non essere in ingresso ad un I/O numerico ma e' associato
 * al valore di una variabile del CN stesso)
 * per distinguere i casi, gestisco i 2 tipi di canale con numerazione differente
 */
static constexpr int DIGITAL_INPUT_VIRTUAL_CHANNEL = -1;
static constexpr int DIGITAL_OUTPUT_VIRTUAL_CHANNEL = -1;
static constexpr int ANALOG_INPUT_VIRTUAL_CHANNEL = -1;
static constexpr int ANALOG_OUTPUT_VIRTUAL_CHANNEL = -1;
static constexpr int DIGITAL_INPUT_CHANNEL_NONE = -1024;
static constexpr int DIGITAL_OUTPUT_CHANNEL_NONE = -1024;
static constexpr int ANALOG_INPUT_CHANNEL_NONE = -1024;
static constexpr int ANALOG_OUTPUT_CHANNEL_NONE = -1024;


/**
 * NOTE NIC 06/04/2020: gestine IO
 * suddivido i bit in categorie; ciascuna categoria puo' contenere 256 input [0, 255];
 * in questo modo posso gestire piu' facilmente gli I/O generici
 * [0...7] : identificano il singolo input
 * [8..15] : identificano la categoria
 */
static constexpr int DIGITAL_INPUT_MASK = 0x00;         // 0   (max 256 input digitali)
static constexpr int DIGITAL_OUTPUT_MASK = 0x01 << 8;   // 256 (max 256 output digitali)
static constexpr int ANALOG_INPUT_MASK = 0x02 << 8;     // 512 (max 256 input analogici)
static constexpr int ANALOG_OUTPUT_MASK = 0x03 << 8;    // 768 (max 256 output analogici)

static constexpr analogReal ANALAG_GAIN_DEFAULT = 1.0;
static constexpr analogReal ANALAG_HYSTERESIS_DEFAULT = 1.0;

DV_LIFE_CLOSE_NAMESPACE

#endif // CONSTANTS_HPP
