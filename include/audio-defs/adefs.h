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

#ifndef _ADEFS_H_
#define _ADEFS_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* To be used for all public API */
#ifdef ADEF_API_EXPORTS
#	ifdef _WIN32
#		define ADEF_API __declspec(dllexport)
#	else /* !_WIN32 */
#		define ADEF_API __attribute__((visibility("default")))
#	endif /* !_WIN32 */
#else /* !ADEF_API_EXPORTS */
#	define ADEF_API
#endif /* !ADEF_API_EXPORTS */


/* Forward declaration */
struct json_object;


#define ADEF_ARRAY_SIZE(x) (sizeof(x) / sizeof(*(x)))


/* Audio encoding */
enum adef_encoding {
	/* Unknown encoding */
	ADEF_ENCODING_UNKNOWN = 0,

	/* Pulse-code modulation (PCM) */
	ADEF_ENCODING_PCM,

	/* ISO/IEC 14496-3 MPEG-4 Audio - AAC profile (Low Complexity) */
	ADEF_ENCODING_AAC_LC,

	/* Enum values count (invalid value) */
	ADEF_ENCODING_MAX,
};


/* AAC data format  */
enum adef_aac_data_format {
	/* Unknown AAC data format */
	ADEF_AAC_DATA_FORMAT_UNKNOWN = 0,

	/* "as is" access units (packet based since there is no sync layer) */
	ADEF_AAC_DATA_FORMAT_RAW,

	/* ADIF bitstream data format */
	ADEF_AAC_DATA_FORMAT_ADIF,

	/* ADTS bitstream data format */
	ADEF_AAC_DATA_FORMAT_ADTS,

	/* Enum values count (invalid value) */
	ADEF_AAC_DATA_FORMAT_MAX,
};


/* See 'WAVE and AVI Codec Registries (Historic Registry)' in 'iana.org' */
enum adef_wave_format {
	/* Unknown */
	ADEF_WAVE_FORMAT_UNKNOWN = 0,

	/* Microsoft PCM (uncompressed) */
	ADEF_WAVE_FORMAT_PCM = 1,

	/* Microsoft ADPCM */
	ADEF_WAVE_FORMAT_ADPCM = 2,

	/* Microsoft IEEE float */
	ADEF_WAVE_FORMAT_IEEE_FLOAT = 3,

	/* ITU G.711 a-law */
	ADEF_WAVE_FORMAT_ALAW = 6,

	/* ITU G.711 u-law */
	ADEF_WAVE_FORMAT_MULAW = 7,

	/* Antex G.723 ADPCM */
	WAVE_FORMAT_G723_ADPCM = 0x14,

	/* Enum values count (invalid value) */
	ADEF_WAVE_FORMAT_MAX,
};


/* Audio format */
struct adef_format {
	/* Audio encoding */
	enum adef_encoding encoding;

	/* Channel count */
	unsigned int channel_count;

	/* Bit depth */
	unsigned int bit_depth;

	/* Sampling rate */
	unsigned int sample_rate;

	/* PCM format parameters (only significant for ADEF_ENCODING_PCM
	 * audio encoding) */
	struct {
		/* Interleaving: true for interleaved channels, false for
		 * non-interleaved channels */
		bool interleaved;

		/* Sign: true for signed values, false for unsigned values */
		bool signed_val;

		/* Endianness: true is little-endian, false is big-endian */
		bool little_endian;
	} pcm;

	/* AAC format parameters (only significant for ADEF_ENCODING_AAC_LC
	 * audio encoding) */
	struct {
		/* AAC data format (transport type) */
		enum adef_aac_data_format data_format;
	} aac;
};


