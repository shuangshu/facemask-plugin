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

#include <dlib/image_processing.h>
#include <dlib/opencv.h>
#include <opencv2/opencv.hpp>
#include <string>
#include <locale>
#include <codecvt>

namespace FaceLib {
	/*
	FaceLandmarks class wrapped around DLIB+OpenCV to detect landmarks
	*/

	class FaceLandmarks {
	public:
		/**
		Constructor to initialize the FaceLandmarks object.

		@usage FaceLib::FaceLandmarks landmarksPredictor;
		*/
		FaceLandmarks();

		/**
		Destructor for the FaceLandmarks object.
		*/
		~FaceLandmarks();

		/**
		Constructor to initialize the FaceLandmarks object.
		Intializes the DLIB Face Shape Predictor.

		@param filename The full path to the shape predictor file.
		@usage FaceLib::FaceDetector detector(filename);
		*/
		FaceLandmarks(char* filename);

		/**
		Constructor to initialize the FaceLandmarks object.
		Intializes the DLIB Face Shape Predictor.

		@param filename The full path to the shape predictor file.
		@usage FaceLib::FaceDetector detector(filename);
		*/
		FaceLandmarks(std::string filename);

		/**
		Function to initialize the DLIB's shape predictor.

		@param filename The full path to the shape predictor file.
		@return None
		*/
		void Init(char* filename);

		/**
		Returns all the landmarks for the given face in the image in
		std::vector<dlib::point> format.

		@param image The image in cv::Mat format to detect landmarks.
		@param face The bounding box of face in dlib::rectangle format.
		@param landmarks Return current landmarks in std::vector<dlib::point>
		@return None.
		*/
		void DetectLandmarks(cv::Mat& image, dlib::rectangle& face, std::vector<dlib::point>& landmarks);

		/**
		Returns all the landmarks for the given face in the image in
		std::vector<dlib::point> format.

		@param image The image in dlib::array2d<unsigned char> format to detect landmarks.
		@param face The bounding box of face in dlib::rectangle format.
		@param landmarks Return current landmarks in std::vector<dlib::point>
		@return None.
		*/
		void DetectLandmarks(dlib::array2d<unsigned char>& image, dlib::rectangle& face, std::vector<dlib::point>& landmarks);

		/**
		Returns the face pose in cv::Mat {R, t} format

		@param landmarks2D Face landmarks in 2D from the image.
		@param K Camera intrinsics matrix.
		@param D Camera distortion coefficients.
		@param R Return rotation matrix for the face pose in euler angles format.
		@param t Return translation vector for the face pose.
		@param useExtrinsicGuess Boolean value to use the previous {R, t} values.
		@return None.
		*/
		void DetectPose(std::vector<cv::Point2d>& landmarks2D, const cv::Mat& K, const cv::Mat& D, cv::Mat& R, cv::Mat& t, bool useExtrinsicGuess = false);

		/**
		Returns the reprojection error for the 2D<->3D landmarks

		@return reprojection error in double format.
		*/
		double GetReprojectionError();

	private:
		dlib::shape_predictor _landmarksPredictor;
		std::vector<cv::Point3d> _landmarks3D;
		double _reprojectionError;

		/**
		Initializes the 3D model landmarks to compute pose

		@return None.
		*/
		void InitLandmarks3D();

		/**
		Computes the reprojection error for the 2D<->3D landmarks 

		@param landmarks2D Face landmarks in 2D from the image.
		@param K Camera intrinsics matrix.
		@param D Camera distortion coefficients.
		@param R Rotation matrix for the face pose in euler angles format.
		@param t translation vector for the face pose.
		@return None.
		*/
		void ComputeReprojectionError(std::vector<cv::Point2d>& landmarks2D, const cv::Mat& K, const cv::Mat& D, cv::Mat& R, cv::Mat& t);
	};
}