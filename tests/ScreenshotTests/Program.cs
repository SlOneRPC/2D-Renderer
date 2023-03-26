using System.Diagnostics;
using System;
using System.Runtime.InteropServices;
using System.Drawing.Imaging;
using ScreenshotTests;
using System.Drawing;
using Codeuctivity.ImageSharpCompare;

string TestDirectory = "../../../../../bin/build/Test/";
string renderer = TestDirectory + "Renderer2D.exe";

Test.AssertTrue(new ScreenshotComparison("Default Scene", 
    renderer, 
    "default.scene").ScreenshotsAreEqual());
Test.AssertTrue(new ScreenshotComparison("Zoomed Out Scene", 
    renderer, 
    "zoom.scene").ScreenshotsAreEqual());
Test.AssertTrue(new ScreenshotComparison("Quad scene",
    renderer,
    "square.scene").ScreenshotsAreEqual());


Test.CheckIfAllPassed();