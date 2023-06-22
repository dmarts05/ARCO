#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <omp.h>
#include <recount.h>
#include <sstream>
#include <sys/time.h>
#include <vector>
// #include <QDir>

using namespace std;

// PROTOTYPES
void calculate_p_participation(vector<recount> &content,
                               string comp_mode = "sequential");
void calculate_p_abstention(vector<recount> &content,
                            string comp_mode = "sequential");
int calculate_total_census(vector<recount> content,
                           string comp_mode = "sequential");
int calculate_total_abstention(vector<recount> content,
                               string comp_mode = "sequential");
recount get_min_census(vector<recount> content,
                       string comp_mode = "sequential");
recount get_max_census(vector<recount> content,
                       string comp_mode = "sequential");
float get_mean_p_participation(vector<recount> content,
                               string comp_mode = "sequential");
float get_mean_p_abstention(vector<recount> content,
                            string comp_mode = "sequential");

// MAIN
int main()
{
  // It can be used to know the execution path
  // cout << "[EXECUTION PATH]: " << QDir::currentPath().toStdString() + '\n';
  // Path and name of the csv file
  string fname = "../openmp-dmarts05/elecciones_navarra_1999.csv";

  // Init variables
  vector<recount> content;
  vector<string> row;
  recount read_recount = recount();
  int count_row = 0;
  string line, word;

  // Read document
  ifstream file(fname, ios::in);
  if (file.is_open())
  {
    // Read each row of the file
    while (getline(file, line))
    {
      row.clear(); // Clear row array
      stringstream stream(line);
      // Divide the line by the separator (;) and each value is an element of
      // the array row
      while (getline(stream, word, ';'))
        row.push_back(word);

      if (count_row > 0)
      { // First row of the document correspond to the header
        // TO_DO: CREATE recount object and append to content
        read_recount = recount(row);
        content.push_back(read_recount);

        // read_recount.print(); // To see the information uncomment this line
      }
      count_row++;
    }
    cout << "[OK]: " << count_row
         << " lines read from the file and added to the list of contents"
         << "\n";
  }
  else
  {
    cout << "[ERROR]: Could not open the file, check the file path\n";
  }

  cout << "***************************************" << endl;
  cout << "*              SEQUENTIAL             *" << endl;
  cout << "***************************************" << endl;

  cout << "***************************************" << endl;
  cout << "Exercise 1: Calculate participation percentage" << endl;
  cout << "***************************************" << endl;
  calculate_p_participation(content, "sequential");

  cout << "***************************************" << endl;
  cout << "Exercise 2: Calculate abstention percentage" << endl;
  cout << "***************************************" << endl;
  calculate_p_abstention(content, "sequential");

  cout << "***************************************" << endl;
  cout << "Exercise 3: Calculate total census" << endl;
  cout << "***************************************" << endl;
  int total_census_sequential = calculate_total_census(content, "sequential");
  cout << "Total census: " << total_census_sequential << endl;

  cout << "***************************************" << endl;
  cout << "Exercise 4: Calculate total abstention" << endl;
  cout << "***************************************" << endl;
  int total_abstention_sequential =
      calculate_total_abstention(content, "sequential");
  cout << "Total abstention: " << total_abstention_sequential << endl;

  cout << "***************************************" << endl;
  cout << "Exercise 5: Get min census" << endl;
  cout << "***************************************" << endl;
  recount min_census_sequential = get_min_census(content, "sequential");
  min_census_sequential.print();

  cout << "***************************************" << endl;
  cout << "Exercise 6: Get max census" << endl;
  cout << "***************************************" << endl;
  recount max_census_sequential = get_max_census(content, "sequential");
  max_census_sequential.print();

  cout << "***************************************" << endl;
  cout << "Exercise 7: Get mean participation percentage" << endl;
  cout << "***************************************" << endl;
  float mean_p_participation_sequential =
      get_mean_p_participation(content, "sequential");
  cout << "Mean participation percentage: " << mean_p_participation_sequential << "%"
       << endl;

  cout << "***************************************" << endl;
  cout << "Exercise 8: Get mean abstention percentage" << endl;
  cout << "***************************************" << endl;
  float mean_p_abstention_sequential =
      get_mean_p_abstention(content, "sequential");
  cout << "Mean abstention percentage: " << mean_p_abstention_sequential << "%"
       << endl;

  cout << endl;
  cout << "***************************************" << endl;
  cout << "*              PARALLEL               *" << endl;
  cout << "***************************************" << endl;

  cout << "***************************************" << endl;
  cout << "Exercise 1: Calculate participation percentage" << endl;
  cout << "***************************************" << endl;
  calculate_p_participation(content, "parallel");

  cout << "***************************************" << endl;
  cout << "Exercise 2: Calculate abstention percentage" << endl;
  cout << "***************************************" << endl;
  calculate_p_abstention(content, "parallel");

  cout << "***************************************" << endl;
  cout << "Exercise 3: Calculate total census" << endl;
  cout << "***************************************" << endl;
  int total_census_parallel = calculate_total_census(content, "parallel");
  cout << "Total census: " << total_census_parallel << endl;

  cout << "***************************************" << endl;
  cout << "Exercise 4: Calculate total abstention" << endl;
  cout << "***************************************" << endl;
  int total_abstention_parallel =
      calculate_total_abstention(content, "parallel");
  cout << "Total abstention: " << total_abstention_parallel << endl;

  cout << "***************************************" << endl;
  cout << "Exercise 5: Get min census" << endl;
  cout << "***************************************" << endl;
  recount min_census_parallel = get_min_census(content, "parallel");
  min_census_parallel.print();

  cout << "***************************************" << endl;
  cout << "Exercise 6: Get max census" << endl;
  cout << "***************************************" << endl;
  recount max_census_parallel = get_max_census(content, "parallel");
  max_census_parallel.print();

  cout << "***************************************" << endl;
  cout << "Exercise 7: Get mean participation percentage" << endl;
  cout << "***************************************" << endl;
  float mean_p_participation_parallel =
      get_mean_p_participation(content, "parallel");
  cout << "Mean participation percentage: " << mean_p_participation_parallel << "%"
       << endl;

  cout << "***************************************" << endl;
  cout << "Exercise 8: Get mean abstention percentage" << endl;
  cout << "***************************************" << endl;
  float mean_p_abstention_parallel = get_mean_p_abstention(content, "parallel");
  cout << "Mean abstention percentage: " << mean_p_abstention_parallel << "%"
       << endl;

  return 0;
}

