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
#ifndef INCLUDE_TIMESERIES_RECORDING_TOOLKIT_RECORD_TIMESERIES_DATA_TO_FILE_H_
#define INCLUDE_TIMESERIES_RECORDING_TOOLKIT_RECORD_TIMESERIES_DATA_TO_FILE_H_
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <string>
#include <fstream>
#include <queue>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/date_time.hpp>

namespace recording_toolkit {
class PrintRecorder {
 public:
  PrintRecorder(const char *filename,
                bool output_screen=false,
                uint32_t queue_size=2048);
  virtual ~PrintRecorder();

  virtual uint32_t RecordPrintf(const char *fmt, ...);
  virtual uint32_t StartRecord();
  virtual uint32_t StopRecord();
 private:
  static void Worker(PrintRecorder *object);
  virtual uint32_t RecordingWorker();
  virtual void ProcessBufferQueue(std::queue<std::string> *buffer);
  bool recording_;
  bool screen_;
  std::fstream file_;
  std::queue<std::string> *thread_queue_ptr_, *thread_queue_buffer_ptr_;
  std::queue<std::string> queues[2];
  uint32_t queue_size_;

  boost::thread *printing_thread;
  boost::mutex queue_access;
};

// class WatchRecorder {
//  public:
//   Recorder();
//   virtual ~Recorder(const char *filename,
//                     bool output_screen=false,
//                     uint32_t queue_size=64);

//   virtual uint32_t FormatStringPointers(const char *fmt, ...);
//   virtual uint32_t StartRecord();
//   virtual uint32_t StopRecord();
//  private:
//   bool recording;
// };

// class TimeSeriesRecorder : public WatchRecorder {
//  public:
//   TimeSeriesRecorder();
//   virtual ~TimeSeriesRecorder();
// };
}  // namespace recording_toolkit
#endif  // INCLUDE_TIMESERIES_RECORDING_TOOLKIT_RECORD_TIMESERIES_DATA_TO_FILE_H_
