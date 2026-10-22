# ESP8266_ESP32_SelfUpdate

[Kurze Änderungsübersicht](AENDERUNGEN_README_2026-10-21.md)

## 🚀 Firmware selbst vom Server laden – zwei getrennte OTA-Beispiele

![Plattform](https://img.shields.io/badge/Plattform-ESP8266%20/%20ESP32-blue) ![Schnittstelle](https://img.shields.io/badge/Schnittstelle-HTTP%28S%29--Download-orange)

Beispielsammlung für selbst gestartete Firmware-Downloads. Die ESP32- und ESP8266-Varianten verwenden unterschiedliche Verfahren; daraus entsteht noch kein allgemeiner gerätespezifischer Updateservice.

**Dokumentationsstand:** 21.10.2026 · Branch `master`. Beschreibt den vorhandenen Projektstand; kein neuer Funktionstest am Gerät.

[Quellcode herunterladen](https://github.com/TimiWho/ESP8266_ESP32_SelfUpdate/archive/refs/heads/master.zip) · [Ursprüngliche Haupt-README](README_Backup_2026-10-21.md)

---

## ⚙️ Softwarevarianten

| Sketch | Verhalten | Relevante Bezeichner |
| --- | --- | --- |
| [esp32_ota/esp32_ota.ino](esp32_ota/esp32_ota.ino) | Prüft Versionsdatei alle 60000 ms, lädt bei abweichendem String ein Binärabbild. BOOT/GPIO0 kann einen direkten Download anfordern. | FirmwareVer, URL_fw_Version, URL_fw_Bin, interval, mini_interval, button_boot |
| [esp8266_ota/esp8266_ota.ino](esp8266_ota/esp8266_ota.ino) | Startet Updateversuche nach WLAN-Verbindung; 10000 ms Pause nach Fehler/kein Update, Neustart nach erfolgreichem Update. | FIRMWARE_VERSION, ESPhttpUpdate, update_started/finished/progress/error |

## 🔌 Inputs, Outputs und Grenzen

ESP32: BOOT-Eingang GPIO0 (`RISING`-Interrupt); `LED_BUILTIN` zeigt Updateaktivität. `mini_interval=1000` ms steuert Diagnose-/WLAN-Prüfung. Das Versionskriterium ist **ungleich**, kein numerischer Versionsvergleich.

ESP8266: `FIRMWARE_VERSION` wird angezeigt, beim aktiven `ESPhttpUpdate.update(...)` aber nicht als Versionsargument übergeben. Die URL ist HTTPS, während der aktive Code einen einfachen `WiFiClient` erzeugt; eine funktionierende TLS-Konfiguration ist damit nicht belegt. Der ESP32-Code verwendet dagegen `WiFiClientSecure` und `cert.h`.

Update-URLs sind fest im jeweiligen Sketch definiert. Es gibt keine automatische Auswahl nach Chip-ID, Gerätename oder Firmwarefamilie. Für mehrere Geräte müssen die passenden Ziele und Images explizit eingerichtet werden.

## 🛠️ Inbetriebnahme

Jeweiligen Sketch separat für die passende Plattform kompilieren, WLAN und Updateziele anpassen und zuerst seriell installieren. Beim ESP32 muss das CA-Zertifikat zu den tatsächlich verwendeten HTTPS-Zielen passen. Vorhandene Beispiel-URLs und Binärdateien sind keine bestätigte aktuelle Firmwareversorgung.

## 🐞 GitHub-Issues

**Abgleich:** 21.10.2026. Status aus GitHub; diese Übersicht ändert keine Issues.

Zum Abgleichzeitpunkt sind keine offenen GitHub-Issues vorhanden.

In diesem Repository sind zum Abgleichzeitpunkt keine GitHub-Issues vorhanden.

## 🗂️ Ursprüngliche Projektdokumentation

Die ursprünglichen technischen Erläuterungen, Quellenangaben und Autorenhinweise bleiben nachfolgend erhalten. Maßgeblich für konkrete Pin- und Timerwerte ist der oben beschriebene Repository-Stand.

<details>
<summary>Ursprüngliche Projektdokumentation anzeigen</summary>

repo contains Arduino sketch that include self OTA support.

ESP32 OTA Demo: https://youtu.be/qCmdUtguwPw

demonstration and code explanation https://youtu.be/FuY6BobS-1k

Just another small demo:  https://youtu.be/2J8KK5Cxf6g

Update: removed fingerprint and added rootca certificate for esp8266 but bin file downloading
is quite slow now.

June 2022 update: Instead of using static url in your firmware, just send it in mqtt message, this way you can avoid scenarios where url/domain goes offline. This project utilize this technique, https://github.com/programmer131/cam-flood-light


</details>

