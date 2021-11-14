using System;
using System.IO.Ports;


namespace Console_app_for_joystick_test
{
    class Program
    {
        static SerialPort port = new SerialPort("COM3",9600);
        static String data;
        static void Main(string[] args)
        {
                port.Open();

            while (true)
            {
                data = port.ReadLine();
                Console.WriteLine(data);
            }
        }
    }
}
