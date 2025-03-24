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

#include "adefs_test.h"


static void test_aac_data_format_from_str(void)
{
	int count = 0;
	enum adef_aac_data_format value;

	value = adef_aac_data_format_from_str(NULL);
	CU_ASSERT_EQUAL(value, ADEF_AAC_DATA_FORMAT_UNKNOWN);

	value = adef_aac_data_format_from_str("?");
	CU_ASSERT_EQUAL(value, ADEF_AAC_DATA_FORMAT_UNKNOWN);

	value = adef_aac_data_format_from_str("abcde");
	CU_ASSERT_EQUAL(value, ADEF_AAC_DATA_FORMAT_UNKNOWN);

	value = adef_aac_data_format_from_str("UNKNOWN");
	count++;
	CU_ASSERT_EQUAL(value, ADEF_AAC_DATA_FORMAT_UNKNOWN);

	value = adef_aac_data_format_from_str("RAW");
	count++;
	CU_ASSERT_EQUAL(value, ADEF_AAC_DATA_FORMAT_RAW);

	value = adef_aac_data_format_from_str("ADIF");
	count++;
	CU_ASSERT_EQUAL(value, ADEF_AAC_DATA_FORMAT_ADIF);

	value = adef_aac_data_format_from_str("ADTS");
	count++;
	CU_ASSERT_EQUAL(value, ADEF_AAC_DATA_FORMAT_ADTS);

	CU_ASSERT_EQUAL(count, ADEF_AAC_DATA_FORMAT_MAX);
}


static void test_aac_data_format_to_str(void)
{
	int count = 0;
	const char *value;

	value = adef_aac_data_format_to_str(-1);
	CU_ASSERT_STRING_EQUAL(value, "UNKNOWN");

	value = adef_aac_data_format_to_str(ADEF_AAC_DATA_FORMAT_UNKNOWN);
	count++;
	CU_ASSERT_STRING_EQUAL(value, "UNKNOWN");

	value = adef_aac_data_format_to_str(ADEF_AAC_DATA_FORMAT_RAW);
	count++;
	CU_ASSERT_STRING_EQUAL(value, "RAW");

	value = adef_aac_data_format_to_str(ADEF_AAC_DATA_FORMAT_ADIF);
	count++;
	CU_ASSERT_STRING_EQUAL(value, "ADIF");

	value = adef_aac_data_format_to_str(ADEF_AAC_DATA_FORMAT_ADTS);
	count++;
	CU_ASSERT_STRING_EQUAL(value, "ADTS");

	value = adef_aac_data_format_to_str(ADEF_AAC_DATA_FORMAT_MAX);
	CU_ASSERT_STRING_EQUAL(value, "UNKNOWN");

	value = adef_aac_data_format_to_str(ADEF_AAC_DATA_FORMAT_MAX + 1);
	CU_ASSERT_STRING_EQUAL(value, "UNKNOWN");

	CU_ASSERT_EQUAL(count, ADEF_AAC_DATA_FORMAT_MAX);
}


static void test_encoding_from_str(void)
{
	int count = 0;
	enum adef_encoding value;

	value = adef_encoding_from_str(NULL);
	CU_ASSERT_EQUAL(value, ADEF_ENCODING_UNKNOWN);

	value = adef_encoding_from_str("?");
	CU_ASSERT_EQUAL(value, ADEF_ENCODING_UNKNOWN);

	value = adef_encoding_from_str("abcde");
	CU_ASSERT_EQUAL(value, ADEF_ENCODING_UNKNOWN);

	value = adef_encoding_from_str("UNKNOWN");
	count++;
	CU_ASSERT_EQUAL(value, ADEF_ENCODING_UNKNOWN);

	value = adef_encoding_from_str("PCM");
	count++;
	CU_ASSERT_EQUAL(value, ADEF_ENCODING_PCM);

	value = adef_encoding_from_str("AAC_LC");
	count++;
	CU_ASSERT_EQUAL(value, ADEF_ENCODING_AAC_LC);

	CU_ASSERT_EQUAL(count, ADEF_ENCODING_MAX);
}


static void test_encoding_to_str(void)
{
	int count = 0;
	const char *value;

	value = adef_encoding_to_str(-1);
	CU_ASSERT_STRING_EQUAL(value, "UNKNOWN");

	value = adef_encoding_to_str(ADEF_ENCODING_UNKNOWN);
	count++;
	CU_ASSERT_STRING_EQUAL(value, "UNKNOWN");

	value = adef_encoding_to_str(ADEF_ENCODING_PCM);
	count++;
	CU_ASSERT_STRING_EQUAL(value, "PCM");

	value = adef_encoding_to_str(ADEF_ENCODING_AAC_LC);
	count++;
	CU_ASSERT_STRING_EQUAL(value, "AAC_LC");

	value = adef_encoding_to_str(ADEF_ENCODING_MAX);
	CU_ASSERT_STRING_EQUAL(value, "UNKNOWN");

	value = adef_encoding_to_str(ADEF_ENCODING_MAX + 1);
	CU_ASSERT_STRING_EQUAL(value, "UNKNOWN");

	CU_ASSERT_EQUAL(count, ADEF_ENCODING_MAX);
}


static void test_format_from_str(void)
{
	int ret;
	struct adef_format fmt;
	struct adef_format cmp_fmt = {0};

	ret = adef_format_from_str(NULL, NULL);
	CU_ASSERT_EQUAL(ret, -EINVAL);

	ret = adef_format_from_str(NULL, &fmt);
	CU_ASSERT_EQUAL(ret, -EINVAL);

	ret = adef_format_from_str("ABCDE", NULL);
	CU_ASSERT_EQUAL(ret, -EINVAL);

	ret = adef_format_from_str("ABCDE", &fmt);
	CU_ASSERT_EQUAL(ret, -EINVAL);

	ret = adef_format_from_str("A/B/C/D/E//", &fmt);
	CU_ASSERT_EQUAL(ret, -EINVAL);

	ret = adef_format_from_str("UNKNOWN/0/0/0/PLANAR/UNSIGNED/BE/UNKNOWN",
				   &fmt);
	CU_ASSERT_EQUAL(ret, 0);
	CU_ASSERT_TRUE(adef_format_cmp(&fmt, &cmp_fmt));

	cmp_fmt.encoding = ADEF_ENCODING_AAC_LC;
	cmp_fmt.channel_count = 1;
	cmp_fmt.bit_depth = 24;
	cmp_fmt.sample_rate = 44100;
	cmp_fmt.aac.data_format = ADEF_AAC_DATA_FORMAT_RAW;
	ret = adef_format_from_str("AAC_LC/1/24/44100/PLANAR/UNSIGNED/BE/RAW",
				   &fmt);
	CU_ASSERT_EQUAL(ret, 0);
	CU_ASSERT_TRUE(adef_format_cmp(&fmt, &cmp_fmt));

	cmp_fmt.encoding = ADEF_ENCODING_PCM;
	cmp_fmt.pcm.interleaved = true;
	cmp_fmt.pcm.signed_val = true;
	cmp_fmt.pcm.little_endian = true;
	cmp_fmt.aac.data_format = ADEF_AAC_DATA_FORMAT_UNKNOWN;
	ret = adef_format_from_str(
		"PCM/1/24/44100/INTERLEAVED/SIGNED/LE/UNKNOWN", &fmt);
	CU_ASSERT_EQUAL(ret, 0);
	CU_ASSERT_TRUE(adef_format_cmp(&fmt, &cmp_fmt));

	/* Known format */
	ret = adef_format_from_str("aac_lc_16b_44100hz_mono_raw", &fmt);
	CU_ASSERT_EQUAL(ret, 0);
	CU_ASSERT_TRUE(
		adef_format_cmp(&fmt, &adef_aac_lc_16b_44100hz_mono_raw));

	/* Known format */
	ret = adef_format_from_str("aac_lc_16b_48000hz_stereo_raw", &fmt);
	CU_ASSERT_EQUAL(ret, 0);
	CU_ASSERT_TRUE(
		adef_format_cmp(&fmt, &adef_aac_lc_16b_48000hz_stereo_raw));

	/* Known format */
	ret = adef_format_from_str("pcm_16b_44100hz_mono", &fmt);
	CU_ASSERT_EQUAL(ret, 0);
	CU_ASSERT_TRUE(adef_format_cmp(&fmt, &adef_pcm_16b_44100hz_mono));

	/* Known format */
	ret = adef_format_from_str("pcm_16b_48000hz_stereo", &fmt);
	CU_ASSERT_EQUAL(ret, 0);
	CU_ASSERT_TRUE(adef_format_cmp(&fmt, &adef_pcm_16b_48000hz_stereo));
}


