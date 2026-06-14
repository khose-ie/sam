#ifndef _UPES_H_
#define _UPES_H_

/// @file upes.h
/// @brief UPES Common Definitions
/// @details This header file defines common types and return values used across the UPES
///          middleware and its components.
/// @author Khose-ie<khose-ie@outlook.com>
/// @date   2026-06-14

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/// @brief Standard return value enumeration
/// @details Represents standard return values for UPES functions
typedef enum
{
    //===============================
    // General logic errors 0-31
    //===============================
    RET_VALUE_OK             = 0, ///< Success
    RET_VALUE_PARAM_ERR      = 1, ///< Invalid parameter
    RET_VALUE_BUSY           = 2, ///< Resource busy
    RET_VALUE_TIMEOUT        = 3, ///< Timeout occurred
    RET_VALUE_STACK_OVERFLOW = 4, ///< Stack overflow
    RET_VALUE_PERMISSION     = 5, ///< Permission denied
    RET_VALUE_NULL_REF       = 6, ///< Null pointer reference

    RET_VALUE_NOT_SUPPORT   = 8, ///< Operation not supported
    RET_VALUE_NOT_AVAILABLE = 9, ///< Resource not available

    //===============================
    //  Basic operation errors 32-47
    //===============================
    RET_VALUE_MEM_ALLOC_FAILURE = 32, ///< Memory allocation failure
    RET_VALUE_FORMAT_FAILURE    = 33, ///< Format failure
    RET_VALUE_LOW_LEVEL_FAILURE = 34, ///< Low-level API failure

    //===============================
    //  Instance management errors 48-63
    //===============================
    RET_VALUE_INSTANCE_CREATE_FAILURE = 48, ///< Failed to create instance
    RET_VALUE_INSTANCE_NOT_FOUND      = 49, ///< Instance not found
    RET_VALUE_INSTANCE_DUPLICATE      = 50, ///< Instance already exists
    RET_VALUE_INSTANCE_IN_USE         = 51, ///< Instance is in use
    RET_VALUE_INSTANCE_UNAVAILABLE    = 52, ///< Instance unavailable

    //===============================
    //  MCU specific errors 64-79
    //===============================
    RET_VALUE_MCU_HW_FAILURE    = 64, ///< MCU hardware failure
    RET_VALUE_MCU_CLOCK_FAILURE = 65, ///< MCU clock or timing error
    RET_VALUE_MCU_RESET         = 66, ///< Unexpected MCU reset

    //===============================
    //  OS specific errors 80-95
    //===============================
    RET_VALUE_OS_KERNEL_ERR    = 80, ///< OS kernel operation failed
    RET_VALUE_OS_EVENT_ERR     = 81, ///< Task deletion failed
    RET_VALUE_OS_MEM_POOL_ERR  = 82, ///< Memory pool operation failed
    RET_VALUE_OS_MQ_ERR        = 83, ///< Message queue operation failed
    RET_VALUE_OS_MUTEX_ERR     = 84, ///< Mutex operation failed
    RET_VALUE_OS_SEMAPHORE_ERR = 85, ///< Semaphore operation failed
    RET_VALUE_OS_TASK_ERR      = 86, ///< Task deletion failed
    RET_VALUE_OS_TIMER_ERR     = 87, ///< Timer creation failed

    //===============================
    //  File system errors 96-111
    //===============================
    RET_VALUE_FS_MOUNT_FAILURE     = 96,  ///< File system mount failure
    RET_VALUE_FS_FORMAT_FAILURE    = 97,  ///< File system format failure
    RET_VALUE_FS_NOT_VALID_FS      = 98,  ///< No valid file system found
    RET_VALUE_FS_NOT_FILE          = 99,  ///< Not a file
    RET_VALUE_FS_NOT_DIR           = 100, ///< Not a directory
    RET_VALUE_FS_DIR_NOT_EMPTY     = 101, ///< File system unmount error
    RET_VALUE_FS_DISK_NOT_READY    = 102, ///< Disk not ready
    RET_VALUE_DISK_WRITE_PROTECTED = 103, ///< Disk write protected
    RET_VALUE_DISK_IO_ERR          = 104, ///< Low-level disk I/O error

    //===============================
    //  Network errors 112-127
    //===============================

    //===============================
    //  Peripheral extension errors 128-254
    //===============================

    //===============================
    //  Unknown error 255
    //===============================
    RET_VALUE_UNKNOWN = 255 ///< Unknown error
} RetValue_t;

/// @brief Function used to get count of aligned type
/// @details This function calculates the number of elements of the aligned type required to hold an
/// object of the specified type.
#define aligned_countof(type, aligned_type)                                                        \
    (((sizeof(type) + (sizeof(aligned_type))) - 1) / sizeof(aligned_type))

/// @brief Function used to get byte size aligned to a specific type
/// @details This function calculates the byte size of a type aligned to the specified alignment
/// type.
#define aligned_sizeof(type, aligned_type)                                                         \
    (aligned_countof(type, aligned_type) * sizeof(aligned_type))

/// @brief Function used to get byte size aligned to 32-bit boundary
/// @details This function calculates the byte size of a type aligned to a 32-bit boundary.
#define sizeof32(type) ((sizeof(type) + 3) & ~3)

/// @brief Function used to get byte size aligned to 64-bit boundary
/// @details This function calculates the byte size of a type aligned to a 64-bit boundary.
#define sizeof64(type) ((sizeof(type) + 7) & ~7)

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _UPES_H_
