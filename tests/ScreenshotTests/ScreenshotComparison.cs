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

        [DllImport("user32.dll")]
        static extern int SetForegroundWindow(IntPtr hwnd);

        [DllImport("kernel32.dll", ExactSpelling = true)]
        static extern IntPtr GetConsoleWindow();

        private Process? p;

        private string testName { get; set; }

        private int frames { get; set; }

        private string executablePath { get; set; }

        private string programArgs { get; set; }

        public ScreenshotComparison(string testName, string executuable, string programArgs)
        {
            this.testName = testName;
            this.frames = 1;
            this.executablePath = executuable;
            this.programArgs = programArgs;
        }

        public ScreenshotComparison(string testName, string executuable, string programArgs, int frameToCapture)
        {
            this.testName = testName;
            this.frames = frameToCapture;
            this.executablePath = executuable;
            this.programArgs = programArgs;
        }

        void ExecuteProgram()
        {
            p = new Process();
            p.StartInfo.FileName = executablePath;
            p.StartInfo.Arguments = programArgs;
            p.StartInfo.WorkingDirectory = @"../../../../../bin/build/Test/";
            p.StartInfo.UseShellExecute = false;
            p.StartInfo.RedirectStandardOutput = false;
            p.Start();
            Thread.Sleep(3000);
        }

        Bitmap? PrintThisWindow(IntPtr hwnd)
        {
            if (!OperatingSystem.IsWindows())
                return null;

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

        void CaptureScreenshotAndSave(string location)
        {
            if (!OperatingSystem.IsWindows())
            {
                Console.WriteLine("Your platform is not supported for this test suite! Only windows is supported.");
                return;
            }

            Bitmap? image = PrintThisWindow(p.MainWindowHandle);

            if (!Directory.Exists("./actual")) Directory.CreateDirectory("./actual");
            image?.Save("./actual/" + location + ".jpg");
        }

        public bool ScreenshotsAreEqual()
        {
            ExecuteProgram();

            bool allTestCasesPass = true;

            for (int i = 1; i <= frames; i++)
            {
                string testCase = testName + "_" + i;
                string expectedPath = "./expected/" + testCase + ".jpg";
                string actualPath = "./actual/" + testCase + ".jpg";

                CaptureScreenshotAndSave(testCase);

                bool ImagesAreEqual = false;

                if (!File.Exists(expectedPath))
                {
                    Console.WriteLine("Test case: {0}. Does not have an expected image. Please verify image then retry.", testName);
                    allTestCasesPass = false;
                }
                else
                {
                    ICompareResult result = ImageSharpCompare.CalcDiff(expectedPath, actualPath);

                    Console.WriteLine("Test case: {0}", testName);
                    Console.WriteLine("Pixel error count {0}", result.PixelErrorCount);
                    Console.WriteLine("Absolute count {0}", result.AbsoluteError);
                    Console.WriteLine("Mean error {0}", result.MeanError);

                    ImagesAreEqual = ImageSharpCompare.ImagesAreEqual(expectedPath, actualPath);
                }

                if (frames == 1) // only testing one frame
                {
                    allTestCasesPass = ImagesAreEqual;
                    break;
                }
                else
                {
                    if (!ImagesAreEqual)
                    {
                        Console.WriteLine("Test case: {0}. Does not match expected frame.", testName);
                        allTestCasesPass = false;
                    }

                    if (i < frames)
                    {
                        // perform next frame

                        IntPtr hWndThis = GetConsoleWindow();
                        IntPtr hWndRenderer = Process.GetProcessesByName("Renderer2D")[0].MainWindowHandle;

                        if (hWndRenderer == IntPtr.Zero)
                            return false;

                        SetForegroundWindow(hWndThis);
                        Thread.Sleep(500);
                        // Tell the application to update to the next frame
                        SetForegroundWindow(hWndRenderer);
                        Thread.Sleep(3000);
                    }
                }
            }
            p?.CloseMainWindow();

            return allTestCasesPass;
        }
    }
}
