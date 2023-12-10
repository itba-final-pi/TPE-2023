
# POSSIBLE ERRORS
- empty file
    - update fileHandler to handle it
- wrong arg count ✅
-



# CITY_STATIONS FUNCTION ERRORS 

## CHEQUEAR NULL PUEDE SER UNA MACRO

- newCityStation: ✅
    - NULL si malloc falla

- loadStation
    - TODO: usar errno, que sea void

- addRecursive
    - TODO: usar errno, que sea void

- getStationsCount ???
    - validar que city no sea NULL?

- addStation
    - TODO: usar errno, que sea void

- getStation ??? 
    - devuelve NULL en id fuera de rango
    - debería chequear city == NULL?

- freeCityStations ???
    - debería chequear city == NULL?
    - otra cosa no falla
    - doble free no se puede evitar parece

- processTrip
    - TODO: usar errno, que sea void
    - validar fechas? (poco eficiente)
        - si no lo hacemos es medio incoherente
    - ver qué error se puede devolver si no existe la station con el id que se le pasó

- getStartedTripsByDay 
    - TODO: bug en la validación de dia válido

- getEndedTripsByDay
    - TODO: bug en la validación de dia válido

- incrementStartedTripsByDate
    - TODO: usar la fórmula loca por eficiencia
    - ya usa errno

- incrementEndedTripsByDate
    - TODO: usar la fórmula loca por eficiencia
    - ya usa errno

- orderStationsByTrips
    - chequear city == NULL?
    - TODO: usar errno, no un error propio
    - addRecursive va a actualizarse

- toBeginAlphabeticOrder
    - TODO: lo del NULL y ver errores posibles

 MISMO PARA EL RESTO, CHEQUEAR NULL Y VER ERRORES POSIBLES






