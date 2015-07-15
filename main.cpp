// This file demonstrates the basic operations of OpenCV2 APIs

// Qt Includes
#include <QtGlobal>

// OpenCV Includes
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// System Includes
#include <iostream>
using std::cout;
using std::endl;

// A simlest function demo
cv::Mat simpleFunction( )
{
    // Create an image
    cv::Mat ima( 240, 320, CV_8U, cv::Scalar( 100 ) );
    // Return it
    return ima;
}

// Add 'salt and pepper' noise on an existing iamge,
// where parameter n is the number of noise points
void salt( cv::Mat& image, int n )
{
    for ( int k = 0; k < n; k++ )
    {
        int i = qrand( ) % image.cols;
        int j = qrand( ) % image.rows;

        if ( image.channels( ) == 1 )
        {
            // Accessing method 1
            cv::Mat_< uchar > im2 = image;
            im2( j, i ) = 255;

            // Accessing method 2
            // Note: at method is not fast enough.
            //image.at< uchar >( j, i ) = 255;
        }
        else if ( image.channels( ) == 3 )
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

// Reduce the color range of an image
void colorReduce( cv::Mat& image, int div )
{
    // Implementation 1
    /*
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
    */

    // Implementation 2
    // Using iterator is because of its convenience and safety, instead of its speed.
    cv::Mat_< cv::Vec3b >::iterator it = image.begin< cv::Vec3b >( );  // Obtain iterator at initial position

    cv::Mat_< cv::Vec3b >::iterator itEnd = image.end< cv::Vec3b >( );  // Obtain end position

    // Loop over all pixels
    for ( ; it != itEnd; ++it )
    {
        (*it)[0]=(*it)[0]/div*div + div/2;
        (*it)[1]=(*it)[1]/div*div + div/2;
        (*it)[2]=(*it)[2]/div*div + div/2;
    }
}

// Reduce the color range of an image
void colorReduce( const cv::Mat& image, cv::Mat& result, int div )
{
    result.create( image.rows, image.cols, image.type( ) );

    int nl = image.rows;  // Number of lines
    int nc = image.cols * image.channels( );  // Total number of elements per line

    for ( int j = 0; j < nl; j++ )
    {
        // Get the address of input and output row j
        const uchar* data_in = image.ptr< uchar >( j );
        uchar* data_out = result.ptr< uchar >( j );

        for ( int i = 0; i < nc; i++ )
        {
            // Process each pixel
            // Formula 1
            //data_out[i] = data_in[i]/div*div + div/2;
            // Equivalent statement
            //*data_out++ = *data_in / div*div + div/2;

            // Formula 2
            data_out[i] =  data_in[i] - data_in[i]%div + div/2;
        }
    }
}

// Sharpen an image with Laplacian operator
void sharpen( const cv::Mat& image, cv::Mat& result )
{
    // Allocate memory if necessary
    result.create( image.size( ), image.type( ) );

    // For all rows, except first and last
    for ( int j = 1; j < image.rows - 1; j++ )
    {
        const uchar* previous = image.ptr< const uchar >( j - 1 );  // Previous row
        const uchar* current = image.ptr< const uchar >( j );  // Current row
        const uchar* next = image.ptr< const uchar >( j + 1 );  // Next row

        uchar* output = result.ptr< uchar >( j );  // Output row
        for ( int i = 1; i < image.cols - 1; i++ )
        {
            // Core formula of Laplacian operator
            *output++ = cv::saturate_cast< uchar >( 5 * current[i] - current[i-1] - current[i+1] - previous[i] - next[i] );
        }
    }

    // Set the unprocess pixels to 0
    result.row( 0 ).setTo( cv::Scalar( 0 ) );
    result.row( result.rows - 1 ).setTo( cv::Scalar( 0 ) );
    result.col( 0 ).setTo( cv::Scalar( 0 ) );
    result.col( result.cols - 1 ).setTo( cv::Scalar( 0 ) );
}

// Sharpen an image with Laplacian operator,
// with the help of API filter2D,
// in this way, a 3-channel color image can be processed
void sharpen2D( const cv::Mat& image, cv::Mat& result )
{
    // Construct kernel(all entries initialized to 0)
    cv::Mat kernel( 3, 3, CV_32F, cv::Scalar( 0 ) );
    // Assigns kernel values
    kernel.at< float >( 1, 1 ) = 5.0;
    kernel.at< float >( 0, 1 ) = -1.0;
    kernel.at< float >( 2, 1 ) = -1.0;
    kernel.at< float >( 1, 0 ) = -1.0;
    kernel.at< float >( 1, 2 ) = -1.0;

    // Filter the image
    cv::filter2D( image, result, image.depth( ), kernel );
}

int main( )
{
    // Read an image
    cv::Mat image = cv::imread( "test.jpg" );

    if ( !image.data )
    {
        cout << "No image data!" << endl;
        return -1;
    }

    // Process input image
    cv::Mat result;
    cv::flip( image, result, 1 );  // positive for horizontal
                                   // 0 for vertical,
                                   // negative for both

    cv::Mat grey;
    cv::cvtColor( result, grey, CV_BGR2GRAY );
    cv::Mat sharpened;
    sharpen( grey, sharpened );

    // Example of using kernel matrix
    cv::Mat useKernelSharpened;
    sharpen2D( image, useKernelSharpened );

    salt( result, 5000 );

    cv::Mat clonedResult = result.clone( );

    colorReduce( clonedResult, 32 );

    cv::Mat overloadResult;
    colorReduce( result, overloadResult, 128 );

    cv::imwrite( "flippedGrey.jpg", grey );
    cv::imwrite( "flippedSharpened.jpg", sharpened );
    cv::imwrite( "flippedSalted.jpg", result );
    cv::imwrite( "clonedFlippedColorReduced.jpg", clonedResult );
    cv::imwrite( "overloadFlippedColorReduced.jpg", overloadResult );

    cv::imshow( "Original", image );
    cv::imshow( "Flipped Grey", grey );
    cv::imshow( "Sharpened", sharpened );
    cv::imshow( "Flipped and Salted", result );
    cv::imshow( "Cloned Color Reduce", clonedResult );
    cv::imshow( "Overload Color Reduce", overloadResult );
    cv::imshow( "Use Kernel Matrix", useKernelSharpened );
    cv::waitKey( );


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
