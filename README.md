*This project has been created as part of the 42 curriculum by sevyesil.*

# get_next_line

## Açıklama

`get_next_line`, 42 müfredatı kapsamında geliştirilen ve C dilinde satır satır dosya okuma işlemini gerçekleştiren bir fonksiyondur. Bu projenin temel amacı, dosya işlemleri, bellek yönetimi ve buffer kullanımı gibi konularda derinlemesine bilgi sahibi olmaktır.

Proje boyunca, dosya okuma işlemlerinin yönetimi, dinamik bellek tahsisi, buffer ile çalışma ve çoklu dosya tanımlayıcılarıyla (file descriptor) aynı anda çalışabilme yetkinliği kazanılması hedeflenmiştir.

**Projenin Hedefleri**

- Dosya işlemlerinde satır bazlı okuma mantığını kavramak,
- Bellek sızıntılarını önleyen güvenli kod yazma alışkanlığı edinmek,
- Çoklu dosya tanımlayıcıları ile eşzamanlı okuma işlemlerini yönetmek,
- Modüler ve yeniden kullanılabilir fonksiyonlar geliştirmek.

Ortaya çıkan `get_next_line` fonksiyonu, C projelerinde satır satır dosya okuma ihtiyacını karşılamak üzere tasarlanmıştır.

---

## Talimatlar

Projeyi derlemek için:

```bash
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c -D BUFFER_SIZE=42
```

Bonus kısmı için:

```bash
cc -Wall -Wextra -Werror get_next_line_bonus.c get_next_line_utils_bonus.c -D BUFFER_SIZE=42
```

---

## Kullanım

`get_next_line` fonksiyonunu kullanmak için, ilgili header dosyasını (`get_next_line.h` veya `get_next_line_bonus.h`) projenize dahil etmeniz yeterlidir.

Fonksiyon prototipi:

```c
char *get_next_line(int fd);
```

Kullanım örneği:

