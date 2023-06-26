using System.Diagnostics;
using System;
using System.Runtime.InteropServices;
using System.Drawing.Imaging;
using ScreenshotTests;
using System.Drawing;
using Codeuctivity.ImageSharpCompare;
using System.IO;

string TestDirectory = "../../../../../bin/build/IntegrationTest/";
string renderer = TestDirectory + "Renderer2D.exe";

if (!File.Exists(renderer))
{
    Console.WriteLine("Application does not exist in -> " + renderer);
    return;
}

Test.AssertTrue(new ScreenshotComparison("Default Scene", 
    renderer, 
    "default.scene").ScreenshotsAreEqual());
Test.AssertTrue(new ScreenshotComparison("Zoomed Out Scene", 
    renderer, 
    "zoom.scene").ScreenshotsAreEqual());
Test.AssertTrue(new ScreenshotComparison("Quad scene",
    renderer,
    "square.scene").ScreenshotsAreEqual());
Test.AssertTrue(new ScreenshotComparison("Moving Entities",
    renderer,
    "movingEntity.scene",
    4).ScreenshotsAreEqual());
Test.AssertTrue(new ScreenshotComparison("Rotating Entity",
    renderer,
    "rotate.scene",
    4).ScreenshotsAreEqual());


Test.CheckIfAllPassed();