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
#include "landmarks.hpp"

namespace smll {

	static std::vector<cv::Point3f>	g_landmark_points;
	static std::vector<cv::Point3f>	g_head_points;
	static std::vector<FaceContour>	g_face_contours;
	static std::vector<FaceArea>	g_face_areas;

	std::vector<cv::Point3f>&	GetLandmarkPoints() {
		if (g_landmark_points.size() == 0) {
			/* This code was generated using the landmarks.ma Maya file (in the tools folder), and the
			   following MEL code:

				string $landmarks[] = `ls -transforms "landmark*"`;
				string $obj;
				float $scale_x = 1;
				float $scale_y = -1;
				float $scale_z = -1;
				print("\n\n\n\n\n\n");
				for($obj in $landmarks) {
					float $pos_x = `getAttr ($obj + ".translateX")`;
					float $pos_y = `getAttr ($obj + ".translateY")`;
					float $pos_z = `getAttr ($obj + ".translateZ")`;
					$pos_x = $pos_x * $scale_x;
					$pos_y = $pos_y * $scale_y;
					$pos_z = $pos_z * $scale_z;
					print("g_landmark_points.push_back(cv::Point3f(");
					if ($pos_x == 0)
						print($pos_x + ".0f");
					else
						print($pos_x + "f");
					print(",");
					if ($pos_y == 0)
						print($pos_y + ".0f");
					else
						print($pos_y + "f");
					print(",");
					if ($pos_z == 0)
						print($pos_z + ".0f");
					else
						print($pos_z + "f");
					print("));  //" + $obj + "\n");
				}
			*/
			g_landmark_points.push_back(cv::Point3f(-3.483503406f, -1.875f, 6.257826823f));  //landmark0
			g_landmark_points.push_back(cv::Point3f(-3.359597141f, -0.8238194924f, 6.268504316f));  //landmark1
			g_landmark_points.push_back(cv::Point3f(-3.29341073f, -0.0f, 6.125560005f));  //landmark2
			g_landmark_points.push_back(cv::Point3f(-3.029556606f, 0.8898986532f, 5.949513509f));  //landmark3
			g_landmark_points.push_back(cv::Point3f(-2.807839534f, 1.718491903f, 5.409257409f));  //landmark4
			g_landmark_points.push_back(cv::Point3f(-2.438720413f, 2.560530432f, 4.32768332f));  //landmark5
			g_landmark_points.push_back(cv::Point3f(-1.862063832f, 3.278654632f, 3.281386081f));  //landmark6
			g_landmark_points.push_back(cv::Point3f(-0.9883951084f, 3.766558606f, 2.330544137f));  //landmark7
			g_landmark_points.push_back(cv::Point3f(0.0f, 3.841393622f, 1.83587187f));  //landmark8
			g_landmark_points.push_back(cv::Point3f(0.9883951084f, 3.766558606f, 2.330544137f));  //landmark9
			g_landmark_points.push_back(cv::Point3f(1.862063832f, 3.278654632f, 3.281386081f));  //landmark10
			g_landmark_points.push_back(cv::Point3f(2.438720413f, 2.560530432f, 4.32768332f));  //landmark11
			g_landmark_points.push_back(cv::Point3f(2.807839534f, 1.718491903f, 5.409257409f));  //landmark12
			g_landmark_points.push_back(cv::Point3f(3.029556606f, 0.8898986532f, 5.949513509f));  //landmark13
			g_landmark_points.push_back(cv::Point3f(3.29341073f, -0.0f, 6.125560005f));  //landmark14
			g_landmark_points.push_back(cv::Point3f(3.359597141f, -0.8238194924f, 6.268504316f));  //landmark15
			g_landmark_points.push_back(cv::Point3f(3.483503406f, -1.875f, 6.257826823f));  //landmark16
			g_landmark_points.push_back(cv::Point3f(-2.643977f, -2.489205626f, 2.200659814f));  //landmark17
			g_landmark_points.push_back(cv::Point3f(-2.24022692f, -2.81816975f, 1.764281101f));  //landmark18
			g_landmark_points.push_back(cv::Point3f(-1.665074397f, -3.058339137f, 1.403462785f));  //landmark19
			g_landmark_points.push_back(cv::Point3f(-0.9792975326f, -2.992586771f, 1.351679383f));  //landmark20
			g_landmark_points.push_back(cv::Point3f(-0.414417114f, -2.683012037f, 1.193536808f));  //landmark21
			g_landmark_points.push_back(cv::Point3f(0.414417114f, -2.683012037f, 1.193536808f));  //landmark22
			g_landmark_points.push_back(cv::Point3f(0.9792975326f, -2.992586771f, 1.351679383f));  //landmark23
			g_landmark_points.push_back(cv::Point3f(1.665074397f, -3.058339137f, 1.403462785f));  //landmark24
			g_landmark_points.push_back(cv::Point3f(2.24022692f, -2.81816975f, 1.764281101f));  //landmark25
			g_landmark_points.push_back(cv::Point3f(2.643977f, -2.489205626f, 2.200659814f));  //landmark26
			g_landmark_points.push_back(cv::Point3f(0.0f, -1.83012447f, 1.2548274f));  //landmark27
			g_landmark_points.push_back(cv::Point3f(0.0f, -1.146743411f, 0.7348212125f));  //landmark28
			g_landmark_points.push_back(cv::Point3f(0.0f, -0.5915072192f, 0.3310879765f));  //landmark29
			g_landmark_points.push_back(cv::Point3f(0.0f, -0.0f, -0.0f));  //landmark30
			g_landmark_points.push_back(cv::Point3f(-0.5078303403f, 0.4785699918f, 1.063397473f));  //landmark31
			g_landmark_points.push_back(cv::Point3f(-0.3045344039f, 0.6169094843f, 0.95f));  //landmark32
			g_landmark_points.push_back(cv::Point3f(0.0f, 0.7203533372f, 0.8644320921f));  //landmark33
			g_landmark_points.push_back(cv::Point3f(0.3045344039f, 0.6169094843f, 0.95f));  //landmark34
			g_landmark_points.push_back(cv::Point3f(0.5078303403f, 0.4785699918f, 1.063397473f));  //landmark35
			g_landmark_points.push_back(cv::Point3f(-2.379f, -1.8f, 2.442238431f));  //landmark36
			g_landmark_points.push_back(cv::Point3f(-2.055f, -2.1f, 1.956067275f));  //landmark37
			g_landmark_points.push_back(cv::Point3f(-1.4f, -2.1f, 1.822647331f));  //landmark38
			g_landmark_points.push_back(cv::Point3f(-0.9321320395f, -1.647759215f, 1.985483325f));  //landmark39
			g_landmark_points.push_back(cv::Point3f(-1.4f, -1.51f, 1.952295464f));  //landmark40
			g_landmark_points.push_back(cv::Point3f(-2.04f, -1.51f, 2.108500226f));  //landmark41
			g_landmark_points.push_back(cv::Point3f(0.9321320395f, -1.647759215f, 1.985483325f));  //landmark42
			g_landmark_points.push_back(cv::Point3f(1.4f, -2.1f, 1.822647331f));  //landmark43
			g_landmark_points.push_back(cv::Point3f(2.055f, -2.1f, 1.956067275f));  //landmark44
			g_landmark_points.push_back(cv::Point3f(2.379f, -1.8f, 2.442238431f));  //landmark45
			g_landmark_points.push_back(cv::Point3f(2.04f, -1.51f, 2.108500226f));  //landmark46
			g_landmark_points.push_back(cv::Point3f(1.4f, -1.51f, 1.952295464f));  //landmark47
			g_landmark_points.push_back(cv::Point3f(-1.413398424f, 1.759402258f, 1.81786896f));  //landmark48
			g_landmark_points.push_back(cv::Point3f(-0.8837097315f, 1.555559414f, 1.408546073f));  //landmark49
			g_landmark_points.push_back(cv::Point3f(-0.3800736479f, 1.45738193f, 1.120382417f));  //landmark50
			g_landmark_points.push_back(cv::Point3f(0.0f, 1.516837487f, 1.022306071f));  //landmark51
			g_landmark_points.push_back(cv::Point3f(0.3800736479f, 1.45738193f, 1.120382417f));  //landmark52
			g_landmark_points.push_back(cv::Point3f(0.8837097315f, 1.555559414f, 1.408546073f));  //landmark53
			g_landmark_points.push_back(cv::Point3f(1.413398424f, 1.759402258f, 1.81786896f));  //landmark54
			g_landmark_points.push_back(cv::Point3f(0.9568543383f, 2.133360108f, 1.618440108f));  //landmark55
			g_landmark_points.push_back(cv::Point3f(0.4722337603f, 2.318487353f, 1.297366611f));  //landmark56
			g_landmark_points.push_back(cv::Point3f(0.0f, 2.432607974f, 1.286433896f));  //landmark57
			g_landmark_points.push_back(cv::Point3f(-0.4722337603f, 2.318487353f, 1.297366611f));  //landmark58
			g_landmark_points.push_back(cv::Point3f(-0.9568543383f, 2.133360108f, 1.618440108f));  //landmark59
			g_landmark_points.push_back(cv::Point3f(-0.866954231f, 1.863486992f, 1.647583553f));  //landmark60
			g_landmark_points.push_back(cv::Point3f(-0.4548429381f, 1.831590824f, 1.401979217f));  //landmark61
			g_landmark_points.push_back(cv::Point3f(0.0f, 1.830228784f, 1.150778816f));  //landmark62
			g_landmark_points.push_back(cv::Point3f(0.4548429381f, 1.831590824f, 1.401979217f));  //landmark63
			g_landmark_points.push_back(cv::Point3f(0.866954231f, 1.863486992f, 1.647583553f));  //landmark64
			g_landmark_points.push_back(cv::Point3f(0.4486628082f, 1.952122154f, 1.38448003f));  //landmark65
			g_landmark_points.push_back(cv::Point3f(0.0f, 1.984611663f, 1.157622018f));  //landmark66
			g_landmark_points.push_back(cv::Point3f(-0.4486628082f, 1.952122154f, 1.38448003f));  //landmark67
			g_landmark_points.push_back(cv::Point3f(-3.491717695f, -2.961992051f, 6.153366279f));  //landmark68
			g_landmark_points.push_back(cv::Point3f(-3.425201827f, -4.111108219f, 6.156496982f));  //landmark69
			g_landmark_points.push_back(cv::Point3f(-3.073340494f, -5.372414472f, 6.173058038f));  //landmark70
			g_landmark_points.push_back(cv::Point3f(-2.357762412f, -6.51628002f, 6.206738151f));  //landmark71
			g_landmark_points.push_back(cv::Point3f(-1.267405458f, -7.183477499f, 6.258057979f));  //landmark72
			g_landmark_points.push_back(cv::Point3f(0.0f, -7.398334079f, 6.239257358f));  //landmark73
			g_landmark_points.push_back(cv::Point3f(1.267405458f, -7.183477499f, 6.258057979f));  //landmark74
			g_landmark_points.push_back(cv::Point3f(2.357762412f, -6.51628002f, 6.206738151f));  //landmark75
			g_landmark_points.push_back(cv::Point3f(3.073340494f, -5.372414472f, 6.173058038f));  //landmark76
			g_landmark_points.push_back(cv::Point3f(3.425201827f, -4.111108219f, 6.156496982f));  //landmark77
			g_landmark_points.push_back(cv::Point3f(3.491717695f, -2.961992051f, 6.153366279f));  //landmark78
			g_landmark_points.push_back(cv::Point3f(-2.700395143f, -3.384052868f, 2.25961197f));  //landmark79
			g_landmark_points.push_back(cv::Point3f(0.0f, -3.450691564f, 1.237835259f));  //landmark80
			g_landmark_points.push_back(cv::Point3f(2.700395143f, -3.384052868f, 2.25961197f));  //landmark81
			g_landmark_points.push_back(cv::Point3f(-2.608838683f, -4.392022168f, 2.73385297f));  //landmark82
			g_landmark_points.push_back(cv::Point3f(0.0f, -4.599807731f, 1.511702317f));  //landmark83
			g_landmark_points.push_back(cv::Point3f(2.608838683f, -4.392022168f, 2.73385297f));  //landmark84
			g_landmark_points.push_back(cv::Point3f(-2.103720942f, -5.614363806f, 3.228975536f));  //landmark85
			g_landmark_points.push_back(cv::Point3f(0.0f, -5.670252201f, 2.298449554f));  //landmark86
			g_landmark_points.push_back(cv::Point3f(2.103720942f, -5.614363806f, 3.228975536f));  //landmark87
			g_landmark_points.push_back(cv::Point3f(-1.685508739f, -6.51628002f, 4.34258624f));  //landmark88
			g_landmark_points.push_back(cv::Point3f(0.0f, -6.512242897f, 3.42293761f));  //landmark89
			g_landmark_points.push_back(cv::Point3f(1.685508739f, -6.51628002f, 4.34258624f));  //landmark90
			g_landmark_points.push_back(cv::Point3f(-0.9454320571f, -7.183477499f, 5.25124897f));  //landmark91
			g_landmark_points.push_back(cv::Point3f(-8.881784197e-016f, -7.151991675f, 4.796727772f));  //landmark92
			g_landmark_points.push_back(cv::Point3f(0.9454320571f, -7.183477499f, 5.25124897f));  //landmark93
		}
		return g_landmark_points;
	}

