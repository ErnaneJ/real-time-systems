#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <numeric>
#include <sys/time.h>

#define GAME_RESULT_FILE "../assets/game_results.txt"
#define GAME_WINDOW_SIZE 500
#define GAME_WINDOW_NAME "Human Reaction Time Meter - Game!"
#define GAME_OVER_IMAGE "../assets/game-over.png"
#define CIRCLE_RADIUS 25
#define PRECISION 10
#define ROUNDS 10
#define ARROW_UP 0
#define ARROW_DOWN 1
#define ARROW_LEFT 2
#define ARROW_RIGHT 3

/**
 * @brief Formats the elapsed time into a string.
 * 
 * @param seconds The time in seconds.
 * @return A formatted string representing the time in hours, minutes, seconds, and milliseconds.
 */
std::string formatTime(double seconds) 
{
  int hours = static_cast<int>(seconds / 3600);
  int minutes = static_cast<int>((seconds - hours * 3600) / 60);
  int wholeSeconds = static_cast<int>(seconds) % 60;
  int milliseconds = static_cast<int>(std::round((seconds - static_cast<int>(seconds)) * 1000));
  
  std::ostringstream oss;
  oss << std::setfill('0');
  oss << std::setw(2) << hours << "h " 
      << std::setw(2) << minutes << "min " 
      << std::setw(2) << wholeSeconds << "s " 
      << std::setw(3) << milliseconds << "ms";
  
  return oss.str();
};

/**
 * @brief Saves the game results to a file.
 * 
 * @param responseTimes Vector containing response times.
 * @param correctAnswers Number of correct answers.
 */
void saveResultsToFile(const std::vector<double>& responseTimes, int correctAnswers) 
{
  std::ofstream outFile(GAME_RESULT_FILE, std::ios::app);
  std::time_t now = std::time(nullptr);

  double totalTime = std::accumulate(responseTimes.begin(), responseTimes.end(), 0.0);
  double averageTime = totalTime / responseTimes.size();

  outFile << std::put_time(std::localtime(&now), "%d/%m/%Y às %H:%M:%S") << " | "
          << std::fixed << std::setprecision(PRECISION)
          << formatTime(totalTime) << " | "
          << std::fixed << std::setprecision(PRECISION)
          << formatTime(averageTime) << " | "
          << correctAnswers << "/" << ROUNDS << "\n";
  
  outFile.close();
};

/**
 * @brief Displays previous game results from a file.
 */
void displayPreviousResults() 
{
  std::ifstream inFile(GAME_RESULT_FILE);
  
  if (!inFile) 
  {
    std::cout << "❌ No previous attempts found.\n";
    return;
  }
  
  std::string line;
  std::cout << "\n============================( ✅ Previous attempts ✅ )==============================\n\n";
  
  while (std::getline(inFile, line)) 
  {
    std::cout << line << "\n";
  }
  
  std::cout << "\n====================================================================================\n";
  inFile.close();
};

/**
 * @brief Generates a random color and sets the correct key for the color.
 * 
 * @param correctKey Reference to store the correct key.
 * @return A cv::Scalar representing the color.
 */
cv::Scalar getRandomColor(int& correctKey) 
{
  int color = rand() % 4;
  
  switch (color) 
  {
    case ARROW_UP: 
      correctKey = ARROW_UP;
      return cv::Scalar(0, 255, 255); // Yellow
    case ARROW_RIGHT:
      correctKey = ARROW_RIGHT;
      return cv::Scalar(255, 0, 0);   // Red
    case ARROW_LEFT:
      correctKey = ARROW_LEFT;
      return cv::Scalar(0, 0, 255);   // Blue
    case ARROW_DOWN:
      correctKey = ARROW_DOWN;
      return cv::Scalar(0, 255, 0);   // Green
  }
  
  return cv::Scalar(255, 255, 255); // Default white - fallback
};

/**
 * @brief Displays a spiral animation in the game window.
 * 
 * @param window The window to draw the spiral.
 * @param delayTime The duration of the animation in seconds.
 */
