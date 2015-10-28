#pragma once
#include <ProcessInterface/Process.hpp>
#include "TimeProcessWithConstraint.hpp"
#include <memory>

class OSSIAProcessModel : public Process
{
    public:
        using Process::Process;
        virtual std::shared_ptr<TimeProcessWithConstraint> process() const = 0;
};