	std::vector<cv::Point3f> GetLandmarkPoints(const std::vector<int>& indices)	{
		GetLandmarkPoints();
		std::vector<cv::Point3f> points;
		for (int i = 0; i < indices.size(); i++) {
			points.push_back(g_landmark_points[indices[i]]);
		}
		return points;
	}

	cv::Point3f					GetLandmarkPoint(int which) {
		GetLandmarkPoints();
		return g_landmark_points[which];
	}

	std::vector<cv::Point3f>&	GetAllHeadPoints() {
		if (g_head_points.size() == 0) {
			GetLandmarkPoints();
			g_head_points.assign(g_landmark_points.begin() + HEAD_1, g_landmark_points.end());
		}
		return g_head_points;
	}


	FaceContour::FaceContour(const std::vector<int>& indz) {
		indices = indz;
		bitmask.reset();
		for (auto i : indices) {
			bitmask.set(i);
		}
	}

	std::vector<FaceContour>&	GetFaceContours() {
		if (g_face_contours.size() == 0) {

			// FACE_CONTOUR_CHIN
			g_face_contours.emplace_back(FaceContour({ JAW_1, JAW_2, JAW_3,
				JAW_4, JAW_5, JAW_6, JAW_7, JAW_8, JAW_9, JAW_10,
				JAW_11, JAW_12, JAW_13, JAW_14, JAW_15, JAW_16, JAW_17 }));
			// FACE_CONTOUR_EYEBROW_LEFT
			g_face_contours.emplace_back(FaceContour({ EYEBROW_LEFT_1,
				EYEBROW_LEFT_2, EYEBROW_LEFT_3, EYEBROW_LEFT_4, EYEBROW_LEFT_5 }));
			// FACE_CONTOUR_EYEBROW_RIGHT
			g_face_contours.emplace_back(FaceContour({ EYEBROW_RIGHT_1,
				EYEBROW_RIGHT_2, EYEBROW_RIGHT_3, EYEBROW_RIGHT_4, EYEBROW_RIGHT_5 }));
			// FACE_CONTOUR_NOSE_BRIDGE
			g_face_contours.emplace_back(FaceContour({ NOSE_1, NOSE_2, NOSE_3, NOSE_4 }));
			// FACE_CONTOUR_NOSE_BOTTOM
			g_face_contours.emplace_back(FaceContour({ NOSE_5, NOSE_6, NOSE_7, NOSE_8, NOSE_9 }));
			// FACE_CONTOUR_EYE_LEFT_TOP
			g_face_contours.emplace_back(FaceContour({ EYE_LEFT_1, EYE_LEFT_2, EYE_LEFT_3, EYE_LEFT_4 }));
			// FACE_CONTOUR_EYE_LEFT_BOTTOM
			g_face_contours.emplace_back(FaceContour({ EYE_LEFT_4, EYE_LEFT_5, EYE_LEFT_6, EYE_LEFT_1 }));
			// FACE_CONTOUR_EYE_RIGHT_TOP
			g_face_contours.emplace_back(FaceContour({ EYE_RIGHT_1, EYE_RIGHT_2, EYE_RIGHT_3, EYE_RIGHT_4 }));
			// FACE_CONTOUR_EYE_RIGHT_BOTTOM
			g_face_contours.emplace_back(FaceContour({ EYE_RIGHT_4, EYE_RIGHT_5, EYE_RIGHT_6, EYE_RIGHT_1 }));
			// FACE_CONTOUR_MOUTH_OUTER_TOP_LEFT
			g_face_contours.emplace_back(FaceContour({ MOUTH_OUTER_1, MOUTH_OUTER_2, MOUTH_OUTER_3 }));
			// FACE_CONTOUR_MOUTH_OUTER_TOP_RIGHT
			g_face_contours.emplace_back(FaceContour({ MOUTH_OUTER_5, MOUTH_OUTER_6, MOUTH_OUTER_7 }));
			// FACE_CONTOUR_MOUTH_OUTER_BOTTOM
			g_face_contours.emplace_back(FaceContour({ MOUTH_OUTER_7, MOUTH_OUTER_8, MOUTH_OUTER_9,
				MOUTH_OUTER_10, MOUTH_OUTER_11, MOUTH_OUTER_12, MOUTH_OUTER_1 }));
			// FACE_CONTOUR_MOUTH_INNER_TOP
			g_face_contours.emplace_back(FaceContour({ MOUTH_INNER_1, MOUTH_INNER_2, MOUTH_INNER_3,
				MOUTH_INNER_4, MOUTH_INNER_5 }));
			// FACE_CONTOUR_MOUTH_INNER_BOTTOM
			g_face_contours.emplace_back(FaceContour({ MOUTH_INNER_5, MOUTH_INNER_6, MOUTH_INNER_7,
				MOUTH_INNER_8, MOUTH_INNER_1 }));
			// FACE_CONTOUR_HEAD
			g_face_contours.emplace_back(FaceContour({ JAW_1, HEAD_1, HEAD_2, HEAD_3, HEAD_4,
				HEAD_5, HEAD_6, HEAD_7, HEAD_8, HEAD_9, HEAD_10, HEAD_11, JAW_17 }));
		}
		return g_face_contours;
	}

