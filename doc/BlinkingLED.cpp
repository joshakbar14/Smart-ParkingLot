//BLINKING THE LED//
//TO TEST RASPBERRY PI//

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>

class LinuxFile
{
private:
    int m_Handle;

public:
    LinuxFile(const char *pFile, int flags = O_RDWR)
    {
        m_Handle = open(pFile, flags);
    }

    ~LinuxFile()
    {
        if (m_Handle != -1)
            close(m_Handle);
    }

    size_t Write(const void *pBuffer, size_t size)
    {
        return write(m_Handle, pBuffer, size);
    }

    size_t Read(void *pBuffer, size_t size)
    {
        return read(m_Handle, pBuffer, size);
    }

    size_t Write(const char *pText)
    {
        return Write(pText, strlen(pText));
    }

    size_t Write(int number)
    {
        char szNum[32];
        snprintf(szNum, sizeof(szNum), "%d", number);
        return Write(szNum);
    }
};

class LinuxGPIOExporter
{
protected:
    int m_Number;

public:
    LinuxGPIOExporter(int number)
            : m_Number(number)
    {
        LinuxFile("/sys/class/gpio/export", O_WRONLY).Write(number);
    }

    ~LinuxGPIOExporter()
    {
        LinuxFile("/sys/class/gpio/unexport", O_WRONLY).Write(m_Number);
    }
};

class LinuxGPIO : public LinuxGPIOExporter
{
public:
    LinuxGPIO(int number)
            : LinuxGPIOExporter(number)
    {
    }

    void SetValue(bool value)
    {
        char szFN[128];
        snprintf(szFN, sizeof(szFN), "/sys/class/gpio/gpio%d/value", m_Number);
        LinuxFile(szFN).Write(value ? "1" : "0");
    }

    void SetDirection(bool isOutput)
    {
        char szFN[128];
        snprintf(szFN, sizeof(szFN),
                 "/sys/class/gpio/gpio%d/direction", m_Number);
        LinuxFile(szFN).Write(isOutput ? "out" : "in");
    }
};

int main(int argc, char *argv[])
{
    LinuxGPIO gpio27(27);
    gpio27.SetDirection(true);
    bool on = true;
    for (;;)
    {
        printf("Switching %s the LED...\n", on ? "on" : "off");
        gpio27.SetValue(on);
        on = !on;
        sleep(1);
    }
}