## 🚦 Roadmapa Projektu: Monitor Sieciowy (C++)

### Faza I: Fundamenty i Środowisko

1.  [ ] **Konfiguracja Środowiska Deweloperskiego:**
    - Instalacja **C++** (kompilator GCC/Clang) i **CMake**.
    - Inicjalizacja repozytorium **Git** i pierwsza struktura katalogów.
    - Integracja frameworka testowego (**Google Test** lub inny) i napisanie pierwszego, prostego testu.
2.  [ ] **Integracja Bibliotek Sieciowych:**
    - Instalacja i konfiguracja biblioteki **PCAP** (`libpcap` / `Npcap`).
    - Napisanie minimalnego modułu C++, który potrafi przechwycić 10 pakietów i wydrukować ich surowe rozmiary do konsoli.

### Faza II: Serce Systemu i Wydajność (C++ Systemowe)

3.  [ ] **Implementacja Bufora Cyklicznego (Ring Buffer):**
    - Stworzenie **szablonowej** klasy bufora, który przechowuje surowe dane pakietów.
    - Zaprojektowanie metody `push` i `pop` dla danych.
4.  [ ] **Wdrożenie Synchronizacji (Wielowątkowość):**
    - Zabezpieczenie Bufora Cyklicznego za pomocą **`std::mutex`** do ochrony dostępu.
    - Wykorzystanie **`std::condition_variable`** do sygnalizowania wątkom, że pojawiły się nowe pakiety (dla efektywnego oczekiwania).
5.  [ ] **Implementacja Modelu Producent-Konsument:**
    - Stworzenie **Wątku Producenta** (Capture Thread), który tylko pobiera pakiety z PCAP i umieszcza je w buforze.
    - Stworzenie **Wątku Konsumenta** (Analysis Thread), który tylko pobiera pakiety z bufora i przekazuje je do analizy.

### Faza III: Analiza i Parsowanie Protokołów

6.  [ ] **Parsowanie Nagłówka Ethernet:**
    - Zdefiniowanie struktury C++ mapującej nagłówek Ethernet.
    - Wyciągnięcie adresów MAC i typu protokołu wyższego poziomu (np. IP).
7.  [ ] **Parsowanie Nagłówka IP (IPv4):**
    - Zdefiniowanie struktury dla nagłówka IP.
    - Implementacja logiki do wyciągania **adresów IP** (źródłowy i docelowy).
    - Zapewnienie obsługi kolejności bajtów (**Endianness**) dla pól numerycznych (`ntohl`/`ntohs`).
8.  [ ] **Parsowanie Nagłówka Transportowego (TCP/UDP):**
    - Implementacja logiki do wyciągania **portów** (źródłowego i docelowego).
    - Identyfikacja podstawowych flag (np. czy pakiet jest SYN/ACK).

### Faza IV: Statystyki i Raportowanie

9.  [ ] **Zarządzanie Statystykami (KPI):**
    - Stworzenie globalnej struktury lub klasy do bezpiecznego liczenia: całkowitej liczby pakietów, bajtów i podziału protokołów.
    - Wykorzystanie `std::unordered_map` do śledzenia statystyk dla **Top N Hostów** (najczęściej komunikujących się adresów IP).
10. [ ] **Obliczanie Metryk Czasu Rzeczywistego:**
    - Implementacja licznika dla **PPS** (Pakietów na Sekundę) i **Throughput** (Przepustowości w Mb/s).
11. [ ] **Wyświetlanie Wyników:**
    - Implementacja czytelnego formatowania wyjścia.
    - Wyświetlanie zaktualizowanych statystyk w konsoli co stały interwał czasowy (np. 1 sekunda).

### Faza V: Finalizacja i Dokumentacja

12. [ ] **Testy Jednostkowe (Kluczowe):**
    - Przygotowanie kilku buforów zawierających **przykładowe surowe pakiety** (np. ping, żądanie HTTP).
    - Napisanie testów jednostkowych (Google Test) dla **parsera protokołów** (Faza III), weryfikujących poprawność wyciąganych adresów i portów.
13. [ ] **Opcje Wiersza Poleceń:**
    - Dodanie obsługi argumentów wiersza poleceń (np. `-i <interface>` do wyboru interfejsu, `-t <duration>` do czasu działania).
14. [ ] **Dokumentacja Projektu:**
    - Przygotowanie pliku **`README.md`** z instrukcjami kompilacji i uruchomienia.
    - Stworzenie krótkiego **Design Document** (`DESIGN.md`), wyjaśniającego wybór **wielowątkowości** i **bufora cyklicznego** jako kluczowych rozwiązań wydajnościowych.
