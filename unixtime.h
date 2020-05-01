#ifndef LIB_UNIXTIME_H
#define LIB_UNIXTIME_H


#include <inttypes.h>


#ifdef __cplusplus
extern "C" {
#endif


// Структура для даты и времени
typedef struct
{
	uint16_t year;		/* 1970 -> */
	uint8_t  month;		/* 1 - 12  */
	uint8_t  day;		/* 1 - 31  */
	uint8_t  wday;		/* 0 - 6   Mon->Sun*/
	uint8_t  hour;		/* 0 - 23  */
	uint8_t  min;		/* 0 - 59  */
	uint8_t  sec;		/* 0 - 59  */
} DATETIME;


/*
 * Функция rtc_to_unixtime()
 * Возвращает unixtime соответствующую указанной в dt дате и времени
 */
uint32_t to_unixtime(DATETIME *dt);


/*
 * Функция rtc_from_unixtime()
 * Возвращает в dt разобранную из unixtime дату и время
 */
void from_unixtime(uint32_t unixtime,DATETIME *dt);


#ifdef __cplusplus
}
#endif


#endif
