#include "colordetector.h"

cv::Mat ColorDetector::process( const cv::Mat& image )
{
    // Re-allocate binary map if necessary
    // Same size as input image, but 1-channel
    result.create( image.rows, image.cols, CV_8U );

    // Get the iterators
    cv::Mat_< cv::Vec3b >::const_iterator it = image.begin< cv::Vec3b >( );  // Obtain iterator at initial position

    cv::Mat_< cv::Vec3b >::const_iterator itEnd = image.end< cv::Vec3b >( );  // Obtain end position

    cv::Mat_< uchar >::iterator itout = result.begin< uchar >( );

    // For each pixel
    for ( ; it != itEnd; ++it, ++itout )
    {
        // Process each pixel -----------------
        // Compute distance from target color
        if ( getDistance( *it ) < minDist )
        {
            *itout = 255;
        }
        else
        {
            *itout = 0;
        }
        // End of pixel processing ------------
    }

    return result;
}

// Computes the distance from target color
int ColorDetector::getDistance( const cv::Vec3b& color ) const
{
    // Manhattan block distance
#if 0
    return abs( color[0] - target[0] )+
           abs( color[1] - target[1] )+
           abs( color[2] - target[2] );
#endif

#if 1
    // Euclidean distance
    return static_cast< int >(
                cv::norm< int, 3 >( cv::Vec3i( color[0] - target[0],
                                               color[1] - target[1],
                                               color[2] - target[2] ) ) );

    // Equivalent statement of Euclidean distance,
    // however, it may be not safe, if target value is not right set.
    //return static_cast< int >( cv::norm< uchar, 3 >( color - target ) );
#endif
}