/* Commonly used formats */
/* Pulse-code modulation (PCM) formats */
extern ADEF_API const struct adef_format adef_pcm_16b_8000hz_mono;
extern ADEF_API const struct adef_format adef_pcm_16b_8000hz_stereo;
extern ADEF_API const struct adef_format adef_pcm_16b_11025hz_mono;
extern ADEF_API const struct adef_format adef_pcm_16b_11025hz_stereo;
extern ADEF_API const struct adef_format adef_pcm_16b_12000hz_mono;
extern ADEF_API const struct adef_format adef_pcm_16b_12000hz_stereo;
extern ADEF_API const struct adef_format adef_pcm_16b_16000hz_mono;
extern ADEF_API const struct adef_format adef_pcm_16b_16000hz_stereo;
extern ADEF_API const struct adef_format adef_pcm_16b_22050hz_mono;
extern ADEF_API const struct adef_format adef_pcm_16b_22050hz_stereo;
extern ADEF_API const struct adef_format adef_pcm_16b_24000hz_mono;
extern ADEF_API const struct adef_format adef_pcm_16b_24000hz_stereo;
extern ADEF_API const struct adef_format adef_pcm_16b_32000hz_mono;
extern ADEF_API const struct adef_format adef_pcm_16b_32000hz_stereo;
extern ADEF_API const struct adef_format adef_pcm_16b_44100hz_mono;
extern ADEF_API const struct adef_format adef_pcm_16b_44100hz_stereo;
extern ADEF_API const struct adef_format adef_pcm_16b_48000hz_mono;
extern ADEF_API const struct adef_format adef_pcm_16b_48000hz_stereo;
extern ADEF_API const struct adef_format adef_pcm_16b_64000hz_mono;
extern ADEF_API const struct adef_format adef_pcm_16b_64000hz_stereo;
extern ADEF_API const struct adef_format adef_pcm_16b_88200hz_mono;
extern ADEF_API const struct adef_format adef_pcm_16b_88200hz_stereo;
extern ADEF_API const struct adef_format adef_pcm_16b_96000hz_mono;
extern ADEF_API const struct adef_format adef_pcm_16b_96000hz_stereo;
/* AAC profile (Low Complexity) formats */
extern ADEF_API const struct adef_format adef_aac_lc_16b_8000hz_mono_raw;
extern ADEF_API const struct adef_format adef_aac_lc_16b_8000hz_stereo_raw;
extern ADEF_API const struct adef_format adef_aac_lc_16b_11025hz_mono_raw;
extern ADEF_API const struct adef_format adef_aac_lc_16b_11025hz_stereo_raw;
extern ADEF_API const struct adef_format adef_aac_lc_16b_12000hz_mono_raw;
extern ADEF_API const struct adef_format adef_aac_lc_16b_12000hz_stereo_raw;
extern ADEF_API const struct adef_format adef_aac_lc_16b_16000hz_mono_raw;
extern ADEF_API const struct adef_format adef_aac_lc_16b_16000hz_stereo_raw;
extern ADEF_API const struct adef_format adef_aac_lc_16b_22050hz_mono_raw;
extern ADEF_API const struct adef_format adef_aac_lc_16b_22050hz_stereo_raw;
extern ADEF_API const struct adef_format adef_aac_lc_16b_24000hz_mono_raw;
extern ADEF_API const struct adef_format adef_aac_lc_16b_24000hz_stereo_raw;
extern ADEF_API const struct adef_format adef_aac_lc_16b_32000hz_mono_raw;
extern ADEF_API const struct adef_format adef_aac_lc_16b_32000hz_stereo_raw;
extern ADEF_API const struct adef_format adef_aac_lc_16b_44100hz_mono_raw;
extern ADEF_API const struct adef_format adef_aac_lc_16b_44100hz_stereo_raw;
extern ADEF_API const struct adef_format adef_aac_lc_16b_48000hz_mono_raw;
extern ADEF_API const struct adef_format adef_aac_lc_16b_48000hz_stereo_raw;
extern ADEF_API const struct adef_format adef_aac_lc_16b_64000hz_mono_raw;
extern ADEF_API const struct adef_format adef_aac_lc_16b_64000hz_stereo_raw;
extern ADEF_API const struct adef_format adef_aac_lc_16b_88200hz_mono_raw;
extern ADEF_API const struct adef_format adef_aac_lc_16b_88200hz_stereo_raw;
extern ADEF_API const struct adef_format adef_aac_lc_16b_96000hz_mono_raw;
extern ADEF_API const struct adef_format adef_aac_lc_16b_96000hz_stereo_raw;
extern ADEF_API const struct adef_format adef_aac_lc_16b_8000hz_mono_adts;
extern ADEF_API const struct adef_format adef_aac_lc_16b_8000hz_stereo_adts;
extern ADEF_API const struct adef_format adef_aac_lc_16b_11025hz_mono_adts;
extern ADEF_API const struct adef_format adef_aac_lc_16b_11025hz_stereo_adts;
extern ADEF_API const struct adef_format adef_aac_lc_16b_12000hz_mono_adts;
extern ADEF_API const struct adef_format adef_aac_lc_16b_12000hz_stereo_adts;
extern ADEF_API const struct adef_format adef_aac_lc_16b_16000hz_mono_adts;
extern ADEF_API const struct adef_format adef_aac_lc_16b_16000hz_stereo_adts;
extern ADEF_API const struct adef_format adef_aac_lc_16b_22050hz_mono_adts;
extern ADEF_API const struct adef_format adef_aac_lc_16b_22050hz_stereo_adts;
extern ADEF_API const struct adef_format adef_aac_lc_16b_24000hz_mono_adts;
extern ADEF_API const struct adef_format adef_aac_lc_16b_24000hz_stereo_adts;
extern ADEF_API const struct adef_format adef_aac_lc_16b_32000hz_mono_adts;
extern ADEF_API const struct adef_format adef_aac_lc_16b_32000hz_stereo_adts;
extern ADEF_API const struct adef_format adef_aac_lc_16b_44100hz_mono_adts;
extern ADEF_API const struct adef_format adef_aac_lc_16b_44100hz_stereo_adts;
extern ADEF_API const struct adef_format adef_aac_lc_16b_48000hz_mono_adts;
extern ADEF_API const struct adef_format adef_aac_lc_16b_48000hz_stereo_adts;
extern ADEF_API const struct adef_format adef_aac_lc_16b_64000hz_mono_adts;
extern ADEF_API const struct adef_format adef_aac_lc_16b_64000hz_stereo_adts;
extern ADEF_API const struct adef_format adef_aac_lc_16b_88200hz_mono_adts;
extern ADEF_API const struct adef_format adef_aac_lc_16b_88200hz_stereo_adts;
extern ADEF_API const struct adef_format adef_aac_lc_16b_96000hz_mono_adts;
extern ADEF_API const struct adef_format adef_aac_lc_16b_96000hz_stereo_adts;