```c
#include "get_next_line.h"

int main(void)
{
    int fd = open("dosya.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

---

# Projedeki Tüm Fonksiyonlar ve Açıklamaları (Detaylı)

Aşağıda, get_next_line projesinde yer alan tüm fonksiyonlar, görevleri ve çalışma prensipleri detaylı şekilde açıklanmıştır. Fonksiyonlar hem ana hem de yardımcı dosyalarda yer alır ve satır satır dosya okuma işlemini güvenli ve verimli şekilde gerçekleştirmeni sağlar.

---

## Ana Fonksiyonlar

### 1. get_next_line(int fd)

- `char *get_next_line(int fd);`

- Verilen dosya tanımlayıcısından (fd) bir sonraki satırı okur ve döndürür. Satır sonuna (`\n`) kadar okuma yapar, dosya sonuna gelindiğinde veya hata oluştuğunda `NULL` döner.
- Her çağrıda bir sonraki satırı döndürür, dinamik bellek yönetimi ile çalışır.
- Okuma işlemi sırasında buffer kullanır ve buffer boyutu `BUFFER_SIZE` makrosu ile belirlenir.
- Fonksiyonun içinde, okunan veriler bir buffer'da tutulur ve satır sonu karakteri bulunana kadar okuma devam eder.
- Okunan satır, dinamik olarak ayrılan bir string olarak döndürülür ve kullanıcı tarafından `free` edilmelidir.

**Çalışma Adımları:**
1. `get_read_file`: Dosyadan satır sonuna kadar okuma yapar ve buffer'a ekler.
2. `get_line`: Buffer'dan bir satırı ayırır ve döndürür.
3. `get_stash_clear`: Buffer'da kalan kısmı saklar, bir sonraki çağrıda devam eder.

---

## Yardımcı Fonksiyonlar (get_next_line_utils.c)

### 2. ft_strlen(const char *s)
- Bir string’in uzunluğunu hesaplar. Stringin sonundaki `\0` karakterine kadar sayar ve uzunluğu döndürür.

### 3. ft_strjoin(const char *s1, const char *s2)
- İki string’i birleştirerek yeni bir string oluşturur. Sonuç olarak yeni bir bellek alanı ayırır ve birleştirilmiş stringi döndürür. Bellek yönetimi kullanıcıya aittir.

### 4. ft_strdup(const char *s)
- Verilen string’in dinamik bellekte bir kopyasını oluşturur. Kopyalanan string yeni bir bellek alanında tutulur ve kullanıcı tarafından `free` edilmelidir.

### 5. ft_substr(const char *s, unsigned int start, size_t len)
- Bir string’in belirli bir aralıktaki alt string’ini oluşturur. `start` indeksinden başlayarak `len` kadar karakteri yeni bir string olarak döndürür.

### 6. ft_strchr(const char *s, int c)
- Bir karakterin, string içinde ilk geçtiği yeri bulur ve işaretçi olarak döndürür. Eğer karakter bulunamazsa `NULL` döner.

---

## Statik (Yardımcı) Fonksiyonlar (get_next_line.c)

### 7. get_merge_and_free(char *buffer, char *temp_buffer)
- İki buffer'ı birleştirir ve eski buffer'ı serbest bırakır. Okunan yeni veriyi mevcut buffer'a ekler.

### 8. get_read_file(int fd, char *buffer)
- Dosyadan satır sonuna kadar okuma yapar. Okunan verileri buffer'a ekler. Satır sonu karakteri bulunana kadar okuma devam eder.

### 9. get_line(char *buffer)
- Buffer'dan bir satırı ayırır ve yeni bir string olarak döndürür. Satır sonu karakterine kadar olan kısmı alır.

### 10. get_stash_clear(char *buffer)
- Okunan satırdan sonra buffer'da kalan kısmı saklar. Bir sonraki çağrıda bu kısımdan devam edilir.

---

## Bonus Fonksiyonlar (get_next_line_bonus.c)

### 11. get_next_line_bonus(int fd)
- Aynı anda birden fazla dosya tanımlayıcısı ile çalışabilmek için her fd için ayrı bir buffer yönetimi yapar. Fonksiyonun mantığı ana fonksiyon ile aynıdır, ancak buffer dizisi ile çoklu dosya desteği sağlanır.

---

## Fonksiyonların Genel Görevleri

- **Bellek Yönetimi:** Tüm fonksiyonlar, bellek sızıntılarını önleyecek şekilde dinamik bellek tahsisi ve serbest bırakma işlemlerini dikkatli şekilde gerçekleştirir.
- **String İşlemleri:** Satır okuma, birleştirme, kopyalama ve arama işlemleri için güvenli yardımcı fonksiyonlar kullanılır.
- **Çoklu Dosya Desteği (Bonus):** Aynı anda birden fazla dosya tanımlayıcısı ile çalışabilmek için ek veri yapıları ve algoritmalar kullanılır.

---

## Proje Dosyaları

- **get_next_line.c**  
  Ana fonksiyonun ve okuma işlemlerinin bulunduğu dosya.

- **get_next_line.h**  
  Fonksiyon prototipleri ve gerekli makroların tanımlandığı header dosyası.

- **get_next_line_utils.c**  
  Yardımcı string ve bellek fonksiyonlarının bulunduğu dosya.

- **get_next_line_bonus.c**  
  Çoklu dosya tanımlayıcıları ile çalışmayı sağlayan bonus fonksiyonları.

- **get_next_line_bonus.h**  
  Bonus fonksiyonlar için header dosyası.

- **get_next_line_utils_bonus.c**  
  Bonus için yardımcı fonksiyonlar.

---

## Kaynaklar

- 42 get_next_line subject dokümanı  
- C Standard Library (man pages)  
- IBM C Library Documentation  
- GeeksforGeeks  
- Stack Overflow

---

## AI Kullanımı

Bu proje geliştirilirken yapay zekâ araçları, kavramsal anlamayı desteklemek ve konu tekrarları yapmak amacıyla kullanılmıştır. Fonksiyonların implementasyonu, hata ayıklama süreci ve kod yazımı tamamen sevyesil tarafından gerçekleştirilmiştir. Proje, 42 akademik dürüstlük kurallarına uygun olarak hazırlanmıştır.

---