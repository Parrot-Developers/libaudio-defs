/**
 * Copyright (c) 2021 Parrot Drones SAS
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of the Parrot Drones SAS Company nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE PARROT DRONES SAS COMPANY BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <audio-defs/adefs.h>


#define MONO 1
#define STEREO 2


/* Build a PCM format from:
 * - Encoding
 * - Channel count
 * - Bit depth
 * - Sample rate
 * - (PCM-specific) Interleaved
 * - (PCM-specific) Signed value
 * - (PCM-specific) Little endian
 */
#define ADEF_MAKE_PCM_FORMAT(_name,                                            \
			     _encoding,                                        \
			     _channel_count,                                   \
			     _bit_depth,                                       \
			     _sample_rate,                                     \
			     _pcm_interleaved,                                 \
			     _pcm_signed_val,                                  \
			     _pcm_little_endian)                               \
	const struct adef_format _name = {                                     \
		.encoding = ADEF_ENCODING_##_encoding,                         \
		.channel_count = _channel_count,                               \
		.bit_depth = _bit_depth,                                       \
		.sample_rate = _sample_rate,                                   \
		.pcm =                                                         \
			{                                                      \
				.interleaved = _pcm_interleaved,               \
				.signed_val = _pcm_signed_val,                 \
				.little_endian = _pcm_little_endian,           \
			},                                                     \
		.aac =                                                         \
			{                                                      \
				.data_format = ADEF_AAC_DATA_FORMAT_UNKNOWN,   \
			},                                                     \
	}

/* Pulse-code modulation (PCM) formats */
ADEF_MAKE_PCM_FORMAT(adef_pcm_16b_8000hz_mono,
		     PCM,
		     MONO,
		     16,
		     8000,
		     true,
		     true,
		     true);
ADEF_MAKE_PCM_FORMAT(adef_pcm_16b_8000hz_stereo,
		     PCM,
		     STEREO,
		     16,
		     8000,
		     true,
		     true,
		     true);
ADEF_MAKE_PCM_FORMAT(adef_pcm_16b_11025hz_mono,
		     PCM,
		     MONO,
		     16,
		     11025,
		     true,
		     true,
		     true);
ADEF_MAKE_PCM_FORMAT(adef_pcm_16b_11025hz_stereo,
		     PCM,
		     STEREO,
		     16,
		     11025,
		     true,
		     true,
		     true);
ADEF_MAKE_PCM_FORMAT(adef_pcm_16b_12000hz_mono,
		     PCM,
		     MONO,
		     16,
		     12000,
		     true,
		     true,
		     true);
ADEF_MAKE_PCM_FORMAT(adef_pcm_16b_12000hz_stereo,
		     PCM,
		     STEREO,
		     16,
		     12000,
		     true,
		     true,
		     true);
ADEF_MAKE_PCM_FORMAT(adef_pcm_16b_16000hz_mono,
		     PCM,
		     MONO,
		     16,
		     16000,
		     true,
		     true,
		     true);
ADEF_MAKE_PCM_FORMAT(adef_pcm_16b_16000hz_stereo,
		     PCM,
		     STEREO,
		     16,
		     16000,
		     true,
		     true,
		     true);
ADEF_MAKE_PCM_FORMAT(adef_pcm_16b_22050hz_mono,
		     PCM,
		     MONO,
		     16,
		     22050,
		     true,
		     true,
		     true);
ADEF_MAKE_PCM_FORMAT(adef_pcm_16b_22050hz_stereo,
		     PCM,
		     STEREO,
		     16,
		     22050,
		     true,
		     true,
		     true);
ADEF_MAKE_PCM_FORMAT(adef_pcm_16b_24000hz_mono,
		     PCM,
		     MONO,
		     16,
		     24000,
		     true,
		     true,
		     true);
ADEF_MAKE_PCM_FORMAT(adef_pcm_16b_24000hz_stereo,
		     PCM,
		     STEREO,
		     16,
		     24000,
		     true,
		     true,
		     true);
ADEF_MAKE_PCM_FORMAT(adef_pcm_16b_32000hz_mono,
		     PCM,
		     MONO,
		     16,
		     32000,
		     true,
		     true,
		     true);
ADEF_MAKE_PCM_FORMAT(adef_pcm_16b_32000hz_stereo,
		     PCM,
		     STEREO,
		     16,
		     32000,
		     true,
		     true,
		     true);
