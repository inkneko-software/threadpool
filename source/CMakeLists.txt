aux_source_directory(. inkneko_thread_pool_source)
add_library(inkneko_thread_pool SHARED ${inkneko_thread_pool_source})
target_link_libraries(inkneko_thread_pool pthread)

install(FILES ThreadPool.h
DESTINATION include/nekorpc/
)

install(TARGETS inkneko_thread_pool
LIBRARY DESTINATION lib
)