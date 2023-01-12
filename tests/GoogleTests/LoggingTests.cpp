#include "pch.h"
#include "Core/Logging.h"

#ifdef _DEBUG

TEST(LoggingTests, EnsureInfoCanBeLogged) {
	testing::internal::CaptureStdout();
	
	LOG_INFO("TEST");

	std::string output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(std::string("INFO:  TEST\n"), output);
}

TEST(LoggingTests, EnsureErrorCanBeLogged) {
	testing::internal::CaptureStdout();

	LOG_ERROR("TEST");

	std::string output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(std::string("ERROR:  TEST\n"), output);
}

TEST(LoggingTests, EnsureWarningCanBeLogged) {
	testing::internal::CaptureStdout();

	LOG_WARN("TEST");

	std::string output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(std::string("WARN:  TEST\n"), output);
}

#else

TEST(LoggingTests, EnsureLoggingIsDisabledInRelease) {
	testing::internal::CaptureStdout();

	LOG_INFO("TEST");

	std::string output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(std::string(""), output);
}

#endif