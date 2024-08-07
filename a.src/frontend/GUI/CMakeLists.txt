cmake_minimum_required(VERSION 3.16)

project(GomokuGui VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Multimedia)
find_package(GTest REQUIRED) #for gtest_prod.h
find_package(Protobuf CONFIG REQUIRED)

qt_standard_project_setup()

add_subdirectory(../../backend/core ${CMAKE_BINARY_DIR}/backend_build)
get_target_property(gomokuAlgo_SRC_PATH gomokuAlgo SOURCE_DIR)
get_target_property(gomokuAlgo_INCLUDE_DIR gomokuAlgo INTERFACE_INCLUDE_DIRECTORIES)

#generate C++ protobufs .h/.cpp
add_custom_command(
        OUTPUT ${CMAKE_SOURCE_DIR}/protobuf/messages.pb.h ${CMAKE_SOURCE_DIR}/protobuf/messages.pb.cc
        COMMAND protoc -I=${CMAKE_SOURCE_DIR}/protobuf --cpp_out=${CMAKE_SOURCE_DIR}/protobuf ${CMAKE_SOURCE_DIR}/protobuf/messages.proto
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/protobuf
)

qt_add_executable(GomokuFree
    main.cpp
    GomokuGameClientGUI.cpp
    GomokuGameClientGUI.h
    GomokuGameServerGUI.cpp
    GomokuGameServerGUI.h
    protobuf/messages.pb.h
    protobuf/messages.pb.cc
)

