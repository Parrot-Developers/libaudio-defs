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

#include <errno.h>
#include <stdio.h>
#include <strings.h>

#define ULOG_TAG adef
#include <ulog.h>
ULOG_DECLARE_TAG(ULOG_TAG);

#include <audio-defs/adefs.h>


static const struct {
	const enum adef_encoding encoding;
	const char *str;
} encoding_map[] = {
	{ADEF_ENCODING_UNKNOWN, "UNKNOWN"},
	{ADEF_ENCODING_PCM, "PCM"},
	{ADEF_ENCODING_AAC_LC, "AAC_LC"},
};


enum adef_encoding adef_encoding_from_str(const char *str)
{
	unsigned int i;
	enum adef_encoding ret = ADEF_ENCODING_UNKNOWN;

	ULOG_ERRNO_RETURN_VAL_IF(str == NULL, EINVAL, ret);

	for (i = 0; i < ADEF_ARRAY_SIZE(encoding_map); i++) {
		if (strcasecmp(str, encoding_map[i].str) == 0)
			return encoding_map[i].encoding;
	}
	ULOGW("%s: unknown encoding '%s'", __func__, str);
	return ret;
}


const char *adef_encoding_to_str(enum adef_encoding encoding)
{
	unsigned int i;
	for (i = 0; i < ADEF_ARRAY_SIZE(encoding_map); i++) {
		if (encoding == encoding_map[i].encoding)
			return encoding_map[i].str;
	}
	return "UNKNOWN";
}


static const struct {
	const enum adef_aac_data_format data_format;
	const char *str;
} aac_data_format_map[] = {
	{ADEF_AAC_DATA_FORMAT_UNKNOWN, "UNKNOWN"},
	{ADEF_AAC_DATA_FORMAT_RAW, "RAW"},
	{ADEF_AAC_DATA_FORMAT_ADIF, "ADIF"},
	{ADEF_AAC_DATA_FORMAT_ADTS, "ADTS"},
};


enum adef_aac_data_format adef_aac_data_format_from_str(const char *str)
{
	unsigned int i;
	enum adef_aac_data_format ret = ADEF_AAC_DATA_FORMAT_UNKNOWN;

	ULOG_ERRNO_RETURN_VAL_IF(str == NULL, EINVAL, ret);

	for (i = 0; i < ADEF_ARRAY_SIZE(aac_data_format_map); i++) {
		if (strcasecmp(str, aac_data_format_map[i].str) == 0)
			return aac_data_format_map[i].data_format;
	}
	ULOGW("%s: unknown data format '%s'", __func__, str);
	return ret;
}


const char *adef_aac_data_format_to_str(enum adef_aac_data_format data_format)
{
	unsigned int i;
	for (i = 0; i < ADEF_ARRAY_SIZE(aac_data_format_map); i++) {
		if (data_format == aac_data_format_map[i].data_format)
			return aac_data_format_map[i].str;
	}
	return "UNKNOWN";
}


bool adef_is_format_valid(const struct adef_format *format)
{
	if (!format)
		return false;

	/* Check enumerator bounds */
	if (format->encoding >= ADEF_ENCODING_MAX)
		return false;

	switch (format->encoding) {
	case ADEF_ENCODING_PCM:
		break;
	case ADEF_ENCODING_AAC_LC:
		if (format->aac.data_format == ADEF_AAC_DATA_FORMAT_UNKNOWN ||
		    format->aac.data_format >= ADEF_AAC_DATA_FORMAT_MAX)
			return false;
		break;
	case ADEF_ENCODING_UNKNOWN:
	default:
		return false;
	}

	if ((!format->channel_count) || (!format->bit_depth) ||
	    (!format->sample_rate))
		return false;

	return true;
}


