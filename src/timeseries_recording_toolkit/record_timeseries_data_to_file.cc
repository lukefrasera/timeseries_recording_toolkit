/*
timeseries_recording_toolkit
Copyright (C) 2015  Luke Fraser

timeseries_recording_toolkit is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

timeseries_recording_toolkit is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with timeseries_recording_toolkit.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "timeseries_recording_toolkit/record_timeseries_data_to_file.h"

namespace recording_toolkit {
typedef enum {
  SUCCESS = 1,
  NOT_RECORDING,
} error_recording;

PrintRecorder::PrintRecorder(
    const char *filename,
    bool output_screen,
    uint32_t queue_size) {

  screen_ = output_screen;
  printing_thread = NULL;
  file_.open(filename, std::fstream::out);
  queue_size_ = queue_size;
}
PrintRecorder::~PrintRecorder() {
  if (printing_thread)
    delete printing_thread;
}

uint32_t PrintRecorder::RecordPrintf(const char *fmt, ...) {
  // Generate String to Add to file
  if (!recording_)
    return NOT_RECORDING;
  // va_list args;
  // va_start(args, fmt);
  // int size = vsnprintf(NULL, 0, fmt, args);
  // va_end(args);

  // char *buffer = new char[size];
  // va_start(args, fmt);
  // vsprintf(buffer, fmt, args);
  // printf("%s\n", buffer);
  queue_access.lock();
  thread_queue_.push("hello I am here");
  queue_access.unlock();
  // va_end(args);
  // delete [] buffer;
  return SUCCESS;
}

void PrintRecorder::Worker(PrintRecorder *object) {
  bool result;
  while(true) {
    result = object->RecordingWorker();
    if (!result)
      boost::this_thread::sleep(boost::posix_time::milliseconds(100));
  }
}

uint32_t PrintRecorder::RecordingWorker() {
  std::string front;
  static uint32_t count = 0;
  uint32_t result;
  if (thread_queue_.size() >= queue_size_) {
    for (int i = 0; i < queue_size_; ++i) {
      // queue_access.lock();
      front = thread_queue_.front();
      // queue_access.unlock();
      printf("%s\n", front.c_str());
      queue_access.lock();
      thread_queue_.pop();
      queue_access.unlock();
      result = true;
      count = 0;
    } 
  } else if (thread_queue_.size() > 0 && count > queue_size_) {
    front = thread_queue_.front();
    printf("%s\n", front.c_str());
    queue_access.lock();
    thread_queue_.pop();
    queue_access.unlock();
    result = true;
  } else if (thread_queue_.size() == 0) {
    count = 0;
    result = false;
  } else {
    result = false;
    count++;
  }
  //return result;
}

uint32_t PrintRecorder::StartRecord() {
  printing_thread = new boost::thread(PrintRecorder::Worker, this);
  recording_ = true;
}
uint32_t PrintRecorder::StopRecord() {
  delete printing_thread;
  printing_thread = NULL;
  recording_ = false;
}
}  // namespace recording_toolkit
