
find_package (Threads)
add_ov_library(openAASDiscoveryServer)
ov_library_includes(openAASDiscoveryServer ov fb MessageSys)
target_link_libraries(openAASDiscoveryServer Threads::Threads)
