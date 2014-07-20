#include <iostream>
#include <string>
#include <map>
#include <boost/shared_ptr.hpp>
#include <vector>
#include <abstract_factory/abstract_factory.hpp>

using namespace std;
namespace
{
    /**
     * Interface for executing commands.
     *
     * Includes mapping to specific command.
     */
    class CommandInterface : public AbstractFactoryMethod<CommandInterface, void*>
    {
        public:
            virtual bool checkArguments(const std::vector<std::string>& args) = 0;
            virtual void execute() = 0;
    };

    typedef boost::shared_ptr<CommandInterface> CommandInterfacePtr;
}

namespace
{
    /**
    */
    class StartCommand : public CommandInterface
    {
        public:
            bool checkArguments(const std::vector<std::string>& args)
            {
                return args.size() == 0;
            }

            static std::string getName()
            {
                return "start";
            }

            static CommandInterfacePtr createInstance(void*)
            {
                return static_cast<CommandInterfacePtr>(new StartCommand());
            }

            virtual void execute() {
                cout << "start" << endl;
            }

        private:
            static SubClassRegistry registry;
    };

    CommandInterface::SubClassRegistry StartCommand::registry(StartCommand::getName(), &StartCommand::createInstance);
}

namespace
{
    /**
     * Interface for selecting drivers.
     *
     * Includes mapping to specific driver.
     */
    class DriverInterface : public AbstractFactoryMethod<DriverInterface, const std::string&>
    {
        public:
            virtual void openDriver() = 0;
    };

    typedef boost::shared_ptr<DriverInterface> DriverInterfacePtr;
}

namespace
{
    /**
    */
    class TestDriver : public DriverInterface
    {
        public:
            TestDriver(const std::string& name)
            {
                name_ = name;
            }

            void openDriver()
            {
                cout << "successfully opened the driver "<< name_ << endl;
                return;
            }

            static std::string getName()
            {
                return "pcan";
            }

            static DriverInterfacePtr createInstance(const std::string& name)
            {
                return static_cast<DriverInterfacePtr>(new TestDriver(name));
            }

        private:
            static SubClassRegistry registry;
            std::string             name_;
    };

    DriverInterface::SubClassRegistry TestDriver::registry(TestDriver::getName(), &TestDriver::createInstance);
}


int main(int argc, char* argv[])
{
    try {
     CommandInterfacePtr cmd = CommandInterface::fromName(argv[1], NULL);
     DriverInterfacePtr driver = DriverInterface::fromName("pcan", "tante emma");

     cmd.get()->execute();

     driver.get()->openDriver();
    }
    catch (...)
    {
        cout << "Oh oh error" << endl;
        return 0;
    }

    return 0;
}
