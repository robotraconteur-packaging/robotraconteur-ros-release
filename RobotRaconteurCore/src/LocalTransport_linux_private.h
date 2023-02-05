#include "RobotRaconteur/LocalTransport.h"
#include "RobotRaconteur/ASIOStreamBaseTransport.h"
#include "LocalTransport_discovery_private.h"

#include <boost/filesystem.hpp>

#pragma once

namespace RobotRaconteur
{
namespace detail
{
namespace LocalTransportUtil
{
class FD;
}

class LinuxLocalTransportDiscovery_dir
{
  public:
    boost::filesystem::path path;
    int notify_fd;
    int dir_wd;
    int bynodeid_wd;
    int bynodename_wd;

    LinuxLocalTransportDiscovery_dir();
    ~LinuxLocalTransportDiscovery_dir();
    bool Init(const boost::filesystem::path& path);
    bool Refresh();
};

class LinuxLocalTransportDiscovery : public LocalTransportDiscovery,
                                     public RR_ENABLE_SHARED_FROM_THIS<LinuxLocalTransportDiscovery>
{
  public:
    LinuxLocalTransportDiscovery(const RR_SHARED_PTR<RobotRaconteurNode>& node);
    RR_OVIRTUAL void Init() RR_OVERRIDE;
    RR_OVIRTUAL void Shutdown() RR_OVERRIDE;
    RR_OVIRTUAL ~LinuxLocalTransportDiscovery() RR_OVERRIDE;

    void run();
    bool update_public();
    void refresh_public();

  protected:
    RR_SHARED_PTR<LocalTransportUtil::FD> shutdown_evt;
    RR_SHARED_PTR<LinuxLocalTransportDiscovery_dir> private_dir;
    RR_SHARED_PTR<LocalTransportUtil::FD> public_evt;
    int public_wd;
    std::map<std::string, RR_SHARED_PTR<LinuxLocalTransportDiscovery_dir> > public_user_dirs;
    boost::thread poll_thread;
    NodeDirectories node_dirs;
};
} // namespace detail
} // namespace RobotRaconteur
