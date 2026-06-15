#ifndef _UPES_OS_H_
#define _UPES_OS_H_

/// @file upes-os.h
/// @brief UPES OS Abstraction Layer
/// @details This header file defines the OS abstraction layer for UPES, providing
///          types and function prototypes for various OS services such as tasks,
///          events, message queues, memory pools, mutexes, semaphores, and timers.
///          The implementation of these functions should be provided in the corresponding
///          source file, tailored to the specific underlying OS.
/// @author Khose-ie<khose-ie@outlook.com>
/// @date   2026-06-14

#include <stdint.h>
#include <upes.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define OS_WAIT_NOW     0
#define OS_WAIT_FOREVER UINT32_MAX

#define OS_EVENT_NONE (0x00000000U)
#define OS_EVENT_ALL  (0xFFFFFFFFU)

/// @brief Event handle type
/// @details Opaque handle representing an event object
typedef void* osEventHandle_t;

/// @brief Message queue handle type
/// @details Opaque handle representing a message queue object
typedef void* osMessageQueueHandle_t;

/// @brief Memory pool handle type
/// @details Opaque handle representing a memory pool object
typedef void* osMemPoolHandle_t;

/// @brief Mutex handle type
/// @details Opaque handle representing a mutex object
typedef void* osMutexHandle_t;

/// @brief Semaphore handle type
/// @details Opaque handle representing a semaphore object
typedef void* osSemaphoreHandle_t;

/// @brief Task handle type
/// @details Opaque handle representing a task control block
typedef void* osTaskHandle_t;

/// @brief Timer handle type
/// @details Opaque handle representing a timer object
typedef void* osTimerHandle_t;

/// @brief OS state enumeration
/// @details Represents the various states the OS can be in
typedef enum
{
    OS_STATE_RUNNING      = 0,
    OS_STATE_INITIALIZING = 1,
    OS_STATE_BLOCKED      = 2,
    OS_STATE_SUSPENDED    = 3,
    OS_STATE_LOCKED       = 4,
    OS_STATE_TERMINATED   = 5,
    OS_STATE_ERR_INIT_MEM = 6,
    OS_STATE_UNKNOWN_ERR  = UINT32_MAX
} osState_t;

/// @brief Task state enumeration
/// @details Represents the various states a task can be in
typedef enum
{
    OS_TASK_STATE_INACTIVE   = 0,
    OS_TASK_STATE_READY      = 1,
    OS_TASK_STATE_RUNNING    = 2,
    OS_TASK_STATE_BLOCKED    = 3,
    OS_TASK_STATE_TERMINATED = 4,
    OS_TASK_STATE_ERROR      = 5,
    OS_TASK_STATE_UNKNOWN    = UINT32_MAX
} osTaskState_t;

/// @brief Task priority enumeration
/// @details Represents the priority levels for tasks
typedef enum
{
    OS_TASK_PRIORITY_NONE      = 0,
    OS_TASK_PRIORITY_IDLE      = 1,
    OS_TASK_PRIORITY_BASE      = 2,
    OS_TASK_PRIORITY_LOW       = 3,
    OS_TASK_PRIORITY_NORMAL    = 4,
    OS_TASK_PRIORITY_HIGH      = 5,
    OS_TASK_PRIORITY_PRIVILEGE = 6,
    OS_TASK_PRIORITY_REALTIME  = 7,
    OS_TASK_PRIORITY_MAX       = OS_TASK_PRIORITY_REALTIME
} osTaskPriority_t;

/// @brief Timer state enumeration
/// @details Represents the various states a timer can be in
typedef enum
{
    OS_TIMER_STATE_IDLE    = 0,
    OS_TIMER_STATE_ACTIVE  = 1,
    OS_TIMER_STATE_EXPIRED = 2,
    OS_TIMER_STATE_DELETED = 3,
    OS_TIMER_STATE_ERROR   = 4,
    OS_TIMER_STATE_UNKNOWN = UINT32_MAX
} osTimerState_t;