/* Audio frame information */
struct adef_frame_info {
	/* Frame timestamp in units of time scale */
	uint64_t timestamp;

	/* Time scale in Hz */
	uint32_t timescale;

	/* Frame original capture timestamp in microseconds on the
	 * monotonic clock (or 0 if unknown) */
	uint64_t capture_timestamp;

	/* Frame index */
	uint32_t index;
};


/* Audio frame */
struct adef_frame {
	/* Audio format */
	struct adef_format format;

	/* Frame information */
	struct adef_frame_info info;
};


/**
 * Check the validity of a format.
 * @param format: format
 * @return true if the format is valid, or false otherwise
 */
ADEF_API bool adef_is_format_valid(const struct adef_format *format);


/**
 * Compare two adef_format structs.
 * The components of both formats are compared and if one of them is
 * different, the function will return false.
 * @param f1: the first format to compare
 * @param f2: the second format to compare
 * @return true if both format are identical, false otherwise
 */
ADEF_API bool adef_format_cmp(const struct adef_format *f1,
			      const struct adef_format *f2);


/**
 * Check the intersection of a format against capabilities.
 * @param format: format
 * @param caps: capabilities array
 * @param count: capabilities count in array
 * @return true if the format and the capabilities intersect, or false otherwise
 */
ADEF_API bool adef_format_intersect(const struct adef_format *format,
				    const struct adef_format *caps,
				    unsigned int count);


