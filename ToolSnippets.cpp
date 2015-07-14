/*
* The usual pattern to use in order to obtain the computational time of a given function (or portion of code).
*/
double duration;
duration = static_cast< double >( cv::getTickCount( ) );
Foo( );  // The function to be tested
duration = static_cast< double >( cv::getTickCount( ) ) - duration;
duration /= cv::getTickFrequency( );  // The elapsed time in ms

/*
* Save image sequences(C style API)
*/
char imageName[64];
sprintf( imgName, "imageBaseName_%d.jpg", nFrameNum );
cvSaveImage( imgName, pImg );
