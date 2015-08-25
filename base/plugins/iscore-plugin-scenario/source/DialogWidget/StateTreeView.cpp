#include "StateTreeView.hpp"

#include <DeviceExplorer/../Plugin/Widgets/MessageWidget.hpp>
#include <State/StateItemModel.hpp>
#include <Commands/Event/State/AssignMessagesToState.hpp>
#include <iscore/document/DocumentInterface.hpp>
#include "Document/State/StateModel.hpp"
#include <core/document/Document.hpp>
StateTreeView::StateTreeView(const StateModel& model,
        DeviceExplorerModel* devexplorer,
        QWidget* parent):
    QTreeView{parent},
    m_model{const_cast<StateModel*>(&model)}, // sorry o lord for I have sinned
    m_devExplorer{devexplorer},
    m_dispatcher{iscore::IDocument::documentFromObject(*m_model)->commandStack()}
{
    this->setModel(&m_model->states());
}

void StateTreeView::mouseDoubleClickEvent(QMouseEvent* ev)
{
    QTreeView::mouseDoubleClickEvent(ev);
    auto index = selectedIndexes().first();

    auto node = index.isValid()
                ? static_cast<iscore::StateNode*>(index.internalPointer())
                : nullptr;

    if(node->is<iscore::MessageList>())
    {
        MessageListEditor ed(node->get<iscore::MessageList>(), m_devExplorer, this);
        int ret = ed.exec();

        if(ret)
        {
            auto cmd = new Scenario::Command::AssignMessagesToState{
                       iscore::IDocument::safe_path(*m_model),
                       iscore::StatePath(*node),
                       ed.messages()};

            m_dispatcher.submitCommand(cmd);
        }
    }
    else
    {
        ISCORE_TODO;
    }

}