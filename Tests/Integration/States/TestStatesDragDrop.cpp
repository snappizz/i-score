#include <IscoreIntegrationTests.hpp>
#include <Mocks/MockDevice.hpp>

class TestStatesDragDrop: public IscoreTestBase
{
        Q_OBJECT
    public:
        TestStatesDragDrop(int& argc, char** argv):
            IscoreTestBase(argc, argv)
        {
            SingletonProtocolList::instance().registerFactory(new MockDeviceFactory);
        }

        void setupDevice()
        {
            // We load a device
            iscore::DeviceSettings s;
            s.protocol = "Mock";
            s.name = "MockDevice";

            iscore::Node n{s, nullptr};
            loadDeviceFromXML("TestData/test.namespace.xml", n);
            redo(new LoadDevice{pluginModel<DeviceDocumentPlugin>(), std::move(n)});
        }

    private slots:
        void testDragUndoRedo()
        {
            // We add a constraint
            using namespace Scenario::Command;
            auto& scenar = static_cast<ScenarioModel&>(*getBaseElementModel().baseConstraint().processes.begin());
            auto newStateCmd = new CreateState(scenar, scenar.startEvent().id(), 0);
            redo(newStateCmd);

            iscore::Address addr{"MockDevice", {"test1"}};

            auto& stateMessages = scenar.states.at(newStateCmd->createdState()).messages();
            auto addStartState = new AddMessagesToModel{
                                     stateMessages,
                                     iscore::MessageList{iscore::Message{addr, -30.}}};
            redo(addStartState);

            QVERIFY(stateMessages.rootNode().childCount() == 1);

            auto& dev_node = stateMessages.rootNode().childAt(0);
            QVERIFY(dev_node.is<iscore::DeviceSettings>());

            auto& dev_var = dev_node.get<iscore::DeviceSettings>();
            QVERIFY(dev_var.name == addr.device);

            QVERIFY(dev_node.childCount() == 1);

            auto& addr_node = dev_node.childAt(0);
            QVERIFY(addr_node.is<iscore::AddressSettings>());
            auto& addr_var = addr_node.get<iscore::AddressSettings>();
            QVERIFY(addr_var.name == "test1");
            QVERIFY(addr_var.value.val == -30.);

            undo();

            QVERIFY(stateMessages.rootNode().childCount() == 0);
        }

        void testDragUndoRedoWithDevice()
        {
            setupDevice();

            testDragUndoRedo();
        }

};

ISCORE_INTEGRATION_TEST(TestStatesDragDrop)

#include "TestStatesDragDrop.moc"