/* Helper macros for printing a format as a string from a struct
 * adef_format */
#define ADEF_FORMAT_TO_STR_FMT "%s/%u/%u/%u/%s/%s/%s/%s"
/* codecheck_ignore[COMPLEX_MACRO] */
#define ADEF_FORMAT_TO_STR_ARG(_format)                                        \
	adef_encoding_to_str((_format)->encoding), (_format)->channel_count,   \
		(_format)->bit_depth, (_format)->sample_rate,                  \
		(_format)->pcm.interleaved ? "INTERLEAVED" : "PLANAR",         \
		(_format)->pcm.signed_val ? "SIGNED" : "UNSIGNED",             \
		(_format)->pcm.little_endian ? "LE" : "BE",                    \
		adef_aac_data_format_to_str((_format)->aac.data_format)


/**
 * Fill a struct adef_format from a string.
 * The case is ignored.
 * @param str: format name to convert
 * @param format: format to fill
 * @return 0 on success, negative errno value in case of error
 */
ADEF_API int adef_format_from_str(const char *str, struct adef_format *format);


/**
 * Get a string from a struct enum adef_format.
 * @param format: format to convert
 * @return a string description of the format, the string should be freed
 *         after usage
 */
ADEF_API char *adef_format_to_str(const struct adef_format *format);


/**
 * Get an enum adef_encoding value from a string.
 * Valid strings are only the suffix of the encoding name (eg. 'AAC_LC').
 * The case is ignored.
 * @param str: encoding name to convert
 * @return the enum adef_encoding value or ADEF_ENCODING_UNKNOWN
 *         if unknown
 */
ADEF_API enum adef_encoding adef_encoding_from_str(const char *str);


/**
 * Get a string from an enum adef_encoding value.
 * @param encoding: encoding value to convert
 * @return a string description of the encoding
 */
ADEF_API const char *adef_encoding_to_str(enum adef_encoding encoding);


/**
 * Get an enum adef_aac_data_format value from a string.
 * Valid strings are only the suffix of the data format name (eg. 'ADTS').
 * The case is ignored.
 * @param str: data format name to convert
 * @return the enum adef_aac_data_format value or ADEF_AAC_DATA_FORMAT_UNKNOWN
 *         if unknown
 */
ADEF_API enum adef_aac_data_format
adef_aac_data_format_from_str(const char *str);


/**
 * Get a string from an enum adef_aac_data_format value.
 * @param data_format: data format value to convert
 * @return a string description of the data format
 */
ADEF_API const char *
adef_aac_data_format_to_str(enum adef_aac_data_format data_format);


/**
 * Write a frame information structure to a JSON object.
 * The jobj JSON object must have been previously allocated.
 * The ownership of the JSON object stays with the caller.
 * @param info: pointer to an adef_frame_info structure
 * @param jobj: pointer to the JSON object to write to (output)
 * @return 0 on success, negative errno value in case of error
 */
ADEF_API
int adef_frame_info_to_json(const struct adef_frame_info *info,
			    struct json_object *jobj);


/**
 * Write a format structure to a JSON object.
 * The jobj JSON object must have been previously allocated.
 * The ownership of the JSON object stays with the caller.
 * @param format: pointer to an adef_format structure
 * @param jobj: pointer to the JSON object to write to (output)
 * @return 0 on success, negative errno value in case of error
 */
ADEF_API
int adef_format_to_json(const struct adef_format *format,
			struct json_object *jobj);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !_ADEFS_H_ */