/// @brief Initialize the OS abstraction layer
/// @details This function initializes the OS abstraction layer by creating
///          the OS stack byte pool and setting the initial OS state.
/// @return RET_VALUE_OK on success, error code otherwise
RetValue_t os_initialize(void);

/// @brief Initialize the OS memory pool
/// @details This function initializes the OS memory pool used for dynamic
///          memory allocations within the OS abstraction layer.
/// @return RET_VALUE_OK on success, error code otherwise
RetValue_t os_initialize_mem_pool(void);

/// @brief Get the current OS state
/// @return Current OS state
osState_t os_state(void);

/// @brief Get the current system tick count
/// @return Current system tick count in milliseconds
uint32_t os_tick_count(void);

/// @brief  Get the number of tasks currently in the system
/// @return Number of tasks in the system
uint32_t os_task_count(void);

// /// @brief  Suspend the task scheduler
// /// @return Previous scheduler state to be used for resuming
// uint32_t os_suspend_schedule(void);

// /// @brief  Resume the task scheduler
// /// @param previous_state Previous scheduler state returned by @ref os_suspend_schedule
// void os_resume_schedule(uint32_t previous_state);

/// @brief  Get the currently running task
/// @return Handle to the currently running task
osTaskHandle_t os_current_task(void);

/// @brief  Delay the current task for a specified time
/// @details This function puts the current task into a blocked state for the specified number of
/// system ticks.
/// @param ticks Number of system ticks to delay
void os_delay(uint32_t ticks);

/// @brief  Delay the current task until a specified time
/// @details This function delays the current task until the specified time increment has passed
/// since the previous wake time.
/// @param ticks     Time increment in system ticks
void os_delay_interval(uint32_t ticks);

/// @brief  Yield the processor from the current task
/// @details This function allows the current task to yield the processor, allowing other tasks to
/// run.
void os_switch_task(void);

/// @brief  Exit the current task
/// @details This function terminates the execution of the current task.
void os_exit_task(void);

/// @brief  Exit the current task created with static stack allocation
/// @details This function terminates the execution of the current task created with static stack
void os_exit_task_static(void);

/// @brief  Allocate memory from the OS memory pool
/// @details This function allocates a block of memory of the specified size from the OS memory
///          pool.
/// The OS implementation will choose the best-fit memory block from the pool.
/// @param size Size of memory want to allocate in bytes
/// @return Pointer to the allocated memory block, or NULL on failure
void* os_malloc(uint32_t size);

/// @brief  Free memory back to the OS memory pool
/// @details This function frees a previously allocated block of memory back to the OS memory pool.
/// @param ptr Pointer to the memory block to free
/// @param size Size of the memory to free in bytes
void os_free(void* ptr, uint32_t size);

/// @brief  Create a new event object
/// @details This function creates a new event object with the specified name.
/// @param name Name of the event object
/// @return Handle to the created event object or NULL on failure
osEventHandle_t os_event_create(const char* name);

/// @brief  Delete an event object
/// @details This function deletes the specified event object and frees its resources.
/// @param event Handle to the event object to be deleted
void os_event_delete(osEventHandle_t event);

/// @brief  Get the name of an event object
/// @details This function retrieves the name of the specified event object.
/// @param event Handle to the event object
/// @return Pointer to the event object's name string
const char* os_event_name(osEventHandle_t event);

/// @brief  Get the current state of an event object
/// @details This function retrieves the current state (flags) of the specified event object.
/// @param event Handle to the event object
/// @return Current state (flags) of the event object
uint32_t os_event_state(osEventHandle_t event);

/// @brief  Put event flags
/// @details This function puts the specified flags in the event object.
/// @param event Handle to the event object
/// @param events_value Flags to be putted
/// @return RET_VALUE_OK on success, error code otherwise
RetValue_t os_event_put(osEventHandle_t event, uint32_t events_value);

/// @brief  Wait for event flags
/// @details This function waits for the specified flags to be set in the event object.
/// @param event        Handle to the event object
/// @param events_value Flags to wait for
/// @param timeout      Timeout in milliseconds to wait (0 for no wait, OS_WAIT_FOREVER for
/// infinite wait)
/// @return RET_VALUE_OK on success, error code otherwise
RetValue_t os_event_wait(osEventHandle_t event, uint32_t events_value, uint32_t timeout);

