#pragma once
#include <iscore/tools/NamedObject.hpp>
#include <iscore/tools/SettableIdentifier.hpp>
#include <ProcessInterface/ZoomHelper.hpp>

class DeckModel;
class DeckView;
class ICommandDispatcher;
namespace iscore
{
    class SerializableCommand;
}
class ProcessPresenterInterface;
class ProcessSharedModelInterface;
class ProcessViewModelInterface;
class ProcessViewInterface;
class BoxView;
class DeckPresenter : public NamedObject
{
        Q_OBJECT

    public:
        DeckPresenter(DeckModel* model,
                      BoxView* view,
                      QObject* parent);
        virtual ~DeckPresenter();

        id_type<DeckModel> id() const;
        const DeckModel& model() const;
        int height() const; // Return the height of the view

        void setWidth(double w);
        void setVerticalPosition(double h);

        // Sets the enabled - disabled graphism for
        // the deck move tool
        void enable();
        void disable();

    signals:
        void askUpdate();

    public slots:
        // From Model
        void on_processViewModelCreated(id_type<ProcessViewModelInterface> processId);
        void on_processViewModelDeleted(id_type<ProcessViewModelInterface> processId);
        void on_processViewModelSelected(id_type<ProcessViewModelInterface> processId);
        void on_heightChanged(double height);
        void on_parentGeometryChanged();

        void on_zoomRatioChanged(ZoomRatio);

    private:
        void on_processViewModelCreated_impl(ProcessViewModelInterface*);

        void updateProcessesShape();

        DeckModel* m_model{};
        DeckView* m_view{};
        QVector<QPair<ProcessPresenterInterface*, ProcessViewInterface*>> m_processes;

        // Maybe move this out of the state of the presenter ?
        int m_currentResizingValue {}; // Used when the deckView is being resized.

        ZoomRatio m_zoomRatio {};
};

