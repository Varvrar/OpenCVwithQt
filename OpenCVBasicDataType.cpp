#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
using namespace std;

int main( )
{
    cv::Point_< double > pt2d( 3.0, 3.0 );
    cout << pt2d.x << "  " << pt2d.y << endl;

    cv::Point3_< float > pt3f( 2.5, 3.4, -4.0 );
    cout << pt3f.x << "  " << pt3f.y << "  " << pt3f.z << endl;

    cv::Size_< int > size( 320, 240 );
    cout << size.area( ) << endl;
    cout << size.height << "  " << size.width << endl;

    return 0;
}