bool adef_format_cmp(const struct adef_format *f1, const struct adef_format *f2)
{
	bool ret;
	if (!f1 && !f2)
		return true;
	if (!f1 || !f2)
		return false;
	ret = f1->encoding == f2->encoding &&
	      f1->channel_count == f2->channel_count &&
	      f1->bit_depth == f2->bit_depth &&
	      f1->sample_rate == f2->sample_rate;
	if (f1->encoding == ADEF_ENCODING_PCM)
		ret &= f1->pcm.interleaved == f2->pcm.interleaved &&
		       f1->pcm.signed_val == f2->pcm.signed_val &&
		       f1->pcm.little_endian == f2->pcm.little_endian;
	if (f1->encoding == ADEF_ENCODING_AAC_LC)
		ret &= f1->aac.data_format == f2->aac.data_format;
	return ret;
}


bool adef_format_intersect(const struct adef_format *format,
			   const struct adef_format *caps,
			   unsigned int count)
{
	if (!caps || !adef_is_format_valid(format))
		return false;

	while (count--) {
		if (adef_format_cmp(format, caps++))
			return true;
	}

	return false;
}


static const struct {
	const char *str;
	const struct adef_format *format;
} format_map[] = {
	/* Pulse-code modulation (PCM) formats */
	{"pcm_16b_8000hz_mono", &adef_pcm_16b_8000hz_mono},
	{"pcm_16b_8000hz_stereo", &adef_pcm_16b_8000hz_stereo},
	{"pcm_16b_11025hz_mono", &adef_pcm_16b_11025hz_mono},
	{"pcm_16b_11025hz_stereo", &adef_pcm_16b_11025hz_stereo},
	{"pcm_16b_12000hz_mono", &adef_pcm_16b_12000hz_mono},
	{"pcm_16b_12000hz_stereo", &adef_pcm_16b_12000hz_stereo},
	{"pcm_16b_16000hz_mono", &adef_pcm_16b_16000hz_mono},
	{"pcm_16b_16000hz_stereo", &adef_pcm_16b_16000hz_stereo},
	{"pcm_16b_22050hz_mono", &adef_pcm_16b_22050hz_mono},
	{"pcm_16b_22050hz_stereo", &adef_pcm_16b_22050hz_stereo},
	{"pcm_16b_24000hz_mono", &adef_pcm_16b_24000hz_mono},
	{"pcm_16b_24000hz_stereo", &adef_pcm_16b_24000hz_stereo},
	{"pcm_16b_32000hz_mono", &adef_pcm_16b_32000hz_mono},
	{"pcm_16b_32000hz_stereo", &adef_pcm_16b_32000hz_stereo},
	{"pcm_16b_44100hz_mono", &adef_pcm_16b_44100hz_mono},
	{"pcm_16b_44100hz_stereo", &adef_pcm_16b_44100hz_stereo},
	{"pcm_16b_48000hz_mono", &adef_pcm_16b_48000hz_mono},
	{"pcm_16b_48000hz_stereo", &adef_pcm_16b_48000hz_stereo},
	{"pcm_16b_64000hz_mono", &adef_pcm_16b_64000hz_mono},
	{"pcm_16b_64000hz_stereo", &adef_pcm_16b_64000hz_stereo},
	{"pcm_16b_88200hz_mono", &adef_pcm_16b_88200hz_mono},
	{"pcm_16b_88200hz_stereo", &adef_pcm_16b_88200hz_stereo},
	{"pcm_16b_96000hz_mono", &adef_pcm_16b_96000hz_mono},
	{"pcm_16b_96000hz_stereo", &adef_pcm_16b_96000hz_stereo},
	/* AAC profile (Low Complexity) formats: RAW */
	{"aac_lc_16b_8000hz_mono_raw", &adef_aac_lc_16b_8000hz_mono_raw},
	{"aac_lc_16b_8000hz_stereo_raw", &adef_aac_lc_16b_8000hz_stereo_raw},
	{"aac_lc_16b_11025hz_mono_raw", &adef_aac_lc_16b_11025hz_mono_raw},
	{"aac_lc_16b_11025hz_stereo_raw", &adef_aac_lc_16b_11025hz_stereo_raw},
	{"aac_lc_16b_12000hz_mono_raw", &adef_aac_lc_16b_12000hz_mono_raw},
	{"aac_lc_16b_12000hz_stereo_raw", &adef_aac_lc_16b_12000hz_stereo_raw},
	{"aac_lc_16b_16000hz_mono_raw", &adef_aac_lc_16b_16000hz_mono_raw},
	{"aac_lc_16b_16000hz_stereo_raw", &adef_aac_lc_16b_16000hz_stereo_raw},
	{"aac_lc_16b_22050hz_mono_raw", &adef_aac_lc_16b_22050hz_mono_raw},
	{"aac_lc_16b_22050hz_stereo_raw", &adef_aac_lc_16b_22050hz_stereo_raw},
	{"aac_lc_16b_24000hz_mono_raw", &adef_aac_lc_16b_24000hz_mono_raw},
	{"aac_lc_16b_24000hz_stereo_raw", &adef_aac_lc_16b_24000hz_stereo_raw},
	{"aac_lc_16b_32000hz_mono_raw", &adef_aac_lc_16b_32000hz_mono_raw},
	{"aac_lc_16b_32000hz_stereo_raw", &adef_aac_lc_16b_32000hz_stereo_raw},
	{"aac_lc_16b_44100hz_mono_raw", &adef_aac_lc_16b_44100hz_mono_raw},
	{"aac_lc_16b_44100hz_stereo_raw", &adef_aac_lc_16b_44100hz_stereo_raw},
	{"aac_lc_16b_48000hz_mono_raw", &adef_aac_lc_16b_48000hz_mono_raw},
	{"aac_lc_16b_48000hz_stereo_raw", &adef_aac_lc_16b_48000hz_stereo_raw},
	{"aac_lc_16b_64000hz_mono_raw", &adef_aac_lc_16b_64000hz_mono_raw},
	{"aac_lc_16b_64000hz_stereo_raw", &adef_aac_lc_16b_64000hz_stereo_raw},
	{"aac_lc_16b_88200hz_mono_raw", &adef_aac_lc_16b_88200hz_mono_raw},
	{"aac_lc_16b_88200hz_stereo_raw", &adef_aac_lc_16b_88200hz_stereo_raw},
	{"aac_lc_16b_96000hz_mono_raw", &adef_aac_lc_16b_96000hz_mono_raw},
	{"aac_lc_16b_96000hz_stereo_raw", &adef_aac_lc_16b_96000hz_stereo_raw},
	/* AAC profile (Low Complexity) formats: ADTS */
	{"aac_lc_16b_8000hz_mono_adts", &adef_aac_lc_16b_8000hz_mono_adts},
	{"aac_lc_16b_8000hz_stereo_adts", &adef_aac_lc_16b_8000hz_stereo_adts},
	{"aac_lc_16b_11025hz_mono_adts", &adef_aac_lc_16b_11025hz_mono_adts},
	{"aac_lc_16b_11025hz_stereo_adts",
	 &adef_aac_lc_16b_11025hz_stereo_adts},
	{"aac_lc_16b_12000hz_mono_adts", &adef_aac_lc_16b_12000hz_mono_adts},
	{"aac_lc_16b_12000hz_stereo_adts",
	 &adef_aac_lc_16b_12000hz_stereo_adts},
	{"aac_lc_16b_16000hz_mono_adts", &adef_aac_lc_16b_16000hz_mono_adts},
	{"aac_lc_16b_16000hz_stereo_adts",
	 &adef_aac_lc_16b_16000hz_stereo_adts},
	{"aac_lc_16b_22050hz_mono_adts", &adef_aac_lc_16b_22050hz_mono_adts},
	{"aac_lc_16b_22050hz_stereo_adts",
	 &adef_aac_lc_16b_22050hz_stereo_adts},
	{"aac_lc_16b_24000hz_mono_adts", &adef_aac_lc_16b_24000hz_mono_adts},
	{"aac_lc_16b_24000hz_stereo_adts",
	 &adef_aac_lc_16b_24000hz_stereo_adts},
	{"aac_lc_16b_32000hz_mono_adts", &adef_aac_lc_16b_32000hz_mono_adts},
	{"aac_lc_16b_32000hz_stereo_adts",
	 &adef_aac_lc_16b_32000hz_stereo_adts},
	{"aac_lc_16b_44100hz_mono_adts", &adef_aac_lc_16b_44100hz_mono_adts},
	{"aac_lc_16b_44100hz_stereo_adts",
	 &adef_aac_lc_16b_44100hz_stereo_adts},
	{"aac_lc_16b_48000hz_mono_adts", &adef_aac_lc_16b_48000hz_mono_adts},
	{"aac_lc_16b_48000hz_stereo_adts",
	 &adef_aac_lc_16b_48000hz_stereo_adts},
	{"aac_lc_16b_64000hz_mono_adts", &adef_aac_lc_16b_64000hz_mono_adts},
	{"aac_lc_16b_64000hz_stereo_adts",
	 &adef_aac_lc_16b_64000hz_stereo_adts},
	{"aac_lc_16b_88200hz_mono_adts", &adef_aac_lc_16b_88200hz_mono_adts},
	{"aac_lc_16b_88200hz_stereo_adts",
	 &adef_aac_lc_16b_88200hz_stereo_adts},
	{"aac_lc_16b_96000hz_mono_adts", &adef_aac_lc_16b_96000hz_mono_adts},
	{"aac_lc_16b_96000hz_stereo_adts",
	 &adef_aac_lc_16b_96000hz_stereo_adts},
};


int adef_format_from_str(const char *str, struct adef_format *format)
{
	const char *delim = "/";
	char *s, *tok, *p;
	int ret = -EINVAL;

	if (!str || !format)
		return -EINVAL;

	/* First find in registered formats */
	for (unsigned int i = 0; i < ADEF_ARRAY_SIZE(format_map); i++) {
		if (!strcasecmp(format_map[i].str, str)) {
			memcpy(format, format_map[i].format, sizeof(*format));
			return 0;
		}
	}

	/* Copy string for parsing */
	s = strdup(str);

	/* Get encoding */
	tok = strtok_r(s, delim, &p);
	if (!tok)
		goto out;
	format->encoding = adef_encoding_from_str(tok);

	/* Get channel count */
	tok = strtok_r(NULL, delim, &p);
	if (!tok)
		goto out;
	format->channel_count = strtoul(tok, NULL, 10);

	/* Get bit depth */
	tok = strtok_r(NULL, delim, &p);
	if (!tok)
		goto out;
	format->bit_depth = strtoul(tok, NULL, 10);

	/* Get sample rate */
	tok = strtok_r(NULL, delim, &p);
	if (!tok)
		goto out;
	format->sample_rate = strtoul(tok, NULL, 10);

	/* Get interleaved */
	tok = strtok_r(NULL, delim, &p);
	if (!tok)
		goto out;
	format->pcm.interleaved = !strcmp(tok, "INTERLEAVED") ? true : false;

	/* Get signed value */
	tok = strtok_r(NULL, delim, &p);
	if (!tok)
		goto out;
	format->pcm.signed_val = !strcmp(tok, "SIGNED") ? true : false;

	/* Get little endian */
	tok = strtok_r(NULL, delim, &p);
	if (!tok)
		goto out;
	format->pcm.little_endian = !strcmp(tok, "LE") ? true : false;

	/* Get AAC data format */
	tok = strtok_r(NULL, delim, &p);
	if (!tok)
		goto out;
	format->aac.data_format = adef_aac_data_format_from_str(tok);

	/* Parsing succeed */
	ret = 0;

out:
	/* Free string */
	free(s);

	return ret;
}


char *adef_format_to_str(const struct adef_format *format)
{
	char *str;

	if (!format)
		return NULL;

	/* First find in registered formats */
	for (unsigned int i = 0; i < ADEF_ARRAY_SIZE(format_map); i++) {
		if (adef_format_cmp(format_map[i].format, format))
			return strdup(format_map[i].str);
	}

	/* Generate generic format name */
	if (asprintf(&str,
		     ADEF_FORMAT_TO_STR_FMT,
		     ADEF_FORMAT_TO_STR_ARG(format)) == -1)
		return NULL;

	return str;
}
