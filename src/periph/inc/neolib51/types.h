/**
 * @author Li Kangfeng
 * @brief primative data type defines
 */

#ifndef __NEOLIB51_TYPES_H
#define __NEOLIB51_TYPES_H

/* Integer typed */
typedef unsigned char uint8_t;
typedef char int8_t;
typedef unsigned int uint16_t;
typedef int int16_t;
typedef unsigned long uint32_t;
typedef long int32_t;

/* Float types */
typedef float float32_t;

/* Boolean types */
typedef enum
{
    FALSE = 0,
    TRUE = 1
} bool_t;

/* Null pointer */
#define null ((void *)0)

#endif