	const FaceContour&	GetFaceContour(FaceContourID which) {
		GetFaceContours();
		return g_face_contours[which];
	}



	FaceArea::FaceArea(const std::vector<int>& indz, BoolOp opp) {
		indices = indz;
		operation = opp;
		bitmask.reset();
		for (auto i : indices) {
			bitmask.set(i);
		}
	}

	std::vector<FaceArea>&	GetFaceAreas() {
		if (g_face_areas.size() == 0) {
			
			// FACE_AREA_EYE_LEFT
			g_face_areas.emplace_back(FaceArea({ EYE_LEFT_1, EYE_LEFT_2, EYE_LEFT_3,
				EYE_LEFT_4, EYE_LEFT_5, EYE_LEFT_6}, FaceArea::BoolOp::BOOLOP_ALL));
			// FACE_AREA_EYE_RIGHT
			g_face_areas.emplace_back(FaceArea({ EYE_RIGHT_1, EYE_RIGHT_2, EYE_RIGHT_3,
				EYE_RIGHT_4, EYE_RIGHT_5, EYE_RIGHT_6 }, FaceArea::BoolOp::BOOLOP_ALL));
			// FACE_AREA_MOUTH_HOLE
			g_face_areas.emplace_back(FaceArea({ MOUTH_INNER_1, MOUTH_INNER_2, MOUTH_INNER_3,
				MOUTH_INNER_4, MOUTH_INNER_5, MOUTH_INNER_6, MOUTH_INNER_7, MOUTH_INNER_8 }, 
				FaceArea::BoolOp::BOOLOP_ALL));
			// FACE_AREA_MOUTH_LIPS
			g_face_areas.emplace_back(FaceArea({ MOUTH_INNER_1, MOUTH_INNER_2, MOUTH_INNER_3,
				MOUTH_INNER_4, MOUTH_INNER_5, MOUTH_INNER_6, MOUTH_INNER_7, MOUTH_INNER_8,
				MOUTH_OUTER_1, MOUTH_OUTER_2, MOUTH_OUTER_3, MOUTH_OUTER_4, MOUTH_OUTER_5,
				MOUTH_OUTER_6, MOUTH_OUTER_7, MOUTH_OUTER_8, MOUTH_OUTER_9, MOUTH_OUTER_10,
				MOUTH_OUTER_11, MOUTH_OUTER_12 },
				FaceArea::BoolOp::BOOLOP_ALL));
			// FACE_AREA_MOUTH
			g_face_areas.emplace_back(FaceArea({ MOUTH_INNER_1, MOUTH_INNER_2, MOUTH_INNER_3,
				MOUTH_INNER_4, MOUTH_INNER_5, MOUTH_INNER_6, MOUTH_INNER_7, MOUTH_INNER_8,
				MOUTH_OUTER_1, MOUTH_OUTER_2, MOUTH_OUTER_3, MOUTH_OUTER_4, MOUTH_OUTER_5, 
				MOUTH_OUTER_6, MOUTH_OUTER_7, MOUTH_OUTER_8, MOUTH_OUTER_9, MOUTH_OUTER_10, 
				MOUTH_OUTER_11, MOUTH_OUTER_12 },
				FaceArea::BoolOp::BOOLOP_ALL));

			// ALL LANDMARK POINTS
			std::vector<int> allpoints;
			for (int i = 0; i < NUM_FACIAL_LANDMARKS; i++) {
				allpoints.push_back(i);
			}

			// FACE_AREA_BACKGROUND
			g_face_areas.emplace_back(FaceArea(allpoints, FaceArea::BoolOp::BOOLOP_NOT_ALL));
			// FACE_AREA_FACE
			g_face_areas.emplace_back(FaceArea(allpoints, FaceArea::BoolOp::BOOLOP_ALL));
			// FACE_AREA_EVERYTHING
			g_face_areas.emplace_back(FaceArea(allpoints, FaceArea::BoolOp::BOOLOP_ANY));
		}
		return g_face_areas;
	}

	const FaceArea&	GetFaceArea(FaceAreaID which) {
		GetFaceAreas();
		return g_face_areas[which];
	}


}