ADEF_MAKE_PCM_FORMAT(adef_pcm_16b_44100hz_mono,
		     PCM,
		     MONO,
		     16,
		     44100,
		     true,
		     true,
		     true);
ADEF_MAKE_PCM_FORMAT(adef_pcm_16b_44100hz_stereo,
		     PCM,
		     STEREO,
		     16,
		     44100,
		     true,
		     true,
		     true);
ADEF_MAKE_PCM_FORMAT(adef_pcm_16b_48000hz_mono,
		     PCM,
		     MONO,
		     16,
		     48000,
		     true,
		     true,
		     true);
ADEF_MAKE_PCM_FORMAT(adef_pcm_16b_48000hz_stereo,
		     PCM,
		     STEREO,
		     16,
		     48000,
		     true,
		     true,
		     true);
ADEF_MAKE_PCM_FORMAT(adef_pcm_16b_64000hz_mono,
		     PCM,
		     MONO,
		     16,
		     64000,
		     true,
		     true,
		     true);
ADEF_MAKE_PCM_FORMAT(adef_pcm_16b_64000hz_stereo,
		     PCM,
		     STEREO,
		     16,
		     64000,
		     true,
		     true,
		     true);
ADEF_MAKE_PCM_FORMAT(adef_pcm_16b_88200hz_mono,
		     PCM,
		     MONO,
		     16,
		     88200,
		     true,
		     true,
		     true);
ADEF_MAKE_PCM_FORMAT(adef_pcm_16b_88200hz_stereo,
		     PCM,
		     STEREO,
		     16,
		     88200,
		     true,
		     true,
		     true);
ADEF_MAKE_PCM_FORMAT(adef_pcm_16b_96000hz_mono,
		     PCM,
		     MONO,
		     16,
		     96000,
		     true,
		     true,
		     true);
ADEF_MAKE_PCM_FORMAT(adef_pcm_16b_96000hz_stereo,
		     PCM,
		     STEREO,
		     16,
		     96000,
		     true,
		     true,
		     true);


/* Build an AAC_LC format from:
 * - Encoding
 * - Channel count
 * - Bit depth
 * - Sample rate
 * - (AAC-specific) Data format
 */
#define ADEF_MAKE_AAC_LC_FORMAT(_name,                                         \
				_encoding,                                     \
				_channel_count,                                \
				_bit_depth,                                    \
				_sample_rate,                                  \
				_aac_data_fmt)                                 \
	const struct adef_format _name = {                                     \
		.encoding = ADEF_ENCODING_##_encoding,                         \
		.channel_count = _channel_count,                               \
		.bit_depth = _bit_depth,                                       \
		.sample_rate = _sample_rate,                                   \
		.pcm =                                                         \
			{                                                      \
				.interleaved = false,                          \
				.signed_val = false,                           \
				.little_endian = false,                        \
			},                                                     \
		.aac =                                                         \
			{                                                      \
				.data_format =                                 \
					ADEF_AAC_DATA_FORMAT_##_aac_data_fmt,  \
			},                                                     \
	}

