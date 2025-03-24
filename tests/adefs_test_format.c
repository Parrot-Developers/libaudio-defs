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


static void test_is_format_valid(void)
{
	bool ret;
	struct adef_format fmt = {0};

	ret = adef_is_format_valid(NULL);
	CU_ASSERT_FALSE(ret);

	fmt.encoding = ADEF_ENCODING_MAX;

	ret = adef_is_format_valid(&fmt);
	CU_ASSERT_FALSE(ret);

	fmt.encoding = ADEF_ENCODING_UNKNOWN;
	ret = adef_is_format_valid(&fmt);
	CU_ASSERT_FALSE(ret);

	fmt.encoding = ADEF_ENCODING_PCM;
	ret = adef_is_format_valid(&fmt);
	CU_ASSERT_FALSE(ret);

	fmt.channel_count = 1;
	ret = adef_is_format_valid(&fmt);
	CU_ASSERT_FALSE(ret);

	fmt.bit_depth = 8;
	ret = adef_is_format_valid(&fmt);
	CU_ASSERT_FALSE(ret);

	fmt.sample_rate = 44100;
	ret = adef_is_format_valid(&fmt);
	CU_ASSERT_TRUE(ret);

	fmt.encoding = ADEF_ENCODING_AAC_LC;
	ret = adef_is_format_valid(&fmt);
	CU_ASSERT_FALSE(ret);

	fmt.aac.data_format = ADEF_AAC_DATA_FORMAT_RAW;
	ret = adef_is_format_valid(&fmt);
	CU_ASSERT_TRUE(ret);

	fmt.aac.data_format = ADEF_AAC_DATA_FORMAT_ADTS;
	ret = adef_is_format_valid(&fmt);
	CU_ASSERT_TRUE(ret);
}


static void test_format_cmp(void)
{
	bool ret;
	struct adef_format fmt1 = {0};
	struct adef_format fmt2 = {0};

	ret = adef_format_cmp(NULL, NULL);
	CU_ASSERT_TRUE(ret);

	ret = adef_format_cmp(&fmt1, NULL);
	CU_ASSERT_FALSE(ret);

	ret = adef_format_cmp(NULL, &fmt2);
	CU_ASSERT_FALSE(ret);

	ret = adef_format_cmp(&fmt1, &fmt2);
	CU_ASSERT_TRUE(ret);

	/* PCM checks */

	fmt1 = fmt2 = adef_pcm_16b_48000hz_stereo;

	ret = adef_format_cmp(&fmt1, &fmt2);
	CU_ASSERT_TRUE(ret);

	/* Check that we don't care about AAA_LC when encoding is PCM */
	fmt1.aac.data_format = ADEF_AAC_DATA_FORMAT_ADTS;
	fmt2.aac.data_format = ADEF_AAC_DATA_FORMAT_UNKNOWN;

	ret = adef_format_cmp(&fmt1, &fmt2);
	CU_ASSERT_TRUE(ret);

	fmt2.pcm.interleaved = false;

	ret = adef_format_cmp(&fmt1, &fmt2);
	CU_ASSERT_FALSE(ret);

	/* AAC_LC checks */

	fmt1 = fmt2 = adef_aac_lc_16b_48000hz_stereo_raw;

	ret = adef_format_cmp(&fmt1, &fmt2);
	CU_ASSERT_TRUE(ret);

	/* Check that we don't care about PCM when encoding is AAC_LC */
	fmt1.pcm.interleaved = true;
	fmt1.pcm.signed_val = true;
	fmt1.pcm.little_endian = true;

	fmt2.pcm.interleaved = false;
	fmt2.pcm.signed_val = false;
	fmt2.pcm.little_endian = false;

	ret = adef_format_cmp(&fmt1, &fmt2);
	CU_ASSERT_TRUE(ret);

	fmt2.aac.data_format = ADEF_AAC_DATA_FORMAT_ADTS;

	ret = adef_format_cmp(&fmt1, &fmt2);
	CU_ASSERT_FALSE(ret);

	ret = adef_format_cmp(&adef_aac_lc_16b_48000hz_stereo_raw,
			      &adef_aac_lc_16b_48000hz_stereo_raw);
	CU_ASSERT_TRUE(ret);

	ret = adef_format_cmp(&adef_aac_lc_16b_48000hz_stereo_raw,
			      &adef_aac_lc_16b_48000hz_stereo_adts);
	CU_ASSERT_FALSE(ret);

	ret = adef_format_cmp(&adef_aac_lc_16b_48000hz_stereo_raw,
			      &adef_aac_lc_16b_48000hz_mono_raw);
	CU_ASSERT_FALSE(ret);

	ret = adef_format_cmp(&adef_aac_lc_16b_48000hz_stereo_raw,
			      &adef_aac_lc_16b_44100hz_stereo_adts);
	CU_ASSERT_FALSE(ret);

	ret = adef_format_cmp(&adef_aac_lc_16b_48000hz_stereo_raw,
			      &adef_pcm_16b_48000hz_stereo);
	CU_ASSERT_FALSE(ret);

	ret = adef_format_cmp(&adef_pcm_16b_48000hz_stereo,
			      &adef_pcm_16b_48000hz_stereo);
	CU_ASSERT_TRUE(ret);
}