// TO_DO: FUNCTIONS

/**
 * @brief calculate_p_participation calculate participation percentage:
 * p_participation = (v_cast * 100) / census
 * @param content vector of recount elements
 * @param comp_mode is the computational mode, it can be: sequential or parallel
 */
void calculate_p_participation(vector<recount> &content, string comp_mode)
{
  // Init variables
  recount *r;
  struct timeval begin, end;
  double wt1 = 0, wt2 = 0;
  float p_participation = 0;

  wt1 = omp_get_wtime();
  gettimeofday(&begin, 0);
  // Sequential mode
  if (comp_mode == "sequential")
  {
    for (size_t i = 0; i < content.size(); i++)
    {
      r = &content[i];
      p_participation = (r->get_v_cast() * 100) / r->get_census();
      // cout << "Participation percentage of code " << r->get_code() << ": "
      //  << p_participation << endl;
      r->set_p_participation(p_participation);
    }
  }
  // Parallel mode
  else if (comp_mode == "parallel")
  {
#pragma omp parallel for shared(content) private(r, p_participation)
    for (size_t i = 0; i < content.size(); i++)
    {
      r = &content[i];
      p_participation = (r->get_v_cast() * 100) / r->get_census();
      // cout << "Participation percentage of code " << r->get_code() << ": "
      //  << p_participation << endl;
      r->set_p_participation(p_participation);
    }
  }
  else
  {
    printf("[ERROR]: Not valid computational mode in %s. Only: sequential and "
           "parallel\n",
           __FUNCTION__);
    throw("ERROR");
  }
  gettimeofday(&end, 0);
  wt2 = omp_get_wtime();

  // Print results
  long seconds = end.tv_sec - begin.tv_sec;
  long microseconds = end.tv_usec - begin.tv_usec;
  double elapsed = seconds * 1e-6 + microseconds; // in microseconds
  printf("[CPU_TIME]: %s \tComputational mode: %s  \t%.2f microseconds \n",
         __FUNCTION__, comp_mode.c_str(), elapsed);
  double omp_elapse = (wt2 - wt1) * 1e-6;
  printf("[OMP_TIME]: %s \tComputational mode: %s  \t%.2f microseconds \n",
         __FUNCTION__, comp_mode.c_str(), omp_elapse);
}

