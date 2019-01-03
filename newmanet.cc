#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/wifi-module.h"
#include "ns3/internet-module.h"
#include "ns3/applications-module.h"
#include "ns3/dsdv-module.h"
#include "ns3/aodv-module.h"
#include "ns3/dsr-module.h"
#include "ns3/netanim-module.h"

#include <time.h>

using namespace ns3;

int main(int argc, char *argv[])
{
  std::string phyMode("DsssRate2Mbps");
  int nodeNumber = 5;
  double simTime = 200.0;
  uint16_t port = 6000;
  Time interPacketInterval = Seconds(1);

  NodeContainer nodes;
  nodes.Create(nodeNumber);

  WifiHelper wifi;
  wifi.SetStandard(WIFI_PHY_STANDARD_80211b);

  YansWifiPhyHelper wifiPhy =  YansWifiPhyHelper::Default();
  wifiPhy.SetPcapDataLinkType(YansWifiPhyHelper::DLT_IEEE802_11_RADIO);


  YansWifiChannelHelper wifiChannel = YansWifiChannelHelper::Default();
  wifiPhy.SetChannel(wifiChannel.Create());

  NqosWifiMacHelper wifiMac = NqosWifiMacHelper::Default();
  wifi.SetRemoteStationManager("ns3::ConstantRateWifiManager",
                               "DataMode", StringValue(phyMode),
                                                           "ControlMode", StringValue(phyMode));

  wifiMac.SetType("ns3::AdhocWifiMac");
  NetDeviceContainer devices = wifi.Install(wifiPhy, wifiMac, nodes);


  MobilityHelper mobility;

  Ptr<ListPositionAllocator> positionAlloc1 = CreateObject<ListPositionAllocator> ();

  //positionAlloc1->Add (Vector (100.0, 0.0, 0.0));
 
  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility.Install(nodes.Get(0));

  mobility.SetPositionAllocator(positionAlloc1);

  ObjectFactory pos;
  pos.SetTypeId ("ns3::RandomRectanglePositionAllocator");
  pos.Set ("X", StringValue ("ns3::UniformRandomVariable[Min=0.0|Max=300.0]"));
  pos.Set ("Y", StringValue ("ns3::UniformRandomVariable[Min=0.0|Max=500.0]"));
  Ptr<PositionAllocator> taPositionAlloc = pos.Create ()->GetObject<PositionAllocator> ();

  mobility.SetMobilityModel ("ns3::RandomWaypointMobilityModel",
                             "Speed", StringValue ("ns3::UniformRandomVariable[Min=0.0|Max=40.0]"),
                             "Pause", StringValue ("ns3::UniformRandomVariable[Min=0.0|Max=5.0]"),
                             "PositionAllocator", PointerValue (taPositionAlloc)
                             );
  mobility.SetPositionAllocator(taPositionAlloc);
  mobility.Install(nodes.Get(1));
  mobility.Install(nodes.Get(2));
   mobility.Install(nodes.Get(3));
   mobility.Install(nodes.Get(4));

  InternetStackHelper internet;
  DsdvHelper dsdv;
  internet.SetRoutingHelper(dsdv);
  internet.Install(nodes);
  /*
  AodvHelper aodv;
  internet.SetRoutingHelper(aodv);
  internet.Install(nodes);
  */
 
  Ipv4AddressHelper ipv4;
  ipv4.SetBase("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer i = ipv4.Assign(devices);

  UdpServerHelper server(port);
  ApplicationContainer apps = server.Install(nodes.Get(0));
  apps.Start(Seconds(1.0));
  apps.Stop(Seconds(simTime));

  UdpClientHelper client(i.GetAddress(0), port);
  client.SetAttribute("PacketSize", UintegerValue(1024));
  client.SetAttribute("Interval",TimeValue(interPacketInterval));
  apps = client.Install(nodes.Get(19));
  apps.Start(Seconds(1.0));
  apps.Stop(Seconds(simTime));
 

  wifiPhy.EnablePcapAll("manet-test");
  wifiPhy.EnableAsciiAll("manet-test");
  AnimationInterface anim("manet-test.xml");

  Simulator::Stop(Seconds(simTime));
  Simulator::Run ();
  Simulator::Destroy ();

  return 0;
}
