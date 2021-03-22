
find_package (Threads)

add_ov_library(opcuaSubscription)
ov_library_includes(opcuaSubscription ov fb opcua)
target_link_libraries(opcuaSubscription PRIVATE Threads::Threads)

