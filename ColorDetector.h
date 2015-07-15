// A class encapsulating an algorithm that will identify all of the pixels in an image,
// which have a given color by the class user. The algorithm accepts an image and a color as input,
// and returns a binary image showing the pixels having the specified color.
// The tolerance with which we want to accept a color will be another parameter,
// to be specified before running the algorithm.

#ifndef COLORDETECTOR_H
#define COLORDETECTOR_H

// OpenCV Includes
#include <opencv2/core/core.hpp>

class ColorDetector
{
public:
    // Empty constructor
    ColorDetector( ) : minDist( 100 )
    {
        // Default parameter initialization here
        target[0] = target[1] = target[2] = 0;
    }

    // Sets the color distance threshold.
    // Threshold must be positive,
    // otherwise distance threshold is set to 0.
    void setColorDistanceThreshold( int distance )
    {
        if ( distance < 0 )
            minDist = 0;

        minDist = distance;
    }

    // Gets the color distance threshold
    int getColorDistanceThreshold( ) const
    {
        return minDist;
    }

    // Sets the color to be detected
    void setTargetColor( unsigned char red,
                         unsigned char green,
                         unsigned char blue )
    {
        // BGR order
        target[2] = red;
        target[1] = green;
        target[0] = blue;
    }

    // Sets the color to be detected
    void setTargetColor( cv::Vec3b color )
    {
        target = color;
    }

    // Gets the color to be detected
    cv::Vec3b getTargetColor( ) const
    {
        return target;
    }

    cv::Mat process( const cv::Mat& image );

private:
    // Minimum acceptable distance
    int minDist;

    // Target color
    cv::Vec3b target;

    // Image containing resulting binary map
    cv::Mat result;

    int getDistance( const cv::Vec3b& color ) const;
};

#endif // COLORDETECTOR_H
