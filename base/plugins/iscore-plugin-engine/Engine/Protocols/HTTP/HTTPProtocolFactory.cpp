#include <QObject>


#include <Device/Protocol/DeviceSettings.hpp>
#include "HTTPDevice.hpp"
#include "HTTPProtocolFactory.hpp"
#include <Engine/Protocols/HTTP/HTTPProtocolSettingsWidget.hpp>
#include <Engine/Protocols/HTTP/HTTPSpecificSettings.hpp>

namespace Device
{
class DeviceInterface;
class ProtocolSettingsWidget;
}

struct VisitorVariant;

namespace Engine
{
namespace Network
{
QString HTTPProtocolFactory::prettyName() const
{
    return QObject::tr("HTTP");
}

Device::DeviceInterface* HTTPProtocolFactory::makeDevice(
        const Device::DeviceSettings& settings,
        const iscore::DocumentContext& ctx)
{
    return new HTTPDevice{settings};
}

const Device::DeviceSettings& HTTPProtocolFactory::defaultSettings() const
{
    static const Device::DeviceSettings settings = [&] () {
        Device::DeviceSettings s;
        s.protocol = concreteFactoryKey();
        s.name = "HTTP";
        HTTPSpecificSettings specif;
        s.deviceSpecificSettings = QVariant::fromValue(specif);
        return s;
    }();
    return settings;
}

Device::ProtocolSettingsWidget* HTTPProtocolFactory::makeSettingsWidget()
{
    return new HTTPProtocolSettingsWidget;
}

QVariant HTTPProtocolFactory::makeProtocolSpecificSettings(const VisitorVariant& visitor) const
{
    return makeProtocolSpecificSettings_T<HTTPSpecificSettings>(visitor);
}

void HTTPProtocolFactory::serializeProtocolSpecificSettings(const QVariant& data, const VisitorVariant& visitor) const
{
    serializeProtocolSpecificSettings_T<HTTPSpecificSettings>(data, visitor);
}

bool HTTPProtocolFactory::checkCompatibility(const Device::DeviceSettings& a, const Device::DeviceSettings& b) const
{
    return a.name != b.name;
}
}
}
