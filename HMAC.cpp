#include <iostream>
#include <sstream>

#include "SHA1.cpp"

int main()
{
    const int block_size = 64; // размер блока в хэш функции
    const char nullByte = 0x00; // нулевой байт
    const int hashLength = 20; // длина хэша

    string message = "Hello World!";
    string K = "Key";
    
    // расширяю ключ до block_size
    string K_0;
    // равно
    if (K.length() == block_size)
    {
        K_0 = K;
    }
    // больше
    else if (K.length() > block_size)
    {
        // беру хэш
        K_0 = myHash(K);
        // заполняю нулями
        while (K_0.length() != block_size)
        {
            K_0 += nullByte;
        }
    }
    // меньше
    else
    {
        K_0 = K;
        // заполняю нулями
        while (K_0.length() != block_size)
        {
            K_0 += nullByte;
        }
    }

    // магические числа из стандарта
    const char ipad = 0x36; // inner
    const char opad = 0x5c; // outer

    // блоки S_i и S_o
    string S_i = K_0, S_o = K_0;
    for (size_t i = 0; i < block_size; i++)
    {
        S_i[i] = S_i[i] ^ ipad;
        S_o[i] = S_o[i] ^ opad;
    }

    // дополняю сообщение до длины block_size
    while (message.length() % block_size != 0)
    {
        message += nullByte;
    }
    
    // разбиваю сообщение на блоки и склеиваю S_i с каждым блоком сообщения
    int blocksLength = message.length() / block_size;
    stringstream newMessage;
    for (size_t block_i = 0; block_i < blocksLength; block_i++)
    {
        newMessage << S_i;
        for (size_t symbol_i = 0; symbol_i < block_size; symbol_i++)
        {
            newMessage << message[block_i * block_size + symbol_i];
        }
    }
    
    cout << message << endl << myHash(S_o + myHash(newMessage.str())) << endl;

    system("pause");
    return 0;
}
