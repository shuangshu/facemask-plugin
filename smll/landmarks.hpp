/*
* Face Masks for SlOBS
* smll - streamlabs machine learning library
*
* Copyright (C) 2017 General Workings Inc
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
*/
#pragma once

#pragma warning( push )
#pragma warning( disable: 4127 )
#pragma warning( disable: 4201 )
#pragma warning( disable: 4456 )
#pragma warning( disable: 4458 )
#pragma warning( disable: 4459 )
#pragma warning( disable: 4505 )
#pragma warning( disable: 4267 )
#include <opencv2/opencv.hpp>
#pragma warning( pop )

#include <vector>
#include <bitset>


namespace smll {

	// 68 Facial Landmark Indices
	// 
	enum
	{
		JAW_1 = 0,
		JAW_2 = 1,
		JAW_3 = 2,
		JAW_4 = 3,
		JAW_5 = 4,
		JAW_6 = 5,
		JAW_7 = 6,
		JAW_8 = 7,
		JAW_9 = 8,
		JAW_10 = 9,
		JAW_11 = 10,
		JAW_12 = 11,
		JAW_13 = 12,
		JAW_14 = 13,
		JAW_15 = 14,
		JAW_16 = 15,
		JAW_17 = 16,

		EYEBROW_LEFT_1 = 17,
		EYEBROW_LEFT_2 = 18,
		EYEBROW_LEFT_3 = 19,
		EYEBROW_LEFT_4 = 20,
		EYEBROW_LEFT_5 = 21,

		EYEBROW_RIGHT_1 = 22,
		EYEBROW_RIGHT_2 = 23,
		EYEBROW_RIGHT_3 = 24,
		EYEBROW_RIGHT_4 = 25,
		EYEBROW_RIGHT_5 = 26,

		NOSE_1 = 27,
		NOSE_2 = 28,
		NOSE_3 = 29,
		NOSE_4 = 30,
		NOSE_5 = 31,
		NOSE_6 = 32,
		NOSE_7 = 33,
		NOSE_8 = 34,
		NOSE_9 = 35,

		EYE_LEFT_1 = 36,
		EYE_LEFT_2 = 37,
		EYE_LEFT_3 = 38,
		EYE_LEFT_4 = 39,
		EYE_LEFT_5 = 40,
		EYE_LEFT_6 = 41,

		EYE_RIGHT_1 = 42,
		EYE_RIGHT_2 = 43,
		EYE_RIGHT_3 = 44,
		EYE_RIGHT_4 = 45,
		EYE_RIGHT_5 = 46,
		EYE_RIGHT_6 = 47,

		MOUTH_OUTER_1 = 48,
		MOUTH_OUTER_2 = 49,
		MOUTH_OUTER_3 = 50,
		MOUTH_OUTER_4 = 51,
		MOUTH_OUTER_5 = 52,
		MOUTH_OUTER_6 = 53,
		MOUTH_OUTER_7 = 54,
		MOUTH_OUTER_8 = 55,
		MOUTH_OUTER_9 = 56,
		MOUTH_OUTER_10 = 57,
		MOUTH_OUTER_11 = 58,
		MOUTH_OUTER_12 = 59,

		MOUTH_INNER_1 = 60,
		MOUTH_INNER_2 = 61,
		MOUTH_INNER_3 = 62,
		MOUTH_INNER_4 = 63,
		MOUTH_INNER_5 = 64,
		MOUTH_INNER_6 = 65,
		MOUTH_INNER_7 = 66,
		MOUTH_INNER_8 = 67,

		// Here ends the detected 68 landmarks
		NUM_FACIAL_LANDMARKS = 68,

		// And here begins the extra ones

		// Extra 11 head points
		HEAD_1 = 68,
		HEAD_2 = 69,
		HEAD_3 = 70,
		HEAD_4 = 71,
		HEAD_5 = 72,
		HEAD_6 = 73,
		HEAD_7 = 74,
		HEAD_8 = 75,
		HEAD_9 = 76,
		HEAD_10 = 77,
		HEAD_11 = 78,

		// Here ends the 79 morph landmarks
		NUM_MORPH_LANDMARKS = 79,