/// @brief  Clear event flags
/// @details This function clears the specified flags in the event object.
/// @param event Handle to the event object
/// @param events_value Flags to be cleared
void os_event_clear(osEventHandle_t event, uint32_t events_value);

/// @brief  Wait for event flags and clear them
/// @details This function waits for the specified flags to be set in the event object and clears
/// them upon wakeup.
/// @param event             Handle to the event object
/// @param events_value      Flags to wait for
/// @param out_events_value  Pointer to store the flags that caused the wakeup
/// @param timeout           Timeout in milliseconds to wait (0 for no wait, OS_WAIT_FOREVER
/// for infinite wait)
/// @return RET_VALUE_OK on success, error code otherwise
RetValue_t os_event_wait_and_clear(osEventHandle_t event, uint32_t events_value,
                                   uint32_t* out_events_value, uint32_t timeout);

/// @brief  Create a new message queue
/// @details This function creates a new message queue with the specified parameters.
/// @param name          Name of the message queue
/// @param message_size  Size of each message in bytes
/// @param message_count Maximum number of messages the queue can hold
/// @return Handle to the created message queue or NULL on failure
osMessageQueueHandle_t os_message_queue_create(const char* name, uint32_t message_size,
                                               uint32_t message_count);

/// @brief  Create a new message queue with static buffer
/// @details This function creates a new message queue with the specified parameters,
///     using a statically allocated message buffer.
/// @param name           Name of the message queue
/// @param message_buffer Pointer to the statically allocated message buffer
/// @param message_size   Size of each message in bytes
/// @param message_count  Maximum number of messages the queue can hold
/// @return Handle to the created message queue
osMessageQueueHandle_t os_message_queue_create_static(const char* name, uint8_t* message_buffer,
                                                      uint32_t message_size,
                                                      uint32_t message_count);

/// @brief  Delete a message queue
/// @details This function deletes the specified message queue and frees its resources.
/// @param queue Handle to the message queue to be deleted
void os_message_queue_delete(osMessageQueueHandle_t queue);

/// @brief  Delete a message queue created with static buffer
/// @details This function deletes the specified message queue created with a static buffer.
/// @param queue Handle to the message queue to be deleted
void os_message_queue_delete_static(osMessageQueueHandle_t queue);

/// @brief  Get the name of a message queue
/// @param queue Handle to the message queue
/// @return Pointer to the message queue's name string
const char* os_message_queue_name(osMessageQueueHandle_t queue);

/// @brief  Get the size of a message in the queue
/// @param queue Handle to the message queue
/// @return Size of each message in bytes
uint32_t os_message_queue_message_size(osMessageQueueHandle_t queue);

/// @brief  Get the number of messages currently in the queue
/// @param queue Handle to the message queue
/// @return Number of messages currently in the queue
uint32_t os_message_queue_message_count(osMessageQueueHandle_t queue);

/// @brief  Get the maximum number of messages the queue can hold
/// @param queue Handle to the message queue
/// @return Maximum number of messages the queue can hold
uint32_t os_message_queue_max_message_count(osMessageQueueHandle_t queue);

/// @brief  Send a message to the queue
/// @details This function sends a message to the specified message queue.
/// @param queue    Handle to the message queue
/// @param message  Pointer to the buffer containing the message to send
/// @param timeout  Timeout in milliseconds to wait (0 for no wait, OS_WAIT_FOREVER for
///                 infinite wait)
/// @return RET_VALUE_OK on success, error code otherwise
RetValue_t os_message_queue_send(osMessageQueueHandle_t queue, const void* message,
                                 uint32_t timeout);

/// @brief  Receive a message from the queue
/// @details This function receives a message from the specified message queue.
/// @param queue    Handle to the message queue
/// @param message  Pointer to the buffer to store the received message
/// @param timeout  Timeout in milliseconds to wait for a message (0 for no wait,
/// OS_WAIT_FOREVER for infinite wait)
/// @return RET_VALUE_OK on success, error code otherwise
RetValue_t os_message_queue_receive(osMessageQueueHandle_t queue, void* message, uint32_t timeout);

