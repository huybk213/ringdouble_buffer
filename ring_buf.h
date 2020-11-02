/*
 * ring_buf.h
 *
 *  Created on: Apr 22, 2019
 *      Author: huytv
 */

#ifndef RING_BUF_H_
#define RING_BUF_H_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define RING_BUF_MAX_SIZE 16

typedef struct
{
    uint8_t len;
    uint8_t data[RING_BUF_MAX_SIZE];
} ring_buf_data_t;


typedef struct
{
    ring_buf_data_t * buff;
    uint32_t wrIdx; // write index
    uint32_t rdIdx; // read index
    uint32_t size;
} ring_buf_t;

/**
 * @brief Get number of buffer free in ring_buf 
 * @param[in] buf Pointer to holder buffer
 * @retval Numbers of buffer free
 */
uint32_t ring_buf_get_free(ring_buf_t *buf);

/**
 * @brief Get number of buffer ready to read
 * @param[in] buf Pointer to holder buffer
 * @retval Numbers of buffer ready to read
 */
uint32_t ring_buf_get_size_to_read(ring_buf_t *buf);

/**
 * @brief Write data into buffer
 * @param[in] buf Pointer to holder buffer
 * @param[in] msg Data write to buffer
 * @Note Please check buffer free before write
 */
void ring_buf_write(ring_buf_t *buf, ring_buf_data_t * msg);

/**
 * @brief Read data from buffer
 * @param[in] buf Pointer to holder buffer
 * @param[in] msg Data read to buffer
 * @Note Please check ring_buf_get_size_to_read before read action
 */
void ring_buf_read(ring_buf_t *buf, ring_buf_data_t * msg);

/**
 * @brief Skip data in buffer (increase read index data in buffer)
 * @param[in] buf Pointer to holder buffer
 * @param[in] skip_cnt Skip count
 */
void ring_buf_skip(ring_buf_t *buf, uint32_t skip_cnt);


#endif /* RING_BUF_H_ */