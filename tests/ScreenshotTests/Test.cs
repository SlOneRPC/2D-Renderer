using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ScreenshotTests
{
    public class Test
    {
        public static bool allPassed = true;

        public static void AssertTrue(bool result)
        {
            if (result)
            {
                Console.ForegroundColor = ConsoleColor.Green;
                Console.WriteLine("Images match");
            }
            else
            {
                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine("Images do not match!");
                allPassed = false;
            }

            Console.ForegroundColor = ConsoleColor.White;
        }

        public static void CheckIfAllPassed()
        {
            if (allPassed)
            {
                Console.ForegroundColor = ConsoleColor.Green;
                Console.WriteLine("\n===========================");
                Console.WriteLine("All tests passed!");
                Console.WriteLine("===========================");
            }
            else
            {
                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine("\n===========================");
                Console.WriteLine("Not all tests passed!");
                Console.WriteLine("===========================");
            }
            Console.ForegroundColor = ConsoleColor.White;
        }
    }
}