/// @brief  Clear all messages from the queue
/// @details This function clears all messages currently in the specified message queue.
/// @param queue Handle to the message queue
void os_message_queue_clear(osMessageQueueHandle_t queue);

/// @brief  Create a new memory pool
/// @details This function creates a new memory pool with the specified parameters.
/// @param name        Name of the memory pool
/// @param block_size  Size of each memory block in bytes
/// @param block_count Number of memory blocks in the pool
/// @return Handle to the created memory pool or NULL on failure
osMemPoolHandle_t os_mem_pool_create(const char* name, uint32_t block_size, uint32_t block_count);

/// @brief  Create a new memory pool with static buffer
/// @details This function creates a new memory pool with the specified parameters,
///     using a statically allocated pool buffer.
/// @param name        Name of the memory pool
/// @param pool        Pointer to the statically allocated pool structure
/// @param pool_size   Size of the statically allocated pool buffer in bytes
/// @param pool_mem    Pointer to the statically allocated pool buffer
/// @param block_size  Size of each memory block in bytes
/// @param block_count Number of memory blocks in the pool
/// @return Handle to the created memory pool or NULL on failure
osMemPoolHandle_t os_mem_pool_create_static(const char* name, void* pool, uint32_t pool_size,
                                            uint8_t* pool_mem, uint32_t block_size,
                                            uint32_t block_count);

/// @brief  Delete a memory pool
/// @details This function deletes the specified memory pool and frees its resources.
/// @param pool Handle to the memory pool to be deleted
void os_mem_pool_delete(osMemPoolHandle_t pool);

/// @brief  Delete a memory pool created with static buffer
/// @details This function deletes the specified memory pool created with a static buffer.
/// @param pool Handle to the memory pool to be deleted
void os_mem_pool_delete_static(osMemPoolHandle_t pool);

/// @brief  Get the name of a memory pool
/// @param pool Handle to the memory pool
/// @return Pointer to the memory pool's name string
const char* os_mem_pool_name(osMemPoolHandle_t pool);

/// @brief  Get the size of each memory block in the pool
/// @param pool Handle to the memory pool
/// @return Size of each memory block in bytes
uint32_t os_mem_pool_block_size(osMemPoolHandle_t pool);

/// @brief  Get the number of used memory blocks in the pool
/// @param pool Handle to the memory pool
/// @return Number of memory blocks in the pool
uint32_t os_mem_pool_block_count(osMemPoolHandle_t pool);

/// @brief  Get the maximum number of memory blocks in the pool
/// @param pool Handle to the memory pool
/// @return Maximum number of memory blocks in the pool
uint32_t os_mem_pool_max_block_count(osMemPoolHandle_t pool);

/// @brief  Allocate a memory block from the pool
/// @details This function allocates a memory block from the specified memory pool.
/// @param pool    Handle to the memory pool
/// @param timeout Timeout in milliseconds to wait for a memory block (0 for no wait,
/// OS_WAIT_FOREVER for infinite wait)
/// @return Pointer to the allocated memory block, or NULL on failure
void* os_mem_pool_alloc(osMemPoolHandle_t pool, uint32_t timeout);

/// @brief  Free a memory block back to the pool
/// @details This function frees a previously allocated memory block back to the specified memory
/// pool.
/// @param pool  Handle to the memory pool
/// @param block Pointer to the memory block to be freed
void os_mem_pool_free(osMemPoolHandle_t pool, void* block);

/// @brief  Create a new mutex
/// @details This function creates a new mutex with the specified name.
/// @param name Name of the mutex
/// @return Handle to the created mutex or NULL on failure
osMutexHandle_t os_mutex_create(const char* name);

/// @brief  Delete a mutex
/// @details This function deletes the specified mutex and frees its resources.
/// @param mutex Handle to the mutex to be deleted
void os_mutex_delete(osMutexHandle_t mutex);

/// @brief  Get the name of a mutex
/// @param mutex Handle to the mutex
/// @return Pointer to the mutex's name string
const char* os_mutex_name(osMutexHandle_t mutex);