qt_add_qml_module(GomokuFree
   URI GomokuGui
   VERSION 1.0
   QML_FILES Main.qml
   QML_FILES TopBar.qml
   QML_FILES Score.qml
   QML_FILES GoButton.qml
   QML_FILES Notification.qml
   QML_FILES Cell.qml
   QML_FILES GomokuBoard.qml

   #sound
   RESOURCES Sound/newGame.wav
   RESOURCES Sound/youWon.wav
   RESOURCES Sound/yourMove.wav
   RESOURCES Sound/youLost.wav
   RESOURCES Sound/pcMove.wav

   #images
   RESOURCES Images/mainBackGroundBlack.jpg
   RESOURCES Images/black50.gif
   RESOURCES Images/white50.gif
   RESOURCES Images/red50.gif
   RESOURCES Images/black50Redmark.gif
   RESOURCES Images/white50RedMark.gif
   RESOURCES Images/markedFields/excited.gif
   RESOURCES Images/menu/icons8-time-machine-filled-100.png
   RESOURCES Images/menu/icons8-time-machine-100.png
   RESOURCES Images/menu/icons8-info-filled-100.png
   RESOURCES Images/menu/icons8-info-100.png
   RESOURCES Images/menu/icons8-help-filled-100.png
   RESOURCES Images/menu/icons8-help-100.png
   RESOURCES Images/menu/icons8-go-back-filled-100.png
   RESOURCES Images/menu/icons8-go-back-100.png
   RESOURCES Images/menu/icons8-cancel-filled-100.png
   RESOURCES Images/menu/icons8-cancel-100.png
   RESOURCES Images/menu/icons8-time-machine-filled-100_disabled.png
   RESOURCES Images/menu/icons8-go-back-filled-100_disabled.png
   RESOURCES Images/menu/icons8-cancel-filled-100_disabled.png
   RESOURCES Images/boardBorder/border_bottom_01.gif
   RESOURCES Images/boardBorder/border_bottom_02.gif
   RESOURCES Images/boardBorder/border_bottom_03.gif
   RESOURCES Images/boardBorder/border_bottom_04.gif
   RESOURCES Images/boardBorder/border_bottom_05.gif
   RESOURCES Images/boardBorder/border_bottom_06.gif
   RESOURCES Images/boardBorder/border_bottom_07.gif
   RESOURCES Images/boardBorder/border_bottom_08.gif
   RESOURCES Images/boardBorder/border_bottom_09.gif
   RESOURCES Images/boardBorder/border_bottom_10.gif
   RESOURCES Images/boardBorder/border_bottom_11.gif
   RESOURCES Images/boardBorder/border_bottom_12.gif
   RESOURCES Images/boardBorder/border_bottom_13.gif
   RESOURCES Images/boardBorder/border_bottom_14.gif
   RESOURCES Images/boardBorder/border_bottom_15.gif
   RESOURCES Images/boardBorder/border_bottom_16.gif
   RESOURCES Images/boardBorder/border_bottom_17.gif
   RESOURCES Images/boardBorder/border_bottom_18.gif
   RESOURCES Images/boardBorder/border_bottom_19.gif
   RESOURCES Images/boardBorder/border_left_01.gif
   RESOURCES Images/boardBorder/border_left_02.gif
   RESOURCES Images/boardBorder/border_left_03.gif
   RESOURCES Images/boardBorder/border_left_04.gif
   RESOURCES Images/boardBorder/border_left_05.gif
   RESOURCES Images/boardBorder/border_left_06.gif
   RESOURCES Images/boardBorder/border_left_07.gif
   RESOURCES Images/boardBorder/border_left_08.gif
   RESOURCES Images/boardBorder/border_left_09.gif
   RESOURCES Images/boardBorder/border_left_10.gif
   RESOURCES Images/boardBorder/border_left_11.gif
   RESOURCES Images/boardBorder/border_left_12.gif
   RESOURCES Images/boardBorder/border_left_13.gif
   RESOURCES Images/boardBorder/border_left_14.gif
   RESOURCES Images/boardBorder/border_left_15.gif
   RESOURCES Images/boardBorder/border_left_16.gif
   RESOURCES Images/boardBorder/border_left_17.gif
   RESOURCES Images/boardBorder/border_left_18.gif
   RESOURCES Images/boardBorder/border_left_19.gif
   RESOURCES Images/boardBorder/border_right_01.gif
   RESOURCES Images/boardBorder/border_right_02.gif
   RESOURCES Images/boardBorder/border_right_03.gif
   RESOURCES Images/boardBorder/border_right_04.gif
   RESOURCES Images/boardBorder/border_right_05.gif
   RESOURCES Images/boardBorder/border_right_06.gif
   RESOURCES Images/boardBorder/border_right_07.gif
   RESOURCES Images/boardBorder/border_right_08.gif
   RESOURCES Images/boardBorder/border_right_09.gif
   RESOURCES Images/boardBorder/border_right_10.gif
   RESOURCES Images/boardBorder/border_right_11.gif
   RESOURCES Images/boardBorder/border_right_12.gif
   RESOURCES Images/boardBorder/border_right_13.gif
   RESOURCES Images/boardBorder/border_right_14.gif
   RESOURCES Images/boardBorder/border_right_15.gif
   RESOURCES Images/boardBorder/border_right_16.gif
   RESOURCES Images/boardBorder/border_right_17.gif
   RESOURCES Images/boardBorder/border_right_18.gif
   RESOURCES Images/boardBorder/border_right_19.gif
   RESOURCES Images/boardBorder/border_top_01.gif
   RESOURCES Images/boardBorder/border_top_02.gif
   RESOURCES Images/boardBorder/border_top_03.gif
   RESOURCES Images/boardBorder/border_top_04.gif
   RESOURCES Images/boardBorder/border_top_05.gif
   RESOURCES Images/boardBorder/border_top_06.gif
   RESOURCES Images/boardBorder/border_top_07.gif
   RESOURCES Images/boardBorder/border_top_08.gif
   RESOURCES Images/boardBorder/border_top_09.gif
   RESOURCES Images/boardBorder/border_top_10.gif
   RESOURCES Images/boardBorder/border_top_11.gif
   RESOURCES Images/boardBorder/border_top_12.gif
   RESOURCES Images/boardBorder/border_top_13.gif
   RESOURCES Images/boardBorder/border_top_14.gif
   RESOURCES Images/boardBorder/border_top_15.gif
   RESOURCES Images/boardBorder/border_top_16.gif
   RESOURCES Images/boardBorder/border_top_17.gif
   RESOURCES Images/boardBorder/border_top_18.gif
   RESOURCES Images/boardBorder/border_top_19.gif
   RESOURCES Images/boardBorder/corner_bottom_left.gif
   RESOURCES Images/boardBorder/corner_bottom_right.gif
   RESOURCES Images/boardBorder/corner_top_left.gif
   RESOURCES Images/boardBorder/corner_top_right.gif
   RESOURCES Images/boardInterior/interior_01.gif
   RESOURCES Images/boardInterior/interior_02.gif
   RESOURCES Images/boardInterior/interior_03.gif
   RESOURCES Images/boardInterior/interior_04.gif
   RESOURCES Images/boardInterior/interior_05.gif
   RESOURCES Images/boardInterior/interior_06.gif
   RESOURCES Images/boardInterior/interior_07.gif
   RESOURCES Images/boardInterior/interior_08.gif
   RESOURCES Images/boardInterior/interior_09.gif
   RESOURCES Images/boardInterior/interior_10.gif
   RESOURCES Images/boardInterior/interior_11.gif
   RESOURCES Images/boardInterior/interior_12.gif
   RESOURCES Images/boardInterior/interior_13.gif
   RESOURCES Images/boardInterior/interior_14.gif
   RESOURCES Images/boardInterior/interior_15.gif
   RESOURCES Images/boardInterior/interior_16.gif
   RESOURCES Images/boardInterior/interior_17.gif
   RESOURCES Images/boardInterior/interior_18.gif
   RESOURCES Images/boardInterior/interior_19.gif
   RESOURCES Images/boardInterior/interior_20.gif
   RESOURCES Images/boardInterior/interior_21.gif
   RESOURCES Images/boardInterior/interior_22.gif
   RESOURCES Images/boardInterior/interior_23.gif
   RESOURCES Images/boardInterior/interior_24.gif
   RESOURCES Images/boardInterior/interior_25.gif
   RESOURCES Images/boardInterior/interior_26.gif
   RESOURCES Images/boardInterior/interior_27.gif
   RESOURCES Images/boardInterior/interior_28.gif
   RESOURCES Images/boardInterior/interior_29.gif
   RESOURCES Images/boardInterior/interior_30.gif
   RESOURCES Images/boardInterior/interior_31.gif
   RESOURCES Images/boardInterior/interior_32.gif
   RESOURCES Images/boardInterior/interior_33.gif
   RESOURCES Images/boardInterior/interior_34.gif
   RESOURCES Images/boardInterior/interior_35.gif
   RESOURCES Images/boardInterior/interior_36.gif
   RESOURCES Images/boardInterior/interior_37.gif
   RESOURCES Images/boardInterior/interior_38.gif
   RESOURCES Images/boardInterior/interior_39.gif
   RESOURCES Images/boardInterior/interior_40.gif
   RESOURCES Images/boardInterior/interior_41.gif
   RESOURCES Images/boardInterior/interior_42.gif
   RESOURCES Images/boardInterior/interior_43.gif
   RESOURCES Images/boardInterior/interior_44.gif
   RESOURCES Images/boardInterior/interior_45.gif
   RESOURCES Images/boardInterior/interior_46.gif
   RESOURCES Images/boardInterior/interior_47.gif
   RESOURCES Images/boardInterior/interior_48.gif
   RESOURCES Images/boardInterior/interior_49.gif
   RESOURCES Images/boardInterior/interior_50.gif
   RESOURCES Images/boardInterior/interior_51.gif
   RESOURCES Images/boardInterior/interior_52.gif
   RESOURCES Images/boardInterior/interior_53.gif
   RESOURCES Images/boardInterior/interior_54.gif
   RESOURCES Images/boardInterior/interior_55.gif
   RESOURCES Images/boardInterior/interior_56.gif
   RESOURCES Images/boardInterior/interior_57.gif
   RESOURCES Images/boardInterior/interior_58.gif
   RESOURCES Images/boardInterior/interior_59.gif
   RESOURCES Images/boardInterior/interior_60.gif
   RESOURCES Images/boardInterior/interior_61.gif
   RESOURCES Images/boardInterior/interior_62.gif
   RESOURCES Images/boardInterior/interior_63.gif
   RESOURCES Images/boardInterior/interior_64.gif
   RESOURCES Images/boardInterior/interior_65.gif
   RESOURCES Images/boardInterior/interior_66.gif
   RESOURCES Images/boardInterior/interior_67.gif
   RESOURCES Images/boardInterior/interior_68.gif
   RESOURCES Images/boardInterior/interior_69.gif
   RESOURCES Images/boardInterior/interior_70.gif
   RESOURCES Images/boardInterior/interior_71.gif
   RESOURCES Images/boardInterior/interior_72.gif
   RESOURCES Images/boardInterior/interior_73.gif
   RESOURCES Images/boardInterior/interior_74.gif
   RESOURCES Images/boardInterior/interior_75.gif
   RESOURCES Images/boardInterior/interior_76.gif
   RESOURCES Images/boardInterior/interior_77.gif
   RESOURCES Images/boardInterior/interior_78.gif
   RESOURCES Images/boardInterior/interior_79.gif
   RESOURCES Images/boardInterior/interior_80.gif
   RESOURCES Images/boardInterior/interior_81.gif
   RESOURCES Images/boardInterior/interior_82.gif
   RESOURCES Images/boardInterior/interior_83.gif
   RESOURCES Images/boardInterior/interior_84.gif
   RESOURCES Images/boardInterior/interior_85.gif
   RESOURCES Images/boardInterior/interior_86.gif
   RESOURCES Images/boardInterior/interior_87.gif
   RESOURCES Images/boardInterior/interior_88.gif
   RESOURCES Images/boardInterior/interior_89.gif
   RESOURCES Images/boardInterior/interior_90.gif
   RESOURCES Images/boardInterior/interior_91.gif
   RESOURCES Images/boardInterior/interior_92.gif
   RESOURCES Images/boardInterior/interior_93.gif
   RESOURCES Images/boardInterior/interior_94.gif
   RESOURCES Images/boardInterior/interior_95.gif
   RESOURCES Images/boardInterior/interior_96.gif
   RESOURCES Images/boardInterior/interior_97.gif
   RESOURCES Images/boardInterior/interior_98.gif
   RESOURCES Images/boardInterior/interior_99.gif
   RESOURCES Images/boardInterior/interior_100.gif
   RESOURCES Images/boardInterior/interior_101.gif
   RESOURCES Images/boardInterior/interior_102.gif
   RESOURCES Images/boardInterior/interior_103.gif
   RESOURCES Images/boardInterior/interior_104.gif
   RESOURCES Images/boardInterior/interior_105.gif
   RESOURCES Images/boardInterior/interior_106.gif
   RESOURCES Images/boardInterior/interior_107.gif
   RESOURCES Images/boardInterior/interior_108.gif
   RESOURCES Images/boardInterior/interior_109.gif
   RESOURCES Images/boardInterior/interior_110.gif
   RESOURCES Images/boardInterior/interior_111.gif
   RESOURCES Images/boardInterior/interior_112.gif
   RESOURCES Images/boardInterior/interior_113.gif
   RESOURCES Images/boardInterior/interior_114.gif
   RESOURCES Images/boardInterior/interior_115.gif
   RESOURCES Images/boardInterior/interior_116.gif
   RESOURCES Images/boardInterior/interior_117.gif
   RESOURCES Images/boardInterior/interior_118.gif
   RESOURCES Images/boardInterior/interior_119.gif
   RESOURCES Images/boardInterior/interior_120.gif
   RESOURCES Images/boardInterior/interior_121.gif
   RESOURCES Images/boardInterior/interior_122.gif
   RESOURCES Images/boardInterior/interior_123.gif
   RESOURCES Images/boardInterior/interior_124.gif
   RESOURCES Images/boardInterior/interior_125.gif
   RESOURCES Images/boardInterior/interior_126.gif
   RESOURCES Images/boardInterior/interior_127.gif
   RESOURCES Images/boardInterior/interior_128.gif
   RESOURCES Images/boardInterior/interior_129.gif
   RESOURCES Images/boardInterior/interior_130.gif
   RESOURCES Images/boardInterior/interior_131.gif
   RESOURCES Images/boardInterior/interior_132.gif
   RESOURCES Images/boardInterior/interior_133.gif
   RESOURCES Images/boardInterior/interior_134.gif
   RESOURCES Images/boardInterior/interior_135.gif
   RESOURCES Images/boardInterior/interior_136.gif
   RESOURCES Images/boardInterior/interior_137.gif
   RESOURCES Images/boardInterior/interior_138.gif
   RESOURCES Images/boardInterior/interior_139.gif
   RESOURCES Images/boardInterior/interior_140.gif
   RESOURCES Images/boardInterior/interior_141.gif
   RESOURCES Images/boardInterior/interior_142.gif
   RESOURCES Images/boardInterior/interior_143.gif
   RESOURCES Images/boardInterior/interior_144.gif
   RESOURCES Images/boardInterior/interior_145.gif
   RESOURCES Images/boardInterior/interior_146.gif
   RESOURCES Images/boardInterior/interior_147.gif
   RESOURCES Images/boardInterior/interior_148.gif
   RESOURCES Images/boardInterior/interior_149.gif
   RESOURCES Images/boardInterior/interior_150.gif
   RESOURCES Images/boardInterior/interior_151.gif
   RESOURCES Images/boardInterior/interior_152.gif
   RESOURCES Images/boardInterior/interior_153.gif
   RESOURCES Images/boardInterior/interior_154.gif
   RESOURCES Images/boardInterior/interior_155.gif
   RESOURCES Images/boardInterior/interior_156.gif
   RESOURCES Images/boardInterior/interior_157.gif
   RESOURCES Images/boardInterior/interior_158.gif
   RESOURCES Images/boardInterior/interior_159.gif
   RESOURCES Images/boardInterior/interior_160.gif
   RESOURCES Images/boardInterior/interior_161.gif
   RESOURCES Images/boardInterior/interior_162.gif
   RESOURCES Images/boardInterior/interior_163.gif
   RESOURCES Images/boardInterior/interior_164.gif
   RESOURCES Images/boardInterior/interior_165.gif
   RESOURCES Images/boardInterior/interior_166.gif
   RESOURCES Images/boardInterior/interior_167.gif
   RESOURCES Images/boardInterior/interior_168.gif
   RESOURCES Images/boardInterior/interior_169.gif
   RESOURCES Images/boardInterior/interior_170.gif
   RESOURCES Images/boardInterior/interior_171.gif
   RESOURCES Images/boardInterior/interior_172.gif
   RESOURCES Images/boardInterior/interior_173.gif
   RESOURCES Images/boardInterior/interior_174.gif
   RESOURCES Images/boardInterior/interior_175.gif
   RESOURCES Images/boardInterior/interior_176.gif
   RESOURCES Images/boardInterior/interior_177.gif
   RESOURCES Images/boardInterior/interior_178.gif
   RESOURCES Images/boardInterior/interior_179.gif
   RESOURCES Images/boardInterior/interior_180.gif
   RESOURCES Images/boardInterior/interior_181.gif
   RESOURCES Images/boardInterior/interior_182.gif
   RESOURCES Images/boardInterior/interior_183.gif
   RESOURCES Images/boardInterior/interior_184.gif
   RESOURCES Images/boardInterior/interior_185.gif
   RESOURCES Images/boardInterior/interior_186.gif
   RESOURCES Images/boardInterior/interior_187.gif
   RESOURCES Images/boardInterior/interior_188.gif
   RESOURCES Images/boardInterior/interior_189.gif
   RESOURCES Images/boardInterior/interior_190.gif
   RESOURCES Images/boardInterior/interior_191.gif
   RESOURCES Images/boardInterior/interior_192.gif
   RESOURCES Images/boardInterior/interior_193.gif
   RESOURCES Images/boardInterior/interior_194.gif
   RESOURCES Images/boardInterior/interior_195.gif
   RESOURCES Images/boardInterior/interior_196.gif
   RESOURCES Images/boardInterior/interior_197.gif
   RESOURCES Images/boardInterior/interior_198.gif
   RESOURCES Images/boardInterior/interior_199.gif
   RESOURCES Images/boardInterior/interior_200.gif
   RESOURCES Images/boardInterior/interior_201.gif
   RESOURCES Images/boardInterior/interior_202.gif
   RESOURCES Images/boardInterior/interior_203.gif
   RESOURCES Images/boardInterior/interior_204.gif
   RESOURCES Images/boardInterior/interior_205.gif
   RESOURCES Images/boardInterior/interior_206.gif
   RESOURCES Images/boardInterior/interior_207.gif
   RESOURCES Images/boardInterior/interior_208.gif
   RESOURCES Images/boardInterior/interior_209.gif
   RESOURCES Images/boardInterior/interior_210.gif
   RESOURCES Images/boardInterior/interior_211.gif
   RESOURCES Images/boardInterior/interior_212.gif
   RESOURCES Images/boardInterior/interior_213.gif
   RESOURCES Images/boardInterior/interior_214.gif
   RESOURCES Images/boardInterior/interior_215.gif
   RESOURCES Images/boardInterior/interior_216.gif
   RESOURCES Images/boardInterior/interior_217.gif
   RESOURCES Images/boardInterior/interior_218.gif
   RESOURCES Images/boardInterior/interior_219.gif
   RESOURCES Images/boardInterior/interior_220.gif
   RESOURCES Images/boardInterior/interior_221.gif
   RESOURCES Images/boardInterior/interior_222.gif
   RESOURCES Images/boardInterior/interior_223.gif
   RESOURCES Images/boardInterior/interior_224.gif
   RESOURCES Images/boardInterior/interior_225.gif
   RESOURCES Images/boardInterior/interior_226.gif
   RESOURCES Images/boardInterior/interior_227.gif
   RESOURCES Images/boardInterior/interior_228.gif
   RESOURCES Images/boardInterior/interior_229.gif
   RESOURCES Images/boardInterior/interior_230.gif
   RESOURCES Images/boardInterior/interior_231.gif
   RESOURCES Images/boardInterior/interior_232.gif
   RESOURCES Images/boardInterior/interior_233.gif
   RESOURCES Images/boardInterior/interior_234.gif
   RESOURCES Images/boardInterior/interior_235.gif
   RESOURCES Images/boardInterior/interior_236.gif
   RESOURCES Images/boardInterior/interior_237.gif
   RESOURCES Images/boardInterior/interior_238.gif
   RESOURCES Images/boardInterior/interior_239.gif
   RESOURCES Images/boardInterior/interior_240.gif
   RESOURCES Images/boardInterior/interior_241.gif
   RESOURCES Images/boardInterior/interior_242.gif
   RESOURCES Images/boardInterior/interior_243.gif
   RESOURCES Images/boardInterior/interior_244.gif
   RESOURCES Images/boardInterior/interior_245.gif
   RESOURCES Images/boardInterior/interior_246.gif
   RESOURCES Images/boardInterior/interior_247.gif
   RESOURCES Images/boardInterior/interior_248.gif
   RESOURCES Images/boardInterior/interior_249.gif
   RESOURCES Images/boardInterior/interior_250.gif
   RESOURCES Images/boardInterior/interior_251.gif
   RESOURCES Images/boardInterior/interior_252.gif
   RESOURCES Images/boardInterior/interior_253.gif
   RESOURCES Images/boardInterior/interior_254.gif
   RESOURCES Images/boardInterior/interior_255.gif
   RESOURCES Images/boardInterior/interior_256.gif
   RESOURCES Images/boardInterior/interior_257.gif
   RESOURCES Images/boardInterior/interior_258.gif
   RESOURCES Images/boardInterior/interior_259.gif
   RESOURCES Images/boardInterior/interior_260.gif
   RESOURCES Images/boardInterior/interior_261.gif
   RESOURCES Images/boardInterior/interior_262.gif
   RESOURCES Images/boardInterior/interior_263.gif
   RESOURCES Images/boardInterior/interior_264.gif
   RESOURCES Images/boardInterior/interior_265.gif
   RESOURCES Images/boardInterior/interior_266.gif
   RESOURCES Images/boardInterior/interior_267.gif
   RESOURCES Images/boardInterior/interior_268.gif
   RESOURCES Images/boardInterior/interior_269.gif
   RESOURCES Images/boardInterior/interior_270.gif
   RESOURCES Images/boardInterior/interior_271.gif
   RESOURCES Images/boardInterior/interior_272.gif
   RESOURCES Images/boardInterior/interior_273.gif
   RESOURCES Images/boardInterior/interior_274.gif
   RESOURCES Images/boardInterior/interior_275.gif
   RESOURCES Images/boardInterior/interior_276.gif
   RESOURCES Images/boardInterior/interior_277.gif
   RESOURCES Images/boardInterior/interior_278.gif
   RESOURCES Images/boardInterior/interior_279.gif
   RESOURCES Images/boardInterior/interior_280.gif
   RESOURCES Images/boardInterior/interior_281.gif
   RESOURCES Images/boardInterior/interior_282.gif
   RESOURCES Images/boardInterior/interior_283.gif
   RESOURCES Images/boardInterior/interior_284.gif
   RESOURCES Images/boardInterior/interior_285.gif
   RESOURCES Images/boardInterior/interior_286.gif
   RESOURCES Images/boardInterior/interior_287.gif
   RESOURCES Images/boardInterior/interior_288.gif
   RESOURCES Images/boardInterior/interior_289.gif
   RESOURCES Images/boardInterior/interior_290.gif
   RESOURCES Images/boardInterior/interior_291.gif
   RESOURCES Images/boardInterior/interior_292.gif
   RESOURCES Images/boardInterior/interior_293.gif
   RESOURCES Images/boardInterior/interior_294.gif
   RESOURCES Images/boardInterior/interior_295.gif
   RESOURCES Images/boardInterior/interior_296.gif
   RESOURCES Images/boardInterior/interior_297.gif
   RESOURCES Images/boardInterior/interior_298.gif
   RESOURCES Images/boardInterior/interior_299.gif
   RESOURCES Images/boardInterior/interior_300.gif
   RESOURCES Images/boardInterior/interior_301.gif
   RESOURCES Images/boardInterior/interior_302.gif
   RESOURCES Images/boardInterior/interior_303.gif
   RESOURCES Images/boardInterior/interior_304.gif
   RESOURCES Images/boardInterior/interior_305.gif
   RESOURCES Images/boardInterior/interior_306.gif
   RESOURCES Images/boardInterior/interior_307.gif
   RESOURCES Images/boardInterior/interior_308.gif
   RESOURCES Images/boardInterior/interior_309.gif
   RESOURCES Images/boardInterior/interior_310.gif
   RESOURCES Images/boardInterior/interior_311.gif
   RESOURCES Images/boardInterior/interior_312.gif
   RESOURCES Images/boardInterior/interior_313.gif
   RESOURCES Images/boardInterior/interior_314.gif
   RESOURCES Images/boardInterior/interior_315.gif
   RESOURCES Images/boardInterior/interior_316.gif
   RESOURCES Images/boardInterior/interior_317.gif
   RESOURCES Images/boardInterior/interior_318.gif
   RESOURCES Images/boardInterior/interior_319.gif
   RESOURCES Images/boardInterior/interior_320.gif
   RESOURCES Images/boardInterior/interior_321.gif
   RESOURCES Images/boardInterior/interior_322.gif
   RESOURCES Images/boardInterior/interior_323.gif
   RESOURCES Images/boardInterior/interior_324.gif
   RESOURCES Images/boardInterior/interior_325.gif
   RESOURCES Images/boardInterior/interior_326.gif
   RESOURCES Images/boardInterior/interior_327.gif
   RESOURCES Images/boardInterior/interior_328.gif
   RESOURCES Images/boardInterior/interior_329.gif
   RESOURCES Images/boardInterior/interior_330.gif
   RESOURCES Images/boardInterior/interior_331.gif
   RESOURCES Images/boardInterior/interior_332.gif
   RESOURCES Images/boardInterior/interior_333.gif
   RESOURCES Images/boardInterior/interior_334.gif
   RESOURCES Images/boardInterior/interior_335.gif
   RESOURCES Images/boardInterior/interior_336.gif
   RESOURCES Images/boardInterior/interior_337.gif
   RESOURCES Images/boardInterior/interior_338.gif
   RESOURCES Images/boardInterior/interior_339.gif
   RESOURCES Images/boardInterior/interior_340.gif
   RESOURCES Images/boardInterior/interior_341.gif
   RESOURCES Images/boardInterior/interior_342.gif
   RESOURCES Images/boardInterior/interior_343.gif
   RESOURCES Images/boardInterior/interior_344.gif
   RESOURCES Images/boardInterior/interior_345.gif
   RESOURCES Images/boardInterior/interior_346.gif
   RESOURCES Images/boardInterior/interior_347.gif
   RESOURCES Images/boardInterior/interior_348.gif
   RESOURCES Images/boardInterior/interior_349.gif
   RESOURCES Images/boardInterior/interior_350.gif
   RESOURCES Images/boardInterior/interior_351.gif
   RESOURCES Images/boardInterior/interior_352.gif
   RESOURCES Images/boardInterior/interior_353.gif
   RESOURCES Images/boardInterior/interior_354.gif
   RESOURCES Images/boardInterior/interior_355.gif
   RESOURCES Images/boardInterior/interior_356.gif
   RESOURCES Images/boardInterior/interior_357.gif
   RESOURCES Images/boardInterior/interior_358.gif
   RESOURCES Images/boardInterior/interior_359.gif
   RESOURCES Images/boardInterior/interior_360.gif
   RESOURCES Images/boardInterior/interior_361.gif

)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
# set_target_properties(GomokuFree PROPERTIES
# #    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.GomokuFree
#    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#    MACOSX_BUNDLE TRUE
#    WIN32_EXECUTABLE TRUE
# )

set_target_properties(GomokuFree PROPERTIES
   QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android #set my predefined AndroidManifest.xml. You can comment it, so default will be generated.
)

target_link_libraries(GomokuFree
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Multimedia
    gomokuAlgo
    protobuf::libprotobuf
    GTest::gtest #for gtest_prod.h
)

include(GNUInstallDirs)
install(TARGETS GomokuFree
   BUNDLE DESTINATION .
   LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
   RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
