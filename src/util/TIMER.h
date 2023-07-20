/*
This file is part of HOBAK.

Permission is hereby granted to use this software solely for non-commercial applications
and purposes including academic or industrial research, evaluation and not-for-profit media
production.
 
THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT
NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS
FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL PIXAR OR ITS AFFILIATES, YALE, OR
THE AUTHORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <string>
#include <map>
#include <stack>

#include <chrono>

// To time a function, just put:
//
//  TIMER functionTimer(__FUNCTION__);
//
// at the beginning of the function

class TIMER
{
    using time_clock = std::chrono::high_resolution_clock;
    using time_point = std::chrono::time_point<time_clock>;
public:
  // start the timer by default -- if a tick is called later,
  // it will just stomp it
  TIMER(std::string blockName); 
  ~TIMER();

  // stop the timer manually
  void stop();

  static double timing(time_point& begin = _tick, time_point& end  = _tock) {
    return std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() * 1e-6;
  };
  static int hours(int seconds) { return seconds / (60 * 60); };
  static int minutes(int seconds) {
   int mod = seconds % (60 * 60);
   return mod / 60;
  };
  static int seconds(int seconds) {
    int mod = seconds % (60 * 60);
    return mod % 60;
  };

  static void printTimings();
  static void printTimingsPerFrame(const int frames);

private:
  // begin and end of current block being timed
  static time_point _tick;
  static time_point _tock;

  // hash table of all timings
  static std::map<std::string, double> _timings;

  // call stack
  static std::stack<std::string> _callStack;

  // track whether it was stopped already so we don't
  // stop it twice
  bool _stopped;
};

#endif
