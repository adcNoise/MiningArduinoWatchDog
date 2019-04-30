# watchDog для майнинга на Arduino
Прошивка ATMega328p для контроля состояния фермы и последующей её автоматической перезагрузки.

Линии PWR_SW, RESET_SW, HDD_LED в данном приборе можно подключать напрямую к материнской плате и не бояться, что плата будет сожжена высоким напряжением. Данная прошивка управляет линиями выхода таким образом, что порт при высоком уровне напряжения находится в режиме Hi-Z т.е. напряжение не поднимается выше напряжения подтяжки. А при необходимости управления портом линия просто притягивается к земле.
