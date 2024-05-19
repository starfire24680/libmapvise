add_executable(test_anon test_anon.c)

IF ("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
	add_test(
	    NAME Test_test_anon_win
	    COMMAND sh -c "wine test_anon.exe"
	)
ELSE()
	add_test(
	    NAME Test_test_anon
	    COMMAND test_anon
	)
ENDIF()

add_executable(test_file test_file.c)
IF ("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
	add_test(
	    NAME Test_test_file_win
	    COMMAND sh -c "dd if=/dev/zero of=/tmp/test bs=1M count=8 && wine $PWD/test_file.exe && rm /tmp/test"
	)
ELSE()
	add_test(
	    NAME Test_test_file
	    COMMAND sh -c "dd if=/dev/zero of=/tmp/test bs=1M count=8 && $PWD/test_file && rm /tmp/test"
	)
ENDIF()

IF (HUGEFILE_TESTING)
	IF ("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
		add_test(
		    NAME Test_test_file_huge_win
		    COMMAND sh -c "dd if=/dev/zero of=/tmp/test bs=1M count=8192 && wine $PWD/test_file.exe && rm /tmp/test"
		)
	ELSE()
		add_test(
		    NAME Test_test_file_huge
		    COMMAND sh -c "dd if=/dev/zero of=/tmp/test bs=1M count=8192 && $PWD/test_file && rm /tmp/test"
		)
	ENDIF()
ENDIF()
