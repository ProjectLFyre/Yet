/**
 *	***** BEGIN LICENSE BLOCK *****
 *
 *	Copyright 2017 Project LFyre
 *
 *	Licensed under the Apache License, Version 2.0 (the "Apache License")
 *	with the following modification; you may not use this file except in
 *	compliance with the Apache License and the following modification to it:
 *	Section 6. Trademarks. is deleted and replaced with:
 *
 *	6. Trademarks. This License does not grant permission to use the trade
 *		names, trademarks, service marks, or product names of the Licensor
 *		and its affiliates, except as required to comply with Section 4(c) of
 *		the License and to reproduce the content of the NOTICE file.
 *
 *	You may obtain a copy of the Apache License at
 *
 *		http://www.apache.org/licenses/LICENSE-2.0
 *
 *	Unless required by applicable law or agreed to in writing, software
 *	distributed under the Apache License with the above modification is
 *	distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 *	KIND, either express or implied. See the Apache License for the specific
 *	language governing permissions and limitations under the Apache License.
 *
 *	****** END LICENSE BLOCK ******
 *
 *	*****************************************************************
 *
 *	******* BEGIN FILE DESCRIPTION *******
 *
 *	This file is the main source file for Yet. In fact, as of right now, it is
 *	the only source file.
 *
 *	******** END FILE DESCRIPTION ********
 */

#include <time.h>

#include <yet.h>

// This function was conveniently lifted from
// https://www.guyrutenberg.com/2007/09/22/profiling-code-using-clock_gettime/
TimeSpec yet_ts_diff(TimeSpec end, TimeSpec start) {

	TimeSpec temp;

	if ((end.tv_nsec - start.tv_nsec) < 0) {
		temp.tv_sec = end.tv_sec - start.tv_sec - 1;
		temp.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
	}
	else {
		temp.tv_sec = end.tv_sec - start.tv_sec;
		temp.tv_nsec = end.tv_nsec - start.tv_nsec;
	}

	return temp;
}

TimeSpec yet_ts_add(TimeSpec ts1, TimeSpec ts2) {

	TimeSpec temp;

	if ((ts1.tv_nsec + ts2.tv_nsec) > 1000000000) {
		temp.tv_sec = ts1.tv_sec + ts2.tv_sec + 1;
		temp.tv_nsec = ts1.tv_nsec + ts2.tv_nsec - 1000000000;
	}
	else {
		temp.tv_sec = ts1.tv_sec + ts2.tv_sec;
		temp.tv_nsec = ts1.tv_nsec + ts2.tv_nsec;
	}

	return temp;
}

float yet_ts_float(TimeSpec ts) {
	return (float) ts.tv_sec + (float) ts.tv_nsec * 1E-9;
}

TimeSpec yet_timer_start() {

	TimeSpec start;

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);

	return start;
}

TimeSpec yet_timer_stop(TimeSpec start) {

	TimeSpec end;

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
	return yet_ts_diff(end, start);
}

