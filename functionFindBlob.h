//
//  functionFindBlob.h
//  popupImage
//
//  Created by jollytrees on 11/16/15.
//
//

#ifndef functionFindBlob_h
#define functionFindBlob_h


static void FindBlobs(const cv::Mat &binary, std::vector < std::vector<cv::Point2i> > &blobs);

static int countBlobs(cv::Mat &img)
{
    //cv::Mat img = cv::imread("./newPatch/innerGreyB2_2.png", 0); // force greyscale
    //cout << "in Connnected Bolobs" << endl;
    if(!img.data) {
        std::cout << "File not found" << std::endl;
    }
    
    cv::Mat output = cv::Mat::zeros(img.size(), CV_8UC3);
    
    cv::Mat binary;
    std::vector < std::vector<cv::Point2i > > blobs;
    
    cv::threshold(img, binary, 0.0, 1.0, cv::THRESH_BINARY);
    
    FindBlobs(binary, blobs);
    
    return blobs.size();
    
}

static void ConnectedBlobsBinary(cv::Mat &img, vector<cv::Mat> &blobMat)
{
    //cv::Mat img = cv::imread("./newPatch/innerGreyB2_2.png", 0); // force greyscale
    //cout << "in Connnected Bolobs" << endl;
    if(!img.data) {
        std::cout << "File not found" << std::endl;
    }
    
    cv::Mat output = cv::Mat::zeros(img.size(), CV_8UC3);
    
    cv::Mat binary;
    std::vector < std::vector<cv::Point2i > > blobs;
    
    cv::threshold(img, binary, 0.0, 1.0, cv::THRESH_BINARY);
    
    FindBlobs(binary, blobs);
    
    // Randomy color the blobs
    for(size_t i=0; i < blobs.size(); i++) {
        
        output.setTo(black);
        
        unsigned char r = 255 ;
        unsigned char g = 255 ;
        unsigned char b = 255 ;
        
        for(size_t j=0; j < blobs[i].size(); j++) {
            int x = blobs[i][j].x;
            int y = blobs[i][j].y;
            
            output.at<cv::Vec3b>(y,x)[0] = b;
            output.at<cv::Vec3b>(y,x)[1] = g;
            output.at<cv::Vec3b>(y,x)[2] = r;
        }
        
        cv::Mat returnMat;
        cv::cvtColor(output, returnMat, CV_BGR2GRAY);
        blobMat.push_back(returnMat.clone());
    }
    
}


static void ConnectedBlobs(cv::Mat &img, vector<cv::Mat> &blobMat)
{
    //cv::Mat img = cv::imread("./newPatch/innerGreyB2_2.png", 0); // force greyscale
    //cout << "in Connnected Bolobs" << endl;
    if(!img.data) {
        std::cout << "File not found" << std::endl;
    }
    
    cv::Mat output = cv::Mat::zeros(img.size(), CV_8UC3);
    
    cv::Mat binary;
    std::vector < std::vector<cv::Point2i > > blobs;
    
    cv::threshold(img, binary, 0.0, 1.0, cv::THRESH_BINARY);
    
    FindBlobs(binary, blobs);
    
    // Randomy color the blobs
    for(size_t i=0; i < blobs.size(); i++) {
        
        output.setTo(black);
        
        unsigned char r = 255 ;
        unsigned char g = 255 ;
        unsigned char b = 255 ;
        
        for(size_t j=0; j < blobs[i].size(); j++) {
            int x = blobs[i][j].x;
            int y = blobs[i][j].y;
            
            output.at<cv::Vec3b>(y,x)[0] = b;
            output.at<cv::Vec3b>(y,x)[1] = g;
            output.at<cv::Vec3b>(y,x)[2] = r;
        }
        
        blobMat.push_back(output.clone());
    }

}

static void FindBlobs(const cv::Mat &binary, std::vector < std::vector<cv::Point2i> > &blobs)
{
    blobs.clear();
    
    // Fill the label_image with the blobs
    // 0  - background
    // 1  - unlabelled foreground
    // 2+ - labelled foreground
    
    cv::Mat label_image;
    binary.convertTo(label_image, CV_32SC1);
    
    int label_count = 2; // starts at 2 because 0,1 are used already
    
    for(int y=0; y < label_image.rows; y++) {
        int *row = (int*)label_image.ptr(y);
        for(int x=0; x < label_image.cols; x++) {
            if(row[x] != 1) {
                continue;
            }
            
            cv::Rect rect;
            cv::floodFill(label_image, cv::Point(x,y), label_count, &rect, 0, 0, 4);
            
            std::vector <cv::Point2i> blob;
            
            for(int i=rect.y; i < (rect.y+rect.height); i++) {
                int *row2 = (int*)label_image.ptr(i);
                for(int j=rect.x; j < (rect.x+rect.width); j++) {
                    if(row2[j] != label_count) {
                        continue;
                    }
                    
                    blob.push_back(cv::Point2i(j,i));
                }
            }
            
            blobs.push_back(blob);
            
            label_count++;
        }
    }
}


#endif /* functionFindBlob_h */
