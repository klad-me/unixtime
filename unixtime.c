#include "unixtime.h"


// С какого дня года начинается каждый месяц
static const uint16_t rtc_month_days[13] =
{
	0,31,59,90,120,151,181,212,243,273,304,334,365
};


// Сколько дней в каждом месяце
static const uint8_t rtc_days_in_month[12] =
{
	31,28,31,30,31,30,31,31,30,31,30,31
};



// Собирает дату в unixtime
uint32_t to_unixtime(DATETIME *dt)
{
	uint8_t year=dt->year-1900;
	uint16_t days=rtc_month_days[dt->month-1];
	
	if ( (!(year%4)) && (dt->month>2) ) days++;
	
	return (86400L * (
			365L*(uint32_t)(year-80) + (uint32_t)(year-77)/4 +
			(uint32_t)days +
			(uint32_t)(dt->day-1) + 3652L) +
			3600L * (uint32_t)dt->hour +
			60L * (uint32_t)dt->min + (uint32_t)dt->sec);
}



// Разбирает unixtime в DATETIME
#define monsize(mon) (mon == 25 ? 29 : rtc_days_in_month[mon%12])
void from_unixtime(uint32_t unixtime,DATETIME *dt)
{
	uint8_t  mon=0;
	uint32_t days=unixtime/86400L;
	uint16_t fouryears=(uint16_t)((uint32_t)days/1461L);
	int16_t  overdays=(uint16_t)((uint32_t)days%1461L);
	
	for (;;)
	{
		int16_t day=overdays;
		
		if ( (overdays-=monsize(mon))<0 )
		{
			dt->year =4*fouryears+(mon/12)+1970;
			dt->month=mon%12+1;
			dt->day  =day+1;
			dt->wday =(days+4)%7;
			dt->hour =(uint32_t)(unixtime%86400L)/3600L;
			dt->min  =(uint32_t)(unixtime%3600L)/60L;
			dt->sec  =unixtime%60L;
			
			if (dt->wday==0) dt->wday=7;
			dt->wday--;
			return;
		}
		mon++;
	}
}