/**
 * @brief calculate_p_abstention calculate abstention percentage: p_abstention =
 * (abstention * 100) / census
 * @param content vector of recount elements
 * @param comp_mode is the computational mode, it can be: sequential or parallel
 */
void calculate_p_abstention(vector<recount> &content, string comp_mode)
{
  // Init variables
  recount *r;
  struct timeval begin, end;
  double wt1 = 0, wt2 = 0;
  float p_abstention = 0;

  wt1 = omp_get_wtime();
  gettimeofday(&begin, 0);
  // Sequential mode
  if (comp_mode == "sequential")
  {
    for (size_t i = 0; i < content.size(); i++)
    {
      r = &content[i];
      p_abstention = (r->get_abstentions() * 100) / r->get_census();
      // cout << "Abstention percentage of code " << r->get_code() << ": "
      //  << p_abstention << endl;
      r->set_p_abstention(p_abstention);
    }
  }
  // Parallel mode
  else if (comp_mode == "parallel")
  {
#pragma omp parallel for shared(content) private(r, p_abstention)
    for (size_t i = 0; i < content.size(); i++)
    {
      r = &content[i];
      p_abstention = (r->get_abstentions() * 100) / r->get_census();
      // cout << "Abstention percentage of code " << r->get_code() << ": "
      //  << p_abstention << endl;
      r->set_p_abstention(p_abstention);
    }
  }
  else
  {
    printf("[ERROR]: Not valid computational mode in %s. Only: sequential and "
           "parallel\n",
           __FUNCTION__);
    throw("ERROR");
  }
  gettimeofday(&end, 0);
  wt2 = omp_get_wtime();

  // Print results
  long seconds = end.tv_sec - begin.tv_sec;
  long microseconds = end.tv_usec - begin.tv_usec;
  double elapsed = seconds * 1e-6 + microseconds; // in microseconds
  printf("[CPU_TIME]: %s \tComputational mode: %s  \t%.2f microseconds \n",
         __FUNCTION__, comp_mode.c_str(), elapsed);
  double omp_elapse = (wt2 - wt1) * 1e-6;
  printf("[OMP_TIME]: %s \tComputational mode: %s  \t%.2f microseconds \n",
         __FUNCTION__, comp_mode.c_str(), omp_elapse);
}

/**
 * @brief calculate_total_census calculate total number of census people
 * @param content vector of recount elements
 * @param comp_mode is the computational mode, it can be: sequential or parallel
 * @return number of census people in total
 */
