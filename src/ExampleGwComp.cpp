#include <iostream>
#include <string>
#include <stdlib.h>

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/lexical_cast.hpp>

#include <rtm/idl/BasicDataTypeSkel.h>

#include "ros/ros.h"
#include "std_msgs/Int32.h"

#include "Gateway.h"

using namespace boost;
using namespace std;
using namespace std_msgs;
using namespace RTC;
using namespace GatewayFactory;

static const char* gateway_spec[] = { //
    //
        "implementation_id", "ExampleGw", //
        "type_name", "ExampleGw", //
        "description", "An example gateway module", //
        "version", "1.0.0", //
        "vendor", "Gabor Juhasz", //
        "category", "Category", //
        "activity_type", //
        "PERIODIC", //
        "kind", "DataFlowComponent", //
        "max_instance", "1", //
        "language", "C++", //
        "lang_type", "compile", //
        "" };

void convertRosToRtm(const shared_ptr<Int32 const>& in,
    TimedLong& out) {
  out.data = in->data;
}

void convertRtmToRos(const TimedLong& in, Int32& out) {
  out.data = in.data;
}

void callbackRosToRtm(const shared_ptr<Int32 const>&, TimedLong&,
    const RosToRtmLink<TimedLong>&);

void callbackRtmToRos(TimedLong&, Int32&,
    const RtmToRosLink<TimedLong>&);

int main(int argc, char** argv) {
  cout << "Starting" << endl;
  ros::init(argc, argv, "Gateway",
      ros::init_options::NoSigintHandler);

  GatewayFactory::Config config(gateway_spec);

  RosToRtmHandler<Int32, TimedLong> handler1(&convertRosToRtm,
      &callbackRosToRtm);
  config.addNewRosToRtmLink<Int32, TimedLong>("ros_to_rtm", handler1);

  RtmToRosHandler<TimedLong, Int32> handler2(&convertRtmToRos,
      &callbackRtmToRos);
  config.addNewRtmToRosLink<TimedLong, Int32>("rtm_to_ros", handler2);

  createNewGateway<Gateway>(argc, argv, "ExampleGw", config, true);

  return 0;
}

void callbackRosToRtm(const shared_ptr<Int32 const>& in,
    TimedLong& out, const RosToRtmLink<TimedLong>& link) {
  cout << "[";
  cout << link.name.c_str();
  cout << "] : [";
  cout << lexical_cast<string>(in->data).c_str();
  cout << "]->[";
  cout << lexical_cast<string>(out.data).c_str() << "]";
  cout << endl;
}

void callbackRtmToRos(TimedLong& in, Int32& out,
    const RtmToRosLink<TimedLong>& link) {
  cout << "[";
  cout << link.name.c_str();
  cout << "] : [";
  cout << lexical_cast<string>(in.data).c_str();
  cout << "]->[";
  cout << lexical_cast<string>(out.data).c_str() << "]";
  cout << endl;
}
