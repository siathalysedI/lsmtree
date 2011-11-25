#ifndef _PLATFORM_H
#define _PLATFORM_H

#ifndef O_BINARY
	#define O_BINARY (0) 
#endif

#if defined(__linux__)
	# define UINT long long unsigned int
	# define open_db open64
	# define lseek lseek
	# define fstat fstat
	# define fsync fdatasync
	# define LSM_CREAT_FLAGS  (O_RDWR | O_TRUNC | O_CREAT | O_BINARY | O_LARGEFILE)
	# define LSM_OPEN_FLAGS   (O_RDWR | O_BINARY | O_LARGEFILE)
#else
	# define open64 open
	# define LSM_CREAT_FLAGS  (O_RDWR | O_TRUNC | O_CREAT | O_BINARY)
	# define LSM_OPEN_FLAGS   (O_RDWR | O_BINARY)
#endif

#endif