/* AAC profile (Low Complexity) formats (RAW) */
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_8000hz_mono_raw,
			AAC_LC,
			MONO,
			16,
			8000,
			RAW);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_8000hz_stereo_raw,
			AAC_LC,
			STEREO,
			16,
			8000,
			RAW);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_11025hz_mono_raw,
			AAC_LC,
			MONO,
			16,
			11025,
			RAW);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_11025hz_stereo_raw,
			AAC_LC,
			STEREO,
			16,
			11025,
			RAW);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_12000hz_mono_raw,
			AAC_LC,
			MONO,
			16,
			12000,
			RAW);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_12000hz_stereo_raw,
			AAC_LC,
			STEREO,
			16,
			12000,
			RAW);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_16000hz_mono_raw,
			AAC_LC,
			MONO,
			16,
			16000,
			RAW);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_16000hz_stereo_raw,
			AAC_LC,
			STEREO,
			16,
			16000,
			RAW);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_22050hz_mono_raw,
			AAC_LC,
			MONO,
			16,
			22050,
			RAW);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_22050hz_stereo_raw,
			AAC_LC,
			STEREO,
			16,
			22050,
			RAW);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_24000hz_mono_raw,
			AAC_LC,
			MONO,
			16,
			24000,
			RAW);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_24000hz_stereo_raw,
			AAC_LC,
			STEREO,
			16,
			24000,
			RAW);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_32000hz_mono_raw,
			AAC_LC,
			MONO,
			16,
			32000,
			RAW);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_32000hz_stereo_raw,
			AAC_LC,
			STEREO,
			16,
			32000,
			RAW);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_44100hz_mono_raw,
			AAC_LC,
			MONO,
			16,
			44100,
			RAW);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_44100hz_stereo_raw,
			AAC_LC,
			STEREO,
			16,
			44100,
			RAW);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_48000hz_mono_raw,
			AAC_LC,
			MONO,
			16,
			48000,
			RAW);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_48000hz_stereo_raw,
			AAC_LC,
			STEREO,
			16,
			48000,
			RAW);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_64000hz_mono_raw,
			AAC_LC,
			MONO,
			16,
			64000,
			RAW);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_64000hz_stereo_raw,
			AAC_LC,
			STEREO,
			16,
			64000,
			RAW);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_88200hz_mono_raw,
			AAC_LC,
			MONO,
			16,
			88200,
			RAW);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_88200hz_stereo_raw,
			AAC_LC,
			STEREO,
			16,
			88200,
			RAW);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_96000hz_mono_raw,
			AAC_LC,
			MONO,
			16,
			96000,
			RAW);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_96000hz_stereo_raw,
			AAC_LC,
			STEREO,
			16,
			96000,
			RAW);

/* AAC profile (Low Complexity) formats (ADTS) */
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_8000hz_mono_adts,
			AAC_LC,
			MONO,
			16,
			8000,
			ADTS);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_8000hz_stereo_adts,
			AAC_LC,
			STEREO,
			16,
			8000,
			ADTS);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_11025hz_mono_adts,
			AAC_LC,
			MONO,
			16,
			11025,
			ADTS);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_11025hz_stereo_adts,
			AAC_LC,
			STEREO,
			16,
			11025,
			ADTS);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_12000hz_mono_adts,
			AAC_LC,
			MONO,
			16,
			12000,
			ADTS);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_12000hz_stereo_adts,
			AAC_LC,
			STEREO,
			16,
			12000,
			ADTS);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_16000hz_mono_adts,
			AAC_LC,
			MONO,
			16,
			16000,
			ADTS);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_16000hz_stereo_adts,
			AAC_LC,
			STEREO,
			16,
			16000,
			ADTS);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_22050hz_mono_adts,
			AAC_LC,
			MONO,
			16,
			22050,
			ADTS);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_22050hz_stereo_adts,
			AAC_LC,
			STEREO,
			16,
			22050,
			ADTS);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_24000hz_mono_adts,
			AAC_LC,
			MONO,
			16,
			24000,
			ADTS);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_24000hz_stereo_adts,
			AAC_LC,
			STEREO,
			16,
			24000,
			ADTS);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_32000hz_mono_adts,
			AAC_LC,
			MONO,
			16,
			32000,
			ADTS);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_32000hz_stereo_adts,
			AAC_LC,
			STEREO,
			16,
			32000,
			ADTS);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_44100hz_mono_adts,
			AAC_LC,
			MONO,
			16,
			44100,
			ADTS);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_44100hz_stereo_adts,
			AAC_LC,
			STEREO,
			16,
			44100,
			ADTS);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_48000hz_mono_adts,
			AAC_LC,
			MONO,
			16,
			48000,
			ADTS);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_48000hz_stereo_adts,
			AAC_LC,
			STEREO,
			16,
			48000,
			ADTS);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_64000hz_mono_adts,
			AAC_LC,
			MONO,
			16,
			64000,
			ADTS);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_64000hz_stereo_adts,
			AAC_LC,
			STEREO,
			16,
			64000,
			ADTS);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_88200hz_mono_adts,
			AAC_LC,
			MONO,
			16,
			88200,
			ADTS);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_88200hz_stereo_adts,
			AAC_LC,
			STEREO,
			16,
			88200,
			ADTS);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_96000hz_mono_adts,
			AAC_LC,
			MONO,
			16,
			96000,
			ADTS);
ADEF_MAKE_AAC_LC_FORMAT(adef_aac_lc_16b_96000hz_stereo_adts,
			AAC_LC,
			STEREO,
			16,
			96000,
			ADTS);