		// And even more head points
		// - we use these to get a nice set
		//   of points in 2D for the 11 head 
		//   points above
		HEAD_EXTRA_1 = 79,
		HEAD_EXTRA_2 = 80,
		HEAD_EXTRA_3 = 81,
		HEAD_EXTRA_4 = 82,
		HEAD_EXTRA_5 = 83,
		HEAD_EXTRA_6 = 84,
		HEAD_EXTRA_7 = 85,
		HEAD_EXTRA_8 = 86,
		HEAD_EXTRA_9 = 87,
		HEAD_EXTRA_10 = 88,
		HEAD_EXTRA_11 = 89,
		HEAD_EXTRA_12 = 90,
		HEAD_EXTRA_13 = 91,
		HEAD_EXTRA_14 = 92,
		HEAD_EXTRA_15 = 93,

		// The whole sha-bang
		NUM_LANDMARKS = 94,

		// for convenience
		NOSE_TIP = NOSE_4,
		EYE_CENTER = NOSE_1,
		CHIN = JAW_9,
		LEFT_TEMPLE = JAW_1,
		RIGHT_TEMPLE = JAW_17,
		LEFT_INNER_EYE_CORNER = EYE_LEFT_4,
		LEFT_OUTER_EYE_CORNER = EYE_LEFT_1,
		RIGHT_INNER_EYE_CORNER = EYE_RIGHT_1,
		RIGHT_OUTER_EYE_CORNER = EYE_RIGHT_4,
		LEFT_MOUTH_CORNER = MOUTH_OUTER_1,
		RIGHT_MOUTH_CORNER = MOUTH_OUTER_7,
	};


	// access to 3D landmark points
	std::vector<cv::Point3d>&	GetLandmarkPoints();
	std::vector<cv::Point3d>	GetLandmarkPoints(const std::vector<int>& indices);
	cv::Point3d					GetLandmarkPoint(int which);

	// FaceContour: contour definitions
	// - this is used to define segments of landmark points
	//   for smoothing
	// - most are sequential with a start/end index
	// - some (like the eyes and mouth) include an extra index
	//   at the end, so I added last index 
	//
	typedef std::bitset<NUM_FACIAL_LANDMARKS>	LandmarkBitmask;
	struct FaceContour {
		std::vector<int>	indices;
		LandmarkBitmask		bitmask;

		FaceContour(const std::vector<int>& indices);
	};

	enum FaceContourID {
		FACE_CONTOUR_INVALID = -1,
		FACE_CONTOUR_CHIN = 0,
		FACE_CONTOUR_EYEBROW_LEFT,
		FACE_CONTOUR_EYEBROW_RIGHT,
		FACE_CONTOUR_NOSE_BRIDGE,
		FACE_CONTOUR_NOSE_BOTTOM,
		FACE_CONTOUR_EYE_LEFT_TOP,
		FACE_CONTOUR_EYE_LEFT_BOTTOM,
		FACE_CONTOUR_EYE_RIGHT_TOP,
		FACE_CONTOUR_EYE_RIGHT_BOTTOM,
		FACE_CONTOUR_MOUTH_OUTER_TOP_LEFT,
		FACE_CONTOUR_MOUTH_OUTER_TOP_RIGHT,
		FACE_CONTOUR_MOUTH_OUTER_BOTTOM,
		FACE_CONTOUR_MOUTH_INNER_TOP,
		FACE_CONTOUR_MOUTH_INNER_BOTTOM,

		NUM_FACE_CONTOURS
	};

	// Access to contours
	std::vector<FaceContour>&	GetFaceContours();
	const FaceContour&			GetFaceContour(FaceContourID which);

	// FaceArea : triangle area definitions
	// - some of the areas, like the background, do not have any 
	//   landmark points that define them.
	struct FaceArea {
		std::vector<int>	indices;
		LandmarkBitmask		bitmask;

		enum BoolOp {
			BOOLOP_ANY,
			BOOLOP_ALL,
			BOOLOP_NOT_ALL,
		};
		BoolOp				operation;

		FaceArea(const std::vector<int>& indices, BoolOp op);
	};

	// Face Area ids
	// note: these are calculated, in order, using the
	//       bool operations defined for the area.
	enum FaceAreaID {
		FACE_AREA_INVALID = -1,
		FACE_AREA_EYE_LEFT = 0,
		FACE_AREA_EYE_RIGHT,
		FACE_AREA_MOUTH_HOLE,
		FACE_AREA_MOUTH_LIPS,
		FACE_AREA_MOUTH,		// HOLE + LIPS
		FACE_AREA_BACKGROUND,
		FACE_AREA_FACE,
		FACE_AREA_EVERYTHING,

		NUM_FACE_AREAS
	};

	// Access to areas
	std::vector<FaceArea>&	GetFaceAreas();
	const FaceArea&			GetFaceArea(FaceAreaID which);

}