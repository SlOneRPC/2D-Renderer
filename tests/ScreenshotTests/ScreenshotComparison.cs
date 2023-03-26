using System.Diagnostics;
using System;
using System.Runtime.InteropServices;
using System.Drawing.Imaging;
using ScreenshotTests;
using System.Drawing;
using Codeuctivity.ImageSharpCompare;

namespace ScreenshotTests
{
    public class ScreenshotComparison
    {
        [DllImport("user32.dll")]
        static extern bool GetWindowRect(IntPtr hWnd, out RECT lpRect);
        
        [DllImport("user32.dll")]
        static extern bool PrintWindow(IntPtr hWnd, IntPtr hdcBlt, int nFlags);

        private Process p;

        private string testName;

        public ScreenshotComparison(string testName, string executuable, string programArgs)
        {
            this.testName = testName;
            
            p = new Process();
            p.StartInfo.FileName = executuable;
            p.StartInfo.Arguments = programArgs;
            p.StartInfo.WorkingDirectory = @"../../../../../bin/build/Test/";
            p.StartInfo.UseShellExecute = false;
            p.StartInfo.RedirectStandardOutput = false;
            p.Start();

            Thread.Sleep(3000);

            Bitmap image = PrintThisWindow(p.MainWindowHandle);

            if (!Directory.Exists("./actual")) Directory.CreateDirectory("./actual");
            image.Save("./actual/" + testName + ".jpg");
        }

        Bitmap PrintThisWindow(IntPtr hwnd)
        {
            RECT rc;
            GetWindowRect(hwnd, out rc);

            Bitmap bmp = new Bitmap(rc.Right - rc.Left + 1, rc.Bottom - rc.Top + 1, PixelFormat.Format32bppArgb);
            Graphics gfxBmp = Graphics.FromImage(bmp);
            IntPtr hdcBitmap = gfxBmp.GetHdc();

            PrintWindow(hwnd, hdcBitmap, 0);

            gfxBmp.ReleaseHdc(hdcBitmap);
            gfxBmp.Dispose();

            return bmp;
        }

        public bool ScreenshotsAreEqual()
        {
            if (!File.Exists("./expected/" + testName + ".jpg")) return false;

            ICompareResult result = ImageSharpCompare.CalcDiff("test.jpg", "new.jpg");

            Console.WriteLine("Test case: {0}", testName);
            Console.WriteLine("Pixel error count {0}", result.PixelErrorCount);
            Console.WriteLine("Absolute count {0}", result.AbsoluteError);
            Console.WriteLine("Mean error {0}", result.MeanError);

            p.CloseMainWindow();
            return ImageSharpCompare.ImagesAreEqual("./expected/" + testName + ".jpg", "./actual/" + testName + ".jpg");
        }
    }
}
