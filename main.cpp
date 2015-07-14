#include <QtGlobal>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
using std::cout;
using std::endl;

cv::Mat function( )
{
    // Create image
    cv::Mat ima( 240, 320, CV_8U, cv::Scalar( 100 ) );
    // Return it
    return ima;
}

void salt( cv::Mat& image, int n )
{
    for ( int k = 0; k < n; k++ )
    {
        int i = qrand( ) % image.cols;
        int j = qrand( ) % image.rows;

        if ( image.channels() == 1 )
        {
            // Accessing method 1
            cv::Mat_< uchar > im2 = image;
            im2( j, i ) = 255;

            // Accessing method 2
            //image.at< uchar >( j, i ) = 255;
        }
        else if ( image.channels() == 3 )
        {
            // Accessing method 1
            cv::Mat_< cv::Vec3b > im2 = image;
            im2( j, i )[0] = 255;
            im2( j, i )[1] = 255;
            im2( j, i )[2] = 255;

            /* Accessing method 2
            image.at< cv::Vec3b >( j, i )[0] = 255;
            image.at< cv::Vec3b >( j, i )[1] = 255;
            image.at< cv::Vec3b >( j, i )[2] = 255;
            */
        }
    }
}

void colorReduce( cv::Mat& image, int div )
{
    int nl = image.rows;  // Number of lines
    int nc = image.cols * image.channels();  // Total number of elements per line

    for ( int j = 0; j < nl; j++ )
    {
        // Get the address of row j
        uchar* data = image.ptr< uchar >( j );
        for ( int i = 0; i < nc; i++ )
        {
            // Process each pixel
            // Formula 1
            //data[i] = data[i]/div*div + div/2;
            // Equivalent statement
            //*data++ = *data / div*div + div/2;

            // Formula 2
            data[i] =  data[i] - data[i]%div + div/2;
        }
    }
}


int main( )
{
#if 0
    cv::Mat image;
    cout << image.size( ) << endl;

    std::cout << "size: " << image.size().height << " , "
    << image.size().width << std::endl;
#endif

#if 0
    cv::Mat ima1(240,320,CV_32FC3,cv::Scalar(12, 12, 0));
    cv::Mat ima2(240,320,CV_8U,cv::Scalar(255));
    cv::imshow( "F", ima1 );
    cv::imshow( "U", ima2 );
    cv::waitKey( );
#endif

#if 1
    // Read an image
    cv::Mat image = cv::imread( "test.jpg" );

    if ( !image.data )
    {
        cout << "No image data!" << endl;
        return -1;
    }

    // Do some processing
    cv::Mat result;
    cv::flip( image, result, 1 );  // positive for horizontal
                                   // 0 for vertical,
                                   // negative for both
    salt( result, 5000 );

    cv::Mat clonedResult = result.clone( );
    colorReduce( clonedResult, 64 );

  #if 0
    cv::Mat image2, image3;
    image2 = result;
    result.copyTo( image3 );
    cv::imshow( "ReferSame", image2 );
    cv::imshow( "NewCloned", image3 );
  #endif

    cv::namedWindow( "My Image" );
    cv::imshow( "My Image", image );

    cv::namedWindow( "ClonedResult" );
    cv::imshow( "ClonedResult", clonedResult );
    cv::waitKey( );

    cv::imwrite( "hflipped.jpg", result );
#endif

#if 0
    cv::Mat fromFunc = function( );
    cv::imshow( "From Func", fromFunc );
    cv::waitKey( );
#endif

#if 0
    IplImage* iplimg = cvLoadImage( "test.jpg" );
    cv::Mat image4( iplimg, false );
    cv::imshow( "wrapped", image4 );
    cv::waitKey( );
    cvReleaseImage( &iplimg );
#endif

#if 0
    cv::Ptr< IplImage > pIplimg = cvLoadImage( "test.jpg" );
    // How to display it(as a Ptr class)?
    //cv::imshow( "Smart Pointer Wrapper", pIplimg );
    cv::waitKey( );
#endif
    return 0;
}
