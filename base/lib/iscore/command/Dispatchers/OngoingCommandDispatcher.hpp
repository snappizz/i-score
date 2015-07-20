#pragma once
#include <iscore/command/Dispatchers/ICommandDispatcher.hpp>
#include <iscore/command/Dispatchers/SendStrategy.hpp>

#include <core/command/CommandStack.hpp>

class OngoingCommandDispatcher : public ICommandDispatcher
{
    public:
        OngoingCommandDispatcher(iscore::CommandStack& stack):
            ICommandDispatcher{stack}
        {

        }

        template<typename TheCommand, typename... Args> // TODO split in two ?
        void submitCommand(Args&&... args)
        {
            if(!m_cmd)
            {
                m_cmd = std::make_unique<TheCommand>(std::forward<Args>(args)...);
                m_cmd->redo();
            }
            else
            {
                Q_ASSERT(m_cmd->uid() == TheCommand::static_uid());
                static_cast<TheCommand*>(m_cmd.get())->update(std::forward<Args>(args)...);
                m_cmd->redo();
            }
        }

        void commit()
        {
            if(m_cmd)
                SendStrategy::Simple::send(stack(), m_cmd.release());
        }

        void rollback()
        {
            m_cmd->undo();
            m_cmd.reset();
        }

    private:
        std::unique_ptr<iscore::SerializableCommand> m_cmd;
};