/// @brief  Get the owner of a mutex
/// @details This function retrieves the handle of the task that currently owns the specified
/// mutex.
/// @param mutex Handle to the mutex
/// @return Handle to the task that currently owns the mutex
osTaskHandle_t os_mutex_owner(osMutexHandle_t mutex);

/// @brief  Lock a mutex
/// @details This function locks the specified mutex, blocking the calling task if necessary.
/// @param mutex   Handle to the mutex
/// @param timeout Timeout in milliseconds to wait for the mutex (0 for no wait,
/// OS_WAIT_FOREVER for infinite wait)
/// @return RET_VALUE_OK on success, error code otherwise
RetValue_t os_mutex_lock(osMutexHandle_t mutex, uint32_t timeout);

/// @brief  Unlock a mutex
/// @details This function unlocks the specified mutex.
/// @param mutex Handle to the mutex
/// @return RET_VALUE_OK on success, error code otherwise
RetValue_t os_mutex_unlock(osMutexHandle_t mutex);

/// @brief  Create a new semaphore
/// @details This function creates a new semaphore with the specified parameters.
/// @param name          Name of the semaphore
/// @param max_count     Maximum count of the semaphore
/// @return Handle to the created semaphore, or NULL on failure
osSemaphoreHandle_t os_semaphore_create(const char* name, uint32_t max_count);

/// @brief  Delete a semaphore
/// @details This function deletes the specified semaphore and frees its resources.
/// @param semaphore Handle to the semaphore to be deleted
void os_semaphore_delete(osSemaphoreHandle_t semaphore);

/// @brief  Get the name of a semaphore
/// @param semaphore Handle to the semaphore
/// @return Pointer to the semaphore's name string
const char* os_semaphore_name(osSemaphoreHandle_t semaphore);

/// @brief  Get the current count of a semaphore
/// @param semaphore Handle to the semaphore
/// @return Current count of the semaphore
uint32_t os_semaphore_count(osSemaphoreHandle_t semaphore);

/// @brief  Take (decrement) a semaphore
/// @details This function takes (decrements) the specified semaphore, blocking the calling task
/// if necessary.
/// @param semaphore Handle to the semaphore
/// @param timeout   Timeout in milliseconds to wait for the semaphore (0 for no wait,
/// OS_WAIT_FOREVER for infinite wait)
/// @return RET_VALUE_OK on success, error code otherwise
RetValue_t os_semaphore_take(osSemaphoreHandle_t semaphore, uint32_t timeout);

/// @brief  Release (increment) a semaphore
/// @details This function releases (increments) the specified semaphore.
/// @param semaphore Handle to the semaphore
/// @return RET_VALUE_OK on success, error code otherwise
RetValue_t os_semaphore_release(osSemaphoreHandle_t semaphore);

/// @brief  Create a new task
/// @details This function creates a new task with the specified parameters.
///     The task will start executing the provided main function with the given argument.
/// @param name        Name of the task
/// @param main        Pointer to the task's main function
/// @param arg         Argument to be passed to the task's main function
/// @param stack_size  Size of the task's stack in bytes
/// @param priority    Priority of the task (use TASK_PRIORITY_* constants)
/// @return Handle to the created task, or NULL on failure
osTaskHandle_t os_task_create(const char* name, void (*main)(void*), void* arg, uint32_t stack_size,
                              osTaskPriority_t priority);

/// @brief  Create a new task with static stack allocation
/// @details This function creates a new task with the specified parameters.
///     The task will start executing the provided main function with the given argument.
/// @param name        Name of the task
/// @param main        Pointer to the task's main function
/// @param arg         Argument to be passed to the task's main function
/// @param stack       Pointer to the static stack buffer
/// @param stack_size  Size of the task's stack in bytes
/// @param priority    Priority of the task (use TASK_PRIORITY_* constants)
/// @return Handle to the created task, or NULL on failure
osTaskHandle_t os_task_create_static(const char* name, void (*main)(void*), void* arg,
                                     uint8_t* stack, uint32_t stack_size,
                                     osTaskPriority_t priority);

