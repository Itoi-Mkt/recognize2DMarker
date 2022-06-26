#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/aruco.hpp"

// MarkersID取得
void ShowMarkerIdsFunction(cv::OutputArray in)
{
  std::vector<cv::Mat> marker_ids;
  in.getMatVector(marker_ids);
  std::cout << "Marker IDs : " << std::endl;
  for (auto marker_ids : marker_ids)
  {
    std::cout << marker_ids << std::endl;
  }
}

int main(int argh, char *argv[])
{
  // MarkerDictionary生成
  const cv::aruco::PREDEFINED_DICTIONARY_NAME dictionary_name = cv::aruco::DICT_5X5_1000;
  cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(dictionary_name);
  std::vector<int> marker_ids;
  std::vector<std::vector<cv::Point2f>> marker_corners;
  cv::Mat web_camera_frame;
  cv::VideoCapture cap(0);

  // Webカメラ接続
  if (!cap.isOpened())
  {
    printf("web camera : Bad Connection\n");
    return -1;
  }

  // MarkerID認識
  while (cap.read(web_camera_frame))
  {
    // Marker探査
    cv::Ptr<cv::aruco::DetectorParameters> parameters = cv::aruco::DetectorParameters::create();
    cv::aruco::detectMarkers(web_camera_frame, dictionary, marker_corners, marker_ids, parameters);
    cv::aruco::drawDetectedMarkers(web_camera_frame, marker_corners, marker_ids);

    cv::imshow("from camera", web_camera_frame);

    // MarkerIDのコンソールへの表示
    ShowMarkerIdsFunction(marker_ids);

    const int key = cv::waitKey(1);
    if (key == 'q')
    {
      break;
    }
    else if (key == 's')
    {
      cv::imwrite("Marker_ids_recognized.png", web_camera_frame);
    }
  }
  cv::destroyAllWindows();
  return 0;
}
