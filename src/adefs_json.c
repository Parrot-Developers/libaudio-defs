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
#include <errno.h>
#include <json-c/json.h>

#define ULOG_TAG adef
#include <ulog.h>


int adef_frame_info_to_json(const struct adef_frame_info *info,
			    struct json_object *jobj)
{
	ULOG_ERRNO_RETURN_ERR_IF(info == NULL, EINVAL);
	ULOG_ERRNO_RETURN_ERR_IF(jobj == NULL, EINVAL);

	/* Frame timestamp in units of time scale */
	json_object_object_add(
		jobj, "timestamp", json_object_new_int64(info->timestamp));

	/* Time scale */
	json_object_object_add(
		jobj, "timescale", json_object_new_int(info->timescale));

	/* Frame original capture timestamp in microseconds */
	json_object_object_add(jobj,
			       "capture_timestamp",
			       json_object_new_int64(info->capture_timestamp));

	/* Frame index */
	json_object_object_add(jobj, "index", json_object_new_int(info->index));

	return 0;
}


int adef_format_to_json(const struct adef_format *format,
			struct json_object *jobj)
{
	ULOG_ERRNO_RETURN_ERR_IF(format == NULL, EINVAL);
	ULOG_ERRNO_RETURN_ERR_IF(jobj == NULL, EINVAL);

	/* Audio encoding */
	json_object_object_add(
		jobj,
		"encoding",
		json_object_new_string(adef_encoding_to_str(format->encoding)));

	/* Channel count */
	json_object_object_add(jobj,
			       "channel_count",
			       json_object_new_int(format->channel_count));

	/* Bit depth */
	json_object_object_add(
		jobj, "bit_depth", json_object_new_int(format->bit_depth));

	/* Sampling rate */
	json_object_object_add(
		jobj, "sample_rate", json_object_new_int(format->sample_rate));

	switch (format->encoding) {
	case ADEF_ENCODING_PCM: {
		struct json_object *jobj_pcm = json_object_new_object();
		/* Interleaving */
		json_object_object_add(
			jobj_pcm,
			"interleaved",
			json_object_new_boolean(format->pcm.interleaved));

		/* Sign */
		json_object_object_add(
			jobj_pcm,
			"signed_val",
			json_object_new_boolean(format->pcm.signed_val));

		/* Endianness */
		json_object_object_add(
			jobj_pcm,
			"little_endian",
			json_object_new_boolean(format->pcm.little_endian));
		json_object_object_add(jobj, "pcm", jobj_pcm);
		break;
	}
	case ADEF_ENCODING_AAC_LC: {
		struct json_object *jobj_aac_lc = json_object_new_object();
		/* AAC data format (transport type) */
		json_object_object_add(
			jobj_aac_lc,
			"data_format",
			json_object_new_string(adef_aac_data_format_to_str(
				format->aac.data_format)));
		json_object_object_add(jobj, "aac_lc", jobj_aac_lc);
		break;
	}
	default:
		break;
	}

	return 0;
}
