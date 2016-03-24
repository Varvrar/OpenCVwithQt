#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

int main( )
{
    cv::Mat image( 240, 320, CV_8UC3 );
    cv::imshow( "image", image );
    cv::waitKey( );

    image.create( 480, 640, CV_8UC3 );
    cv::imshow( "image", image );
    cv::waitKey( );

    cv::Mat A33( 3, 3, CV_32F, cv::Scalar( 185 ) );
    cv::imshow( "A33", A33 );
    cv::waitKey( );

    cv::Mat B33( 3, 3, CV_32F );
    B33 = cv::Scalar( 255 );
    cv::imshow( "B33", B33 );
    cv::waitKey( );

    cv::Mat C33 = cv::Mat::ones( 3, 3, CV_32F ) * 5;
    cv::imshow( "C33", C33 );
    cv::waitKey( );

    cv::Mat D33 = cv::Mat::ones( 3, 3, CV_32F ) + 5;
    cv::imshow( "D33", D33 );
    cv::waitKey( );

    double a = CV_PI / 3;
    double B22data[] = {cos( a ), -sin( a ), sin( a ), cos( a )};
    cv::Mat B22 = cv::Mat( 2, 2, CV_32F, B22data ).clone( );
    cv::imshow( "B22", B22 );
    cv::waitKey( );

    cv::Mat imageRandomU( 240, 320, CV_8U );
    cv::randu( imageRandomU, cv::Scalar( 0 ), cv::Scalar( 255 ) );
    cv::imshow( "image_uniform", imageRandomU );
    cv::waitKey( );

    cv::Mat imageRandomN( 240, 320, CV_8U );
    cv::randn( imageRandomN, cv::Scalar( 128 ), 10 );
    cv::imshow( "image_normal", imageRandomN );
    cv::waitKey( );

    return 0;
}