/// @brief  Delete a task
/// @details This function deletes the specified task and frees its resources.
/// @param task Handle to the task to be deleted
void os_task_delete(osTaskHandle_t task);

/// @brief  Delete a task created with static stack allocation
/// @details This function deletes the specified task created with static stack allocation.
/// @param task Handle to the task to be deleted
void os_task_delete_static(osTaskHandle_t task);

/// @brief  Get the name of a task
/// @param task Handle to the task control block
/// @return Pointer to the task's name string
const char* os_task_name(osTaskHandle_t task);

/// @brief  Get the current state of a task
/// @param task Handle to the task control block
/// @return Current state of the task
uint32_t os_task_stack_size(osTaskHandle_t task);

/// @brief  Get the priority of a task
/// @param task Handle to the task control block
/// @return Priority of the task
osTaskPriority_t os_task_priority(osTaskHandle_t task);

/// @brief  Get the current state of a task
/// @param task Handle to the task control block
/// @return Current state of the task
osTaskState_t os_task_state(osTaskHandle_t task);

/// @brief  Set the priority of a task
/// @param task     Handle to the task control block
/// @param priority New priority to be set for the task
/// @return RET_VALUE_OK on success, error code otherwise
RetValue_t os_task_set_priority(osTaskHandle_t task, osTaskPriority_t priority);

/// @brief  Suspend a task
/// @param task Handle to the task control block to be suspended
/// @return RET_VALUE_OK on success, error code otherwise
RetValue_t os_task_suspend(osTaskHandle_t task);

/// @brief  Resume a suspended task
/// @param task Handle to the task control block to be resumed
/// @return RET_VALUE_OK on success, error code otherwise
RetValue_t os_task_resume(osTaskHandle_t task);

// /// @brief  Join a task
// /// @details This function waits for the specified task to complete its execution.
// /// @param task Handle to the task to be joined
// /// @return RET_VALUE_OK on success, error code otherwise
// RetValue_t os_task_join(osTaskHandle_t task);

// /// @brief  Detach a task
// /// @details This function detaches the specified task, allowing it to run independently.
// /// @param task Handle to the task to be detached
// /// @return RET_VALUE_OK on success, error code otherwise
// RetValue_t os_task_detach(osTaskHandle_t task);

/// @brief  Create a new timer
/// @details This function creates a new timer with the specified parameters.
/// @param name        Name of the timer
/// @param callback    Pointer to the timer's callback function
/// @param arg         Argument to be passed to the timer's callback function
/// @return Handle to the created timer, or NULL on failure
osTimerHandle_t os_timer_create_once(const char* name, void (*callback)(void*), void* arg);

/// @brief  Create a new periodic timer
/// @details This function creates a new periodic timer with the specified parameters.
/// @param name        Name of the timer
/// @param callback    Pointer to the timer's callback function
/// @param arg         Argument to be passed to the timer's callback function
osTimerHandle_t os_timer_create_periodic(const char* name, void (*callback)(void*), void* arg);

/// @brief  Delete a timer
/// @details This function deletes the specified timer and frees its resources.
/// @param timer Handle to the timer to be deleted
void os_timer_delete(osTimerHandle_t timer);

/// @brief  Get the name of a timer
/// @param timer Handle to the timer
/// @return Pointer to the timer's name string
const char* os_timer_name(osTimerHandle_t timer);

/// @brief  Get the current state of a timer
/// @param timer Handle to the timer
/// @return Current state of the timer
osTimerState_t os_timer_state(osTimerHandle_t timer);

/// @brief  Start a timer
/// @details This function starts the specified timer with the given timeout.
/// @param timer   Handle to the timer
/// @param timeout Timeout in OS count for the timer
/// @return RET_VALUE_OK on success, error code otherwise
RetValue_t os_timer_start(osTimerHandle_t timer, uint32_t timeout);

/// @brief  Stop a timer
/// @details This function stops the specified timer.
/// @param timer Handle to the timer
void os_timer_stop(osTimerHandle_t timer);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _UPES_OS_H_
