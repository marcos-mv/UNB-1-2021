#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

int main(int argc, const char *argv[])
{

    int uart0_filestream = -1;

    uart0_filestream = open("/dev/serial0", O_RDWR | O_NOCTTY | O_NDELAY);

    if (uart0_filestream == -1)
    {
        printf("erro na abertura da UART\n");
    }

    struct termios options;
    tcgetattr(uart0_filestream, &options);

    options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;

    tcflush(uart0_filestream, TCIFLUSH);
    tcsetattr(uart0_filestream, TCSANOW, &options);

    unsigned char tx_buffer[10];

    unsigned char *p_tx_buffer;

    p_tx_buffer = &tx_buffer[0];

    *p_tx_buffer++ = 'O';
    *p_tx_buffer++ = 'l';
    *p_tx_buffer++ = 'a';
    *p_tx_buffer++ = ' ';
    *p_tx_buffer++ = 'M';
    *p_tx_buffer++ = 'u';
    *p_tx_buffer++ = 'n';
    *p_tx_buffer++ = 'd';
    *p_tx_buffer++ = 'o';

    int count = write(uart0_filestream, &tx_buffer[0], (p_tx_buffer - &tx_buffer[0]));
    printf("Escrevendo na UART ... \n");

    if (count < 0)
    {
        printf("Erro no envio de dados - TX\n");
    }

    sleep(1);

    unsigned rx_buffer[100];
    int rx_length = read(uart0_filestream, (void *)rx_buffer, 100);

    if (rx_length < 0)
    {
        printf("Erro na leitura da UART - RX\n");
    }
    else if (rx_length == 0)
    {
        printf("Nenhum dado disponível\n");
    }
    else
    {
        rx_buffer[rx_length] = '\0';
        printf("Mensagem de comprimento %d: %s\n", rx_length, rx_buffer);
    }

    close(uart0_filestream);

    return 0;
}