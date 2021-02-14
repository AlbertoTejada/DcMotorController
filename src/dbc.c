/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2018-2019 Erik Moqvist
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * This file was generated by cantools version 36.1.0 Tue Jan 26 21:24:21 2021.
 */

#include <string.h>

#include "dbc.h"

static inline uint8_t pack_left_shift_u8(
    uint8_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint8_t)((uint8_t)(value << shift) & mask);
}

static inline uint8_t pack_left_shift_u16(
    uint16_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint8_t)((uint8_t)(value << shift) & mask);
}

static inline uint8_t pack_left_shift_u64(
    uint64_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint8_t)((uint8_t)(value << shift) & mask);
}

static inline uint8_t pack_right_shift_u16(
    uint16_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint8_t)((uint8_t)(value >> shift) & mask);
}

static inline uint8_t pack_right_shift_u64(
    uint64_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint8_t)((uint8_t)(value >> shift) & mask);
}

static inline uint16_t unpack_left_shift_u16(
    uint8_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint16_t)((uint16_t)(value & mask) << shift);
}

static inline uint64_t unpack_left_shift_u64(
    uint8_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint64_t)((uint64_t)(value & mask) << shift);
}

static inline uint8_t unpack_right_shift_u8(
    uint8_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint8_t)((uint8_t)(value & mask) >> shift);
}

static inline uint16_t unpack_right_shift_u16(
    uint8_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint16_t)((uint16_t)(value & mask) >> shift);
}

static inline uint64_t unpack_right_shift_u64(
    uint8_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint64_t)((uint64_t)(value & mask) >> shift);
}

int dbc_uds_motor_01_unpack(
    struct dbc_uds_motor_01_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    dst_p->uds_motor_01_signal = unpack_right_shift_u64(src_p[0], 0u, 0xffu);
    dst_p->uds_motor_01_signal |= unpack_left_shift_u64(src_p[1], 8u, 0xffu);
    dst_p->uds_motor_01_signal |= unpack_left_shift_u64(src_p[2], 16u, 0xffu);
    dst_p->uds_motor_01_signal |= unpack_left_shift_u64(src_p[3], 24u, 0xffu);
    dst_p->uds_motor_01_signal |= unpack_left_shift_u64(src_p[4], 32u, 0xffu);
    dst_p->uds_motor_01_signal |= unpack_left_shift_u64(src_p[5], 40u, 0xffu);
    dst_p->uds_motor_01_signal |= unpack_left_shift_u64(src_p[6], 48u, 0xffu);
    dst_p->uds_motor_01_signal |= unpack_left_shift_u64(src_p[7], 56u, 0xffu);

    return (0);
}

double dbc_uds_motor_01_uds_motor_01_signal_decode(uint64_t value)
{
    return ((double)value);
}

bool dbc_uds_motor_01_uds_motor_01_signal_is_in_range(uint64_t value)
{
    (void)value;

    return (true);
}

int dbc_xcp_motor_01_unpack(
    struct dbc_xcp_motor_01_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    dst_p->xcp_motor_01_signal = unpack_right_shift_u64(src_p[0], 0u, 0xffu);
    dst_p->xcp_motor_01_signal |= unpack_left_shift_u64(src_p[1], 8u, 0xffu);
    dst_p->xcp_motor_01_signal |= unpack_left_shift_u64(src_p[2], 16u, 0xffu);
    dst_p->xcp_motor_01_signal |= unpack_left_shift_u64(src_p[3], 24u, 0xffu);
    dst_p->xcp_motor_01_signal |= unpack_left_shift_u64(src_p[4], 32u, 0xffu);
    dst_p->xcp_motor_01_signal |= unpack_left_shift_u64(src_p[5], 40u, 0xffu);
    dst_p->xcp_motor_01_signal |= unpack_left_shift_u64(src_p[6], 48u, 0xffu);
    dst_p->xcp_motor_01_signal |= unpack_left_shift_u64(src_p[7], 56u, 0xffu);

    return (0);
}

double dbc_xcp_motor_01_xcp_motor_01_signal_decode(uint64_t value)
{
    return ((double)value);
}

bool dbc_xcp_motor_01_xcp_motor_01_signal_is_in_range(uint64_t value)
{
    (void)value;

    return (true);
}

int dbc_speed_and_direction_pack(
    uint8_t *dst_p,
    const struct dbc_speed_and_direction_t *src_p,
    size_t size)
{
    uint16_t motor_speed;
    uint16_t wheels_direction;

    if (size < 4u) {
        return (-EINVAL);
    }

    memset(&dst_p[0], 0, 4);

    dst_p[0] |= pack_left_shift_u8(src_p->motor_state, 0u, 0x01u);
    wheels_direction = (uint16_t)src_p->wheels_direction;
    dst_p[0] |= pack_left_shift_u16(wheels_direction, 1u, 0xfeu);
    dst_p[1] |= pack_right_shift_u16(wheels_direction, 7u, 0xffu);
    motor_speed = (uint16_t)src_p->motor_speed;
    dst_p[2] |= pack_left_shift_u16(motor_speed, 0u, 0xffu);
    dst_p[3] |= pack_right_shift_u16(motor_speed, 8u, 0xffu);

    return (4);
}

uint8_t dbc_speed_and_direction_motor_state_encode(double value)
{
    return (uint8_t)(value);
}

int16_t dbc_speed_and_direction_wheels_direction_encode(double value)
{
    return (int16_t)(value);
}

int16_t dbc_speed_and_direction_motor_speed_encode(double value)
{
    return (int16_t)(value);
}

int dbc_motion_control_unpack(
    struct dbc_motion_control_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    uint16_t targert_direction;
    uint16_t target_speed;

    if (size < 4u) {
        return (-EINVAL);
    }

    dst_p->enable_motor = unpack_right_shift_u8(src_p[0], 0u, 0x01u);
    targert_direction = unpack_right_shift_u16(src_p[0], 1u, 0xfeu);
    targert_direction |= unpack_left_shift_u16(src_p[1], 7u, 0xffu);

    if ((targert_direction & (1u << 14)) != 0u) {
        targert_direction |= 0x8000u;
    }

    dst_p->targert_direction = (int16_t)targert_direction;
    target_speed = unpack_right_shift_u16(src_p[2], 0u, 0xffu);
    target_speed |= unpack_left_shift_u16(src_p[3], 8u, 0xffu);
    dst_p->target_speed = (int16_t)target_speed;

    return (0);
}

double dbc_motion_control_enable_motor_decode(uint8_t value)
{
    return ((double)value);
}

bool dbc_motion_control_enable_motor_is_in_range(uint8_t value)
{
    return (value <= 1u);
}

double dbc_motion_control_targert_direction_decode(int16_t value)
{
    return ((double)value);
}

bool dbc_motion_control_targert_direction_is_in_range(int16_t value)
{
    return ((value >= -16384) && (value <= 16383));
}

double dbc_motion_control_target_speed_decode(int16_t value)
{
    return ((double)value);
}

bool dbc_motion_control_target_speed_is_in_range(int16_t value)
{
    (void)value;

    return (true);
}