static void test_format_to_str(void)
{
	char *value;
	struct adef_format fmt = {0};

	value = adef_format_to_str(NULL);
	CU_ASSERT_PTR_EQUAL(value, NULL);

	value = adef_format_to_str(&fmt);
	CU_ASSERT_STRING_EQUAL(value,
			       "UNKNOWN/0/0/0/PLANAR/UNSIGNED/BE/UNKNOWN");
	free(value);

	fmt.encoding = ADEF_ENCODING_AAC_LC;
	value = adef_format_to_str(&fmt);
	CU_ASSERT_STRING_EQUAL(value,
			       "AAC_LC/0/0/0/PLANAR/UNSIGNED/BE/UNKNOWN");
	free(value);

	fmt.channel_count = 1;
	value = adef_format_to_str(&fmt);
	CU_ASSERT_STRING_EQUAL(value,
			       "AAC_LC/1/0/0/PLANAR/UNSIGNED/BE/UNKNOWN");
	free(value);

	fmt.bit_depth = 16;
	value = adef_format_to_str(&fmt);
	CU_ASSERT_STRING_EQUAL(value,
			       "AAC_LC/1/16/0/PLANAR/UNSIGNED/BE/UNKNOWN");
	free(value);

	fmt.aac.data_format = ADEF_AAC_DATA_FORMAT_ADTS;
	value = adef_format_to_str(&fmt);
	CU_ASSERT_STRING_EQUAL(value, "AAC_LC/1/16/0/PLANAR/UNSIGNED/BE/ADTS");
	free(value);

	/* Known format */
	fmt.sample_rate = 44100;
	value = adef_format_to_str(&fmt);
	CU_ASSERT_STRING_EQUAL(value, "aac_lc_16b_44100hz_mono_adts");
	free(value);

	fmt.encoding = ADEF_ENCODING_PCM;
	value = adef_format_to_str(&fmt);
	CU_ASSERT_STRING_EQUAL(value, "PCM/1/16/44100/PLANAR/UNSIGNED/BE/ADTS");
	free(value);

	fmt.pcm.interleaved = true;
	value = adef_format_to_str(&fmt);
	CU_ASSERT_STRING_EQUAL(value,
			       "PCM/1/16/44100/INTERLEAVED/UNSIGNED/BE/ADTS");
	free(value);

	fmt.pcm.signed_val = true;
	value = adef_format_to_str(&fmt);
	CU_ASSERT_STRING_EQUAL(value,
			       "PCM/1/16/44100/INTERLEAVED/SIGNED/BE/ADTS");
	free(value);

	/* Known format */
	fmt.pcm.little_endian = true;
	value = adef_format_to_str(&fmt);
	CU_ASSERT_STRING_EQUAL(value, "pcm_16b_44100hz_mono");
	free(value);

	/* Known format */
	fmt.channel_count = 2;
	value = adef_format_to_str(&fmt);
	CU_ASSERT_STRING_EQUAL(value, "pcm_16b_44100hz_stereo");
	free(value);

	/* Known format */
	fmt.sample_rate = 96000;
	value = adef_format_to_str(&fmt);
	CU_ASSERT_STRING_EQUAL(value, "pcm_16b_96000hz_stereo");
	free(value);
}


CU_TestInfo g_adef_test_str[] = {
	{FN("aac-data-format-from-str"), &test_aac_data_format_from_str},
	{FN("aac-data-format-to-str"), &test_aac_data_format_to_str},
	{FN("encoding-from-str"), &test_encoding_from_str},
	{FN("encoding-to-str"), &test_encoding_to_str},
	{FN("format-from-str"), &test_format_from_str},
	{FN("format-to-str"), &test_format_to_str},

	CU_TEST_INFO_NULL,
};
