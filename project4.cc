/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"

// Default Network Topology

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("ThirdScriptExample");

int 
main (int argc, char *argv[])
{
  bool verbose = true;
  uint32_t nWifi = 6;

  CommandLine cmd;
  cmd.AddValue ("nWifi", "Number of wifi STA devices", nWifi);
  cmd.AddValue ("verbose", "Tell echo applications to log if true", verbose);
  cmd.Parse (argc,argv);

  if (nWifi > 18)
    {
      std::cout << "Number of wifi nodes " << nWifi << 
                   " specified exceeds the mobility bounding box" << std::endl;
      exit (1);
    }

  if (verbose)
    {
      LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
      LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
    }

  NodeContainer p2pNodes;
  p2pNodes.Create (2);

  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));

  NetDeviceContainer p2pDevices;
  p2pDevices = pointToPoint.Install (p2pNodes);
  //////////////////////////////////////////////////////////
  NodeContainer wifiStaNodes;
  wifiStaNodes.Create (nWifi);
  NodeContainer wifiApNode = p2pNodes.Get (0);

  YansWifiChannelHelper channel = YansWifiChannelHelper::Default ();
  YansWifiPhyHelper phy = YansWifiPhyHelper::Default ();
  phy.SetChannel (channel.Create ());

  WifiHelper wifi = WifiHelper::Default ();
  wifi.SetRemoteStationManager ("ns3::AarfWifiManager");

  NqosWifiMacHelper mac = NqosWifiMacHelper::Default ();

  Ssid ssid = Ssid ("ns-3-ssid");
  mac.SetType ("ns3::StaWifiMac",
               "Ssid", SsidValue (ssid),
               "ActiveProbing", BooleanValue (false));

  NetDeviceContainer staDevices;
  staDevices = wifi.Install (phy, mac, wifiStaNodes);

  mac.SetType ("ns3::ApWifiMac",
               "Ssid", SsidValue (ssid));

  NetDeviceContainer apDevices;
  apDevices = wifi.Install (phy, mac, wifiApNode);

  MobilityHelper mobility;

  mobility.SetMobilityModel ("ns3::RandomWalk2dMobilityModel","Bounds", RectangleValue (Rectangle (0, 500, 0, 500)));
  mobility.Install (wifiStaNodes);
  
  Ptr<RandomWalk2dMobilityModel> mob0 = wifiStaNodes.Get(0)->GetObject<RandomWalk2dMobilityModel>();
  mob0->SetPosition(Vector(10.0, 10.0, 0.0));
  Ptr<RandomWalk2dMobilityModel> mob1 = wifiStaNodes.Get(1)->GetObject<RandomWalk2dMobilityModel>();
  mob1->SetPosition(Vector(10.0, 20.0, 0.0));
  Ptr<RandomWalk2dMobilityModel> mob2 = wifiStaNodes.Get(2)->GetObject<RandomWalk2dMobilityModel>();
  mob2->SetPosition(Vector(18.66, 25.0, 0.0));
  Ptr<RandomWalk2dMobilityModel> mob3 = wifiStaNodes.Get(3)->GetObject<RandomWalk2dMobilityModel>();
  mob3->SetPosition(Vector(27.32, 20.0, 0.0));
  Ptr<RandomWalk2dMobilityModel> mob4 = wifiStaNodes.Get(4)->GetObject<RandomWalk2dMobilityModel>();
  mob4->SetPosition(Vector(27.32, 10.0, 0.0));
  Ptr<RandomWalk2dMobilityModel> mob5 = wifiStaNodes.Get(5)->GetObject<RandomWalk2dMobilityModel>();
  mob5->SetPosition(Vector(18.66, 5.0, 0.0));

  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility.Install (wifiApNode);
  Ptr<ConstantPositionMobilityModel> mob6 = wifiApNode.Get(0)->GetObject<ConstantPositionMobilityModel>();
  mob6->SetPosition(Vector(18.66, 15.0, 0.0));
  ///////////////////////////////////////////////////
  NodeContainer wifiStaNodes1;
  wifiStaNodes1.Create (nWifi);
  NodeContainer wifiApNode1 = p2pNodes.Get (1);

  YansWifiChannelHelper channel1 = YansWifiChannelHelper::Default ();
  YansWifiPhyHelper phy1 = YansWifiPhyHelper::Default ();
  phy1.SetChannel (channel1.Create ());

  WifiHelper wifi1 = WifiHelper::Default ();
  wifi1.SetRemoteStationManager ("ns3::AarfWifiManager");

  NqosWifiMacHelper mac1 = NqosWifiMacHelper::Default ();

  Ssid ssid1 = Ssid ("ns-3-ssid");
  mac1.SetType ("ns3::StaWifiMac",
               "Ssid", SsidValue (ssid),
               "ActiveProbing", BooleanValue (false));

  NetDeviceContainer staDevices1;
  staDevices1 = wifi1.Install (phy1, mac1, wifiStaNodes1);

  mac1.SetType ("ns3::ApWifiMac",
               "Ssid", SsidValue (ssid));

  NetDeviceContainer apDevices1;
  apDevices1 = wifi1.Install (phy1, mac1, wifiApNode1);

  MobilityHelper mobility1;

  mobility1.SetMobilityModel ("ns3::RandomWalk2dMobilityModel","Bounds", RectangleValue (Rectangle (0, 500, 0, 500)));
  mobility1.Install (wifiStaNodes1);
  
  Ptr<RandomWalk2dMobilityModel> mob10 = wifiStaNodes1.Get(0)->GetObject<RandomWalk2dMobilityModel>();
  mob10->SetPosition(Vector(60.0, 10.0, 0.0));
  Ptr<RandomWalk2dMobilityModel> mob11 = wifiStaNodes1.Get(1)->GetObject<RandomWalk2dMobilityModel>();
  mob11->SetPosition(Vector(60.0, 20.0, 0.0));
  Ptr<RandomWalk2dMobilityModel> mob12 = wifiStaNodes1.Get(2)->GetObject<RandomWalk2dMobilityModel>();
  mob12->SetPosition(Vector(68.66, 25.0, 0.0));
  Ptr<RandomWalk2dMobilityModel> mob13 = wifiStaNodes1.Get(3)->GetObject<RandomWalk2dMobilityModel>();
  mob13->SetPosition(Vector(77.32, 20.0, 0.0));
  Ptr<RandomWalk2dMobilityModel> mob14 = wifiStaNodes1.Get(4)->GetObject<RandomWalk2dMobilityModel>();
  mob14->SetPosition(Vector(77.32, 10.0, 0.0));
  Ptr<RandomWalk2dMobilityModel> mob15 = wifiStaNodes1.Get(5)->GetObject<RandomWalk2dMobilityModel>();
  mob15->SetPosition(Vector(68.66, 5.0, 0.0));

  mobility1.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility1.Install (wifiApNode1);
  Ptr<ConstantPositionMobilityModel> mob16 = wifiApNode1.Get(0)->GetObject<ConstantPositionMobilityModel>();
  mob16->SetPosition(Vector(68.66, 15.0, 0.0));

 ///////////////////////////////////////////////////
  InternetStackHelper stack;
  stack.Install (wifiApNode);
  stack.Install (wifiStaNodes);
  stack.Install (wifiApNode1);
  stack.Install (wifiStaNodes1);

  Ipv4AddressHelper address;

  address.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer p2pInterfaces;
  p2pInterfaces = address.Assign (p2pDevices);

  address.SetBase ("10.1.2.0", "255.255.255.0");
  address.Assign (staDevices);
  address.Assign (apDevices);

  address.SetBase ("10.1.3.0", "255.255.255.0");
  address.Assign (staDevices1);
  address.Assign (apDevices1);

  UdpEchoServerHelper echoServer (9);

  ApplicationContainer serverApps = echoServer.Install (wifiApNode1.Get (0));
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (10.0));

  UdpEchoClientHelper echoClient (p2pInterfaces.GetAddress (1), 9);
  echoClient.SetAttribute ("MaxPackets", UintegerValue (3));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (0.1)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (512));

  ApplicationContainer clientApps = 
    echoClient.Install (wifiStaNodes.Get (nWifi - 1));
  clientApps.Start (Seconds (2.0));
  clientApps.Stop (Seconds (10.0));

  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  Simulator::Stop (Seconds (10.0));

  pointToPoint.EnablePcapAll ("lastp2p");
  phy.EnablePcap ("lastphy", staDevices.Get (0));
  phy1.EnablePcap ("lastphy1", staDevices1.Get (0));

  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