void showSpiral(cv::Mat& window, int delayTime) 
{
  for (int i = 0; i < delayTime * 10; i++) 
  {
    window = cv::Mat::zeros(GAME_WINDOW_SIZE, GAME_WINDOW_SIZE, CV_32FC3);
    cv::Point center(250, 250);
    cv::ellipse(window, center, cv::Size(50, 50), i * 36, 0, 270, cv::Scalar(255, 255, 255), 2);
    
    cv::circle(window, cv::Point(70, 470), 10, cv::Scalar(0, 255, 255), cv::FILLED); // Yellow
    cv::putText(window, "Up", cv::Point(90, 475), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255), 1);
    
    cv::circle(window, cv::Point(170, 470), 10, cv::Scalar(0, 0, 255), cv::FILLED); // Blue
    cv::putText(window, "Left", cv::Point(190, 475), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255), 1);
    
    cv::circle(window, cv::Point(270, 470), 10, cv::Scalar(255, 0, 0), cv::FILLED); // Red
    cv::putText(window, "Right", cv::Point(290, 475), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255), 1);
    
    cv::circle(window, cv::Point(370, 470), 10, cv::Scalar(0, 255, 0), cv::FILLED); // Green
    cv::putText(window, "Down", cv::Point(390, 475), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255), 1);
    
    cv::imshow(GAME_WINDOW_NAME, window);
    
    if (cv::waitKey(30) == 27) 
    {
      std::cout << std::endl << "❌ Game aborted.\n";
      exit(0);
    }
  }
};

/**
 * @brief Main function to run the Human Reaction Time Meter game.
 * 
 * @return Exit status of the program.
 */
int main() 
{
  srand(static_cast<unsigned>(time(0)));

  std::vector<double> responseTimes;
  int correctAnswers = 0;

  displayPreviousResults();
  std::cout << std::endl << "🔄 Starting new attempt...\n\n";

  cv::namedWindow(GAME_WINDOW_NAME, cv::WINDOW_AUTOSIZE);
  
  for (int round = 0; round < ROUNDS; ++round) 
  {
    int waitTime = 3 + rand() % 8;
    
    cv::Mat waitWindow = cv::Mat::zeros(GAME_WINDOW_SIZE, GAME_WINDOW_SIZE, CV_32FC3);
    showSpiral(waitWindow, waitTime);

    cv::Mat gameWindow = cv::Mat::zeros(GAME_WINDOW_SIZE, GAME_WINDOW_SIZE, CV_32FC3);
    int correctKey;
    cv::Scalar circleColor = getRandomColor(correctKey);

    int circleX = rand() % (GAME_WINDOW_SIZE - 100) + CIRCLE_RADIUS;
    int circleY = rand() % (GAME_WINDOW_SIZE - 100) + CIRCLE_RADIUS;
    
    cv::circle(gameWindow, cv::Point(circleX, circleY), CIRCLE_RADIUS, circleColor, cv::FILLED);
    cv::imshow(GAME_WINDOW_NAME, gameWindow);

    struct timeval startTime, endTime;
    int elapsedTimeMillis;
    float elapsedTimeSeconds;
    int keyPressed = 0;

    gettimeofday(&startTime, NULL);
    
    std::cout << "↳ Round " << round + 1 << "/" << ROUNDS << std::endl;

    while (true) 
    {
      gettimeofday(&endTime, NULL);
      elapsedTimeMillis = static_cast<int>(1000 * (endTime.tv_sec - startTime.tv_sec) + 
                                            (endTime.tv_usec - startTime.tv_usec) / 1000);
      elapsedTimeSeconds = elapsedTimeMillis / 1000.0f;

      std::cout << "\033[F\033[K"; // Clear the last line
      std::cout << "↳ Round " << round + 1 << "/" << ROUNDS << " (" 
                << formatTime(elapsedTimeSeconds) << ") - Press the correct key!\n";
      
      keyPressed = cv::waitKey(1);
      
      if (keyPressed == 27) 
      {
        std::cout << std::endl << "\n❌ Game aborted.\n";
        exit(0);
      } 
      else if (keyPressed == correctKey) 
      {
        std::cout << "✅ Correct!" << std::endl;
        responseTimes.push_back(elapsedTimeSeconds);
        correctAnswers++;
        break;
      } 
      else if (keyPressed == ARROW_UP || keyPressed == ARROW_DOWN || keyPressed == ARROW_LEFT || keyPressed == ARROW_RIGHT) 
      {
        std::cout << "❌ Incorrect!" << std::endl;
        responseTimes.push_back(elapsedTimeSeconds);
        break;
      }
    }
  }

  cv::Mat gameOverImage = cv::imread(GAME_OVER_IMAGE);
  cv::putText(gameOverImage, "Press any key to exit...", cv::Point(140, 475), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255), 1);
  cv::imshow(GAME_WINDOW_NAME, gameOverImage);
  cv::waitKey(0);

  saveResultsToFile(responseTimes, correctAnswers);

  displayPreviousResults();
  
  std::cout << "\n✅ Results saved.\n";

  system("cd $(pwd)/../plot && source venv/bin/activate && pip install -r requirements.txt && python main.py");

  return 0;
};