static void test_format_intersect(void)
{
	bool ret;
	size_t i;
	struct adef_format fmt = {0};
	struct adef_format supported_formats_aac_mono[3];
	struct adef_format supported_formats_aac_stereo[3];
	struct adef_format supported_formats_pcm[4];
	i = 0;
	supported_formats_aac_mono[i++] = adef_aac_lc_16b_44100hz_mono_raw;
	supported_formats_aac_mono[i++] = adef_aac_lc_16b_48000hz_mono_raw;
	supported_formats_aac_mono[i++] = adef_aac_lc_16b_64000hz_mono_raw;
	i = 0;
	supported_formats_aac_stereo[i++] = adef_aac_lc_16b_44100hz_stereo_adts;
	supported_formats_aac_stereo[i++] = adef_aac_lc_16b_48000hz_stereo_adts;
	supported_formats_aac_stereo[i++] = adef_aac_lc_16b_64000hz_stereo_adts;
	i = 0;
	supported_formats_pcm[i++] = adef_pcm_16b_44100hz_mono;
	supported_formats_pcm[i++] = adef_pcm_16b_44100hz_stereo;
	supported_formats_pcm[i++] = adef_pcm_16b_48000hz_mono;
	supported_formats_pcm[i++] = adef_pcm_16b_48000hz_stereo;

	ret = adef_format_intersect(NULL, NULL, 0);
	CU_ASSERT_FALSE(ret);

	ret = adef_format_intersect(NULL, NULL, 10);
	CU_ASSERT_FALSE(ret);

	ret = adef_format_intersect(&fmt, NULL, 0);
	CU_ASSERT_FALSE(ret);

	ret = adef_format_intersect(&fmt, supported_formats_aac_mono, 0);
	CU_ASSERT_FALSE(ret);

	ret = adef_format_intersect(
		&fmt,
		supported_formats_aac_mono,
		ADEF_ARRAY_SIZE(supported_formats_aac_mono));
	CU_ASSERT_FALSE(ret);

	/* Mono */
	for (i = 0; i < ADEF_ARRAY_SIZE(supported_formats_aac_mono); i++) {
		fmt = supported_formats_aac_mono[i];
		ret = adef_format_intersect(
			&fmt,
			supported_formats_aac_mono,
			ADEF_ARRAY_SIZE(supported_formats_aac_mono));
		CU_ASSERT_TRUE(ret);
		ret = adef_format_intersect(
			&fmt,
			supported_formats_aac_stereo,
			ADEF_ARRAY_SIZE(supported_formats_aac_stereo));
		CU_ASSERT_FALSE(ret);
		ret = adef_format_intersect(
			&fmt,
			supported_formats_pcm,
			ADEF_ARRAY_SIZE(supported_formats_pcm));
		CU_ASSERT_FALSE(ret);
	}

	/* Stereo */
	for (i = 0; i < ADEF_ARRAY_SIZE(supported_formats_aac_stereo); i++) {
		fmt = supported_formats_aac_stereo[i];
		ret = adef_format_intersect(
			&fmt,
			supported_formats_aac_mono,
			ADEF_ARRAY_SIZE(supported_formats_aac_mono));
		CU_ASSERT_FALSE(ret);
		ret = adef_format_intersect(
			&fmt,
			supported_formats_aac_stereo,
			ADEF_ARRAY_SIZE(supported_formats_aac_stereo));
		CU_ASSERT_TRUE(ret);
		ret = adef_format_intersect(
			&fmt,
			supported_formats_pcm,
			ADEF_ARRAY_SIZE(supported_formats_pcm));
		CU_ASSERT_FALSE(ret);
	}

	/* PCM/AAC */
	for (i = 0; i < ADEF_ARRAY_SIZE(supported_formats_pcm); i++) {
		fmt = supported_formats_pcm[i];
		ret = adef_format_intersect(
			&fmt,
			supported_formats_aac_mono,
			ADEF_ARRAY_SIZE(supported_formats_aac_mono));
		CU_ASSERT_FALSE(ret);
		ret = adef_format_intersect(
			&fmt,
			supported_formats_aac_stereo,
			ADEF_ARRAY_SIZE(supported_formats_aac_stereo));
		CU_ASSERT_FALSE(ret);
		ret = adef_format_intersect(
			&fmt,
			supported_formats_pcm,
			ADEF_ARRAY_SIZE(supported_formats_pcm));
		CU_ASSERT_TRUE(ret);
	}
}


CU_TestInfo g_adef_test_format[] = {
	{FN("is-format-valid"), &test_is_format_valid},
	{FN("format-cmp"), &test_format_cmp},
	{FN("format-intersect"), &test_format_intersect},

	CU_TEST_INFO_NULL,
};
