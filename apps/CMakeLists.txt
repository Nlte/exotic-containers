add_executable(app_main app_main.cpp)

# target_link_libraries(app_main PRIVATE containers Azure::azure-storage-blobs)
target_link_libraries(app_main PRIVATE containers)
