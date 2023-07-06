set(
    CLI_SAMPLE_NAMES
	SampleHDR
	SampleLiveDepthCallback
	SampleLiveDepthManualQuery
	SampleLiveRgbCallback
	SampleLiveRgbManualQuery
	SamplePointReconstruction
	SampleSoftTrigger
	SampleMultiCamera
	SampleLiveDepthIRCallback
	SampleLiveRgbAutoExposure
	SampleSetAndGetUserData
	SampleSystemQueryCameras
)


foreach(
    SAMPLE_NAME
    ${CLI_SAMPLE_NAMES}
)
	include_directories(Utils)
	include_directories(.)
	add_executable(${SAMPLE_NAME} ${SAMPLE_NAME}/${SAMPLE_NAME}.cpp)

	target_link_libraries(${SAMPLE_NAME} optimized 3DCamera debug 3DCamerad)
	
	set_property(TARGET ${SAMPLE_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${RPATH}/../../../../bin)
	
	add_custom_command(TARGET ${SAMPLE_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${RPATH}/$<CONFIGURATION:${SAMPLE_NAME}>"
        $<TARGET_FILE_DIR:${SAMPLE_NAME}> >nul)

endforeach()

#add handeye 
set(
	CLI_SAMPLE_HANDEYE_NAMES
		SampleHandEye
		SampleHandEyeOffline
		SampleHandEyeReconstructPoints
)

foreach(
	SAMPLE_HANDEYE_NAME
	${CLI_SAMPLE_HANDEYE_NAMES}
)

add_executable(${SAMPLE_HANDEYE_NAME} ${SAMPLE_HANDEYE_NAME}/${SAMPLE_HANDEYE_NAME}.cpp)

target_link_libraries(${SAMPLE_HANDEYE_NAME} optimized 3DCamera debug 3DCamerad)
target_link_libraries(${SAMPLE_HANDEYE_NAME} optimized HandEye debug HandEyed)

add_custom_command(TARGET ${SAMPLE_HANDEYE_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/data" "$<TARGET_FILE_DIR:${SAMPLE_HANDEYE_NAME}>/data"
COMMAND ${CMAKE_COMMAND} -E copy_directory "${RPATH}/$<CONFIGURATION:${SAMPLE_NAME}>" $<TARGET_FILE_DIR:${SAMPLE_HANDEYE_NAME}> >nul
COMMAND ${CMAKE_COMMAND} -E copy_directory "${HANDEYE_LIB}/$<CONFIGURATION:${SAMPLE_NAME}>" $<TARGET_FILE_DIR:${SAMPLE_HANDEYE_NAME}> >nul
)


endforeach()
