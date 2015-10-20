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
#include <boost/thread/thread.hpp>
#include <boost/date_time.hpp>

namespace recording_toolkit {
class Recorder {
 public:
  Recorder();
  virtual ~Recorder();

  virtual uint32_t FormatPrintStyle();
  virtual uint32_t StartRecord();
  virtual uint32_t StopRecord();
};

class TimeSeriesRecorder : public Recorder {
 public:
  TimeSeriesRecorder();
  virtual ~TimeSeriesRecorder();
};
}  // namespace recording_toolkit
#endif  // INCLUDE_TIMESERIES_RECORDING_TOOLKIT_RECORD_TIMESERIES_DATA_TO_FILE_H_