int calculate_total_census(vector<recount> content, string comp_mode)
{
  // Init variables
  recount r = recount();
  struct timeval begin, end;
  double wt1 = 0, wt2 = 0;
  int total = 0;
  int census = 0;

  wt1 = omp_get_wtime();
  gettimeofday(&begin, 0);
  // Sequential mode
  if (comp_mode == "sequential")
  {
    for (size_t i = 0; i < content.size(); i++)
    {
      r = content[i];
      census = r.get_census();
      total += census;
    }
  }
  // Parallel mode
  else if (comp_mode == "parallel")
  {
#pragma omp parallel for shared(content) private(r, census) reduction(+ : total)
    for (size_t i = 0; i < content.size(); i++)
    {
      r = content[i];
      census = r.get_census();
      total += census;
    }
  }
  else
  {
    printf("[ERROR]: Not valid computational mode in %s. Only: sequential and "
           "parallel\n",
           __FUNCTION__);
    throw("ERROR");
  }
  gettimeofday(&end, 0);
  wt2 = omp_get_wtime();

  // Print results
  long seconds = end.tv_sec - begin.tv_sec;
  long microseconds = end.tv_usec - begin.tv_usec;
  double elapsed = seconds * 1e-6 + microseconds; // in microseconds
  printf("[CPU_TIME]: %s \tComputational mode: %s  \t%.2f microseconds \n",
         __FUNCTION__, comp_mode.c_str(), elapsed);
  double omp_elapse = (wt2 - wt1) * 1e-6;
  printf("[OMP_TIME]: %s \tComputational mode: %s  \t%.2f microseconds \n",
         __FUNCTION__, comp_mode.c_str(), omp_elapse);
  return total;
}

/**
 * @brief calculate_total_abstention calculate total number of abstentions
 * @param content vector of recount elements
 * @param comp_mode is the computational mode, it can be: sequential or parallel
 * @return number of abstentions in total
 */
int calculate_total_abstention(vector<recount> content, string comp_mode)
{
  // Init variables
  recount r = recount();
  struct timeval begin, end;
  double wt1 = 0, wt2 = 0;
  int total = 0;
  int abstention = 0;

  wt1 = omp_get_wtime();
  gettimeofday(&begin, 0);
  // Sequential mode
  if (comp_mode == "sequential")
  {
    for (size_t i = 0; i < content.size(); i++)
    {
      r = content[i];
      abstention = r.get_abstentions();
      total += abstention;
    }
  }
  // Parallel mode
  else if (comp_mode == "parallel")
  {
#pragma omp parallel for shared(content) private(r, abstention) reduction(+ : total)
    for (size_t i = 0; i < content.size(); i++)
    {
      r = content[i];
      abstention = r.get_abstentions();
      total += abstention;
    }
  }
  else
  {
    printf("[ERROR]: Not valid computational mode in %s. Only: sequential and "
           "parallel\n",
           __FUNCTION__);
    throw("ERROR");
  }
  gettimeofday(&end, 0);
  wt2 = omp_get_wtime();

  // Print results
  long seconds = end.tv_sec - begin.tv_sec;
  long microseconds = end.tv_usec - begin.tv_usec;
  double elapsed = seconds * 1e-6 + microseconds; // in microseconds
  printf("[CPU_TIME]: %s \tComputational mode: %s  \t%.2f microseconds \n",
         __FUNCTION__, comp_mode.c_str(), elapsed);
  double omp_elapse = (wt2 - wt1) * 1e-6;
  printf("[OMP_TIME]: %s \tComputational mode: %s  \t%.2f microseconds \n",
         __FUNCTION__, comp_mode.c_str(), omp_elapse);
  return total;
}

/**
 * @brief get_min_census get the minimum census
 * @param content vector of recount elements
 * @param comp_mode is the computational mode, it can be: sequential or parallel
 * @return recount element with the minimum census
 */
