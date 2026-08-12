# MSP Протокол

> *MultiWii Последовательный протокол —, как Конфигуратор взаимодействует с OrniFlight.*

## Обзор

OrniFlight расширяет Betaflight MSP сообщениями, специфичными для орнитоптеров. Авторитетная спецификация находится в репозитории прошивки по адресу `src/main/msp/`.

**Текущая версия:** apiVersion 1.46 (OrniFlight v0.4.6)

## Ключевые сообщения

###MSP_PID_ADVANCED (112/0x70)

Основной посыл настройки ONDAS. Размер увеличен с 48 байт (устаревший) до 87 байт (1,46).

| API Версия | Размер | Новое содержание |
|-------------|------|-------------|
| 1,33 | 48 | Legacy PID продвинутый |
| 1,42 | 59 | + itermRelaxCutoff, 10 приростов ONDAS v2 |
| 1,43 | 71 | + servo_mount_angle[4], Phase_shift[4], Prescience, espelho, saudade, ssff |
| 1,44 | 75 | + servo_speed, max_amplitude, закрылков_величины, wing_origin_offset[4] |
| 1,45 | 82 | + freq_channel, freq_min_hz, freq_max_hz, Flight_mode, flutter_gain, flutter_hz, throttle_bypass |
| 1,46 | 87 | + Profile_index,ferocity_downstroke,ferocity_upstroke, aeroelastic_glide, aeroelastic_flap |

###MSP_SERVO_CONFIGURATIONS (120/0x78)

Конфигурация сервопривода с 4 завершающими байтами ONDAS: glide_deg + триплет ONDAS v1.

## Обратная совместимость

Все версии API обратно совместимы. Отправитель размером 48 байт общается с получателем 1.46. — дополнительные поля по умолчанию имеют разумные значения.

## Формат провода

Все многобайтовые значения имеют прямой порядок байтов. Значения со знаком, хранящиеся в сети как `value + 128`. Значения усиления без знака (0–100) являются прямыми. Длине массива предшествует счетчик u8.

---

*Полную спецификацию см. в `docs/MSP_FIRMWARE_INTERFACE.md` в репозитории прошивки.*