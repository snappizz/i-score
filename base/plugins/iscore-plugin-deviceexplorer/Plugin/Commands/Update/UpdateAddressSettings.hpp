#pragma once
#include <iscore/command/SerializableCommand.hpp>
#include <iscore/tools/ModelPath.hpp>
#include <DeviceExplorer/Address/AddressSettings.hpp>
#include <DeviceExplorer/NodePath.hpp>

class DeviceDocumentPlugin;

namespace DeviceExplorer
{
namespace Command
{
class UpdateAddressSettings : public iscore::SerializableCommand
{
        ISCORE_COMMAND_DECL2("DeviceExplorerControl", "UpdateAddressSettings", "UpdateAddressSettings")
        public:
            ISCORE_SERIALIZABLE_COMMAND_DEFAULT_CTOR2(UpdateAddressSettings)
          UpdateAddressSettings(
            ModelPath<DeviceDocumentPlugin>&& device_tree,
            const NodePath &node,
            const iscore::AddressSettings& parameters);


        virtual void undo() override;
        virtual void redo() override;

    protected:
        virtual void serializeImpl(QDataStream&) const override;
        virtual void deserializeImpl(QDataStream&) override;

    private:
        ModelPath<DeviceDocumentPlugin> m_devicesModel;

        NodePath m_node;

        iscore::AddressSettings m_oldParameters;
        iscore::AddressSettings m_newParameters;
};
}
}