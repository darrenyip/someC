/*
 * The linked list struct which will be used in functions
 */
typedef struct flightRecord {
    char AirlineCodeFlightNumber[4];
    char OriginAirportCode[3];
    char DestinationAirportCode[3];
    char DepartureDate[100];
} flightRecord;

typedef struct flightList {
  flightRecord record;
  struct flightList *next;
} flightList;
