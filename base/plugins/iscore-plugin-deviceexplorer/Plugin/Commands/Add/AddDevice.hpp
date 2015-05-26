#pragma once
#include <iscore/command/SerializableCommand.hpp>
#include <iscore/tools/ObjectPath.hpp>
#include <DeviceExplorer/Protocol/DeviceSettings.hpp>

class AddDevice : public iscore::SerializableCommand
{
        ISCORE_COMMAND
        public:
            ISCORE_SERIALIZABLE_COMMAND_DEFAULT_CTOR(AddDevice, "DeviceExplorerControl")
        AddDevice(ObjectPath&& device_tree,
                  const DeviceSettings& parameters,
                  const QString& filePath = QString(""));


        virtual void undo() override;
        virtual void redo() override;

    protected:
        virtual void serializeImpl(QDataStream&) const override;
        virtual void deserializeImpl(QDataStream&) override;

    private:
        ObjectPath m_deviceTree;
        DeviceSettings m_parameters;
        QString m_filePath{};

        int m_row{};
};