recount get_min_census(vector<recount> content, string comp_mode)
{
  // Init variables
  recount r = recount();
  recount min_r = recount();
  struct timeval begin, end;
  double wt1 = 0, wt2 = 0;
  int min_census = 0;
  int census = 0;

  wt1 = omp_get_wtime();
  gettimeofday(&begin, 0);
  // Sequential mode
  if (comp_mode == "sequential")
  {
    min_r = content[0];
    min_census = min_r.get_census();
    for (size_t i = 1; i < content.size(); i++)
    {
      r = content[i];
      census = r.get_census();
      if (census < min_census)
      {
        min_census = census;
        min_r = r;
      }
    }
  }
  // Parallel mode
  else if (comp_mode == "parallel")
  {
    min_r = content[0];
    min_census = min_r.get_census();
#pragma omp parallel for shared(content, min_r, min_census) private(r, census)
    for (size_t i = 1; i < content.size(); i++)
    {
      r = content[i];
      census = r.get_census();
#pragma omp critical
      {
        if (census < min_census)
        {
          min_census = census;
          min_r = r;
        }
      }
    }
  }
  else
  {
    printf("[ERROR]: Not valid computational mode in %s. Only: sequential and "
           "parallel\n",
           __FUNCTION__);
    throw("ERROR");
  }
  gettimeofday(&end, 0);
  wt2 = omp_get_wtime();

  // Print results
  long seconds = end.tv_sec - begin.tv_sec;
  long microseconds = end.tv_usec - begin.tv_usec;
  double elapsed = seconds * 1e-6 + microseconds; // in microseconds
  printf("[CPU_TIME]: %s \tComputational mode: %s  \t%.2f microseconds \n",
         __FUNCTION__, comp_mode.c_str(), elapsed);
  double omp_elapse = (wt2 - wt1) * 1e-6;
  printf("[OMP_TIME]: %s \tComputational mode: %s  \t%.2f microseconds \n",
         __FUNCTION__, comp_mode.c_str(), omp_elapse);
  return min_r;
}

/**
 * @brief get_max_census get the maximum census
 * @param content vector of recount elements
 * @param comp_mode is the computational mode, it can be: sequential or parallel
 * @return recount element with the maximum census
 */
recount get_max_census(vector<recount> content, string comp_mode)
{
  // Init variables
  recount r = recount();
  recount max_r = recount();
  struct timeval begin, end;
  double wt1 = 0, wt2 = 0;
  int max_census = 0;
  int census = 0;

  wt1 = omp_get_wtime();
  gettimeofday(&begin, 0);
  // Sequential mode
  if (comp_mode == "sequential")
  {
    max_r = content[0];
    max_census = max_r.get_census();
    for (size_t i = 1; i < content.size(); i++)
    {
      r = content[i];
      census = r.get_census();
      if (census > max_census)
      {
        max_census = census;
        max_r = r;
      }
    }
  }
  // Parallel mode
  else if (comp_mode == "parallel")
  {
    max_r = content[0];
    max_census = max_r.get_census();
#pragma omp parallel for shared(content, max_r, max_census) private(r, census)
    for (size_t i = 1; i < content.size(); i++)
    {
      r = content[i];
      census = r.get_census();
#pragma omp critical
      {
        if (census > max_census)
        {
          max_census = census;
          max_r = r;
        }
      }
    }
  }
  else
  {
    printf("[ERROR]: Not valid computational mode in %s. Only: sequential and "
           "parallel\n",
           __FUNCTION__);
    throw("ERROR");
  }
  gettimeofday(&end, 0);
  wt2 = omp_get_wtime();

  // Print results
  long seconds = end.tv_sec - begin.tv_sec;
  long microseconds = end.tv_usec - begin.tv_usec;
  double elapsed = seconds * 1e-6 + microseconds; // in microseconds
  printf("[CPU_TIME]: %s \tComputational mode: %s  \t%.2f microseconds \n",
         __FUNCTION__, comp_mode.c_str(), elapsed);
  double omp_elapse = (wt2 - wt1) * 1e-6;
  printf("[OMP_TIME]: %s \tComputational mode: %s  \t%.2f microseconds \n",
         __FUNCTION__, comp_mode.c_str(), omp_elapse);
  return max_r;
}

/**
 * @brief get_mean_census get the mean census
 * @param content vector of recount elements
 * @param comp_mode is the computational mode, it can be: sequential or parallel
 * @return mean census
 */
float get_mean_p_participation(vector<recount> content, string comp_mode)
{
  // Init variables
  recount r = recount();
  struct timeval begin, end;
  double wt1 = 0, wt2 = 0;
  float mean = 0;
  float sum = 0;
  float p_participation = 0;

  wt1 = omp_get_wtime();
  gettimeofday(&begin, 0);
  // Sequential mode
  if (comp_mode == "sequential")
  {
    for (size_t i = 0; i < content.size(); i++)
    {
      r = content[i];
      p_participation = r.get_p_participation();
      sum += p_participation;
    }
    mean = sum / content.size();
  }
  // Parallel mode
  else if (comp_mode == "parallel")
  {
#pragma omp parallel for shared(content) private(r, p_participation) reduction(+ : sum)
    for (size_t i = 0; i < content.size(); i++)
    {
      r = content[i];
      p_participation = r.get_p_participation();
      sum += p_participation;
    }
    mean = sum / content.size();
  }
  else
  {
    printf("[ERROR]: Not valid computational mode in %s. Only: sequential and "
           "parallel\n",
           __FUNCTION__);
    throw("ERROR");
  }
  gettimeofday(&end, 0);
  wt2 = omp_get_wtime();

  // Print results
  long seconds = end.tv_sec - begin.tv_sec;
  long microseconds = end.tv_usec - begin.tv_usec;
  double elapsed = seconds * 1e-6 + microseconds; // in microseconds
  printf("[CPU_TIME]: %s \tComputational mode: %s  \t%.2f microseconds \n",
         __FUNCTION__, comp_mode.c_str(), elapsed);
  double omp_elapse = (wt2 - wt1) * 1e-6;
  printf("[OMP_TIME]: %s \tComputational mode: %s  \t%.2f microseconds \n",
         __FUNCTION__, comp_mode.c_str(), omp_elapse);
  return mean;
}

/**
 * @brief get_mean_p_abstention get the mean abstention
 * @param content vector of recount elements
 * @param comp_mode is the computational mode, it can be: sequential or parallel
 * @return mean abstention
 */
float get_mean_p_abstention(vector<recount> content, string comp_mode)
{
  // Init variables
  recount r = recount();
  struct timeval begin, end;
  double wt1 = 0, wt2 = 0;
  float mean = 0;
  float sum = 0;
  float p_abstention = 0;

  wt1 = omp_get_wtime();
  gettimeofday(&begin, 0);
  // Sequential mode
  if (comp_mode == "sequential")
  {
    for (size_t i = 0; i < content.size(); i++)
    {
      r = content[i];
      p_abstention = r.get_p_abstention();
      sum += p_abstention;
    }
    mean = sum / content.size();
  }
  // Parallel mode
  else if (comp_mode == "parallel")
  {
#pragma omp parallel for shared(content) private(r, p_abstention) reduction(+ : sum)
    for (size_t i = 0; i < content.size(); i++)
    {
      r = content[i];
      p_abstention = r.get_p_abstention();
      sum += p_abstention;
    }
    mean = sum / content.size();
  }
  else
  {
    printf("[ERROR]: Not valid computational mode in %s. Only: sequential and "
           "parallel\n",
           __FUNCTION__);
    throw("ERROR");
  }
  gettimeofday(&end, 0);
  wt2 = omp_get_wtime();

  // Print results
  long seconds = end.tv_sec - begin.tv_sec;
  long microseconds = end.tv_usec - begin.tv_usec;
  double elapsed = seconds * 1e-6 + microseconds; // in microseconds
  printf("[CPU_TIME]: %s \tComputational mode: %s  \t%.2f microseconds \n",
         __FUNCTION__, comp_mode.c_str(), elapsed);
  double omp_elapse = (wt2 - wt1) * 1e-6;
  printf("[OMP_TIME]: %s \tComputational mode: %s  \t%.2f microseconds \n",
         __FUNCTION__, comp_mode.c_str(), omp_elapse);
  return mean;
}
