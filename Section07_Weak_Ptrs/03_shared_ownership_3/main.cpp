/**
 * @file    main.cpp
 * @brief   Demonstrates a shared resource observed by another class using raw pointers,
 *          setting the stage for std::weak_ptr to prevent dangling pointers.
 * @author  Mohamed Atef
 * @date    2026-05-27
 */

/*===========================================================================*
 *                          F I L E  I N C L U S I O N S                     *
 *===========================================================================*/
#ifdef _MSC_VER
    #include <crtdbg.h>
#else
    #include <windows.h>
#endif
#include <iostream>
#include <memory>
#include <string>
using namespace std;

/*===========================================================================*
 *                     M A C R O S  &  F U N C T I O N - L I K E             *
 *                              M A C R O S                                  *
 *===========================================================================*/
/* None */

/*===========================================================================*
 *                           U S E R  T Y P E S                              *
 *===========================================================================*/
/**
 * @brief Represents a string resource that can be printed.
 */
class Resource
{
    string mData{};

public:
    /**
     * @brief Constructs a Resource with the given data.
     * @param data The initial string data.
     */
    Resource(const string &data) : mData(data)
    {

    }

    /**
     * @brief Gets the underlying data of the resource.
     * @return A constant reference to the string data.
     */
    const string &GetData() const
    {
        return mData;
    }

    /**
     * @brief Sets the underlying data of the resource.
     * @param data The new string data to set.
     */
    void SetData(const string &data)
    {
        mData = data;
    }
};

/**
 * @brief Prints the Resource data to the console in a formatted box.
 */
class PrettyPrinter {
    shared_ptr<Resource> m_pResource{};

public:
    /**
     * @brief Constructs a PrettyPrinter.
     * @param pResource Shared pointer to the Resource to be printed.
     */
    PrettyPrinter(shared_ptr<Resource> pResource) : m_pResource{ pResource } {
    }

    /**
     * @brief Clears the screen and prints the Resource data in a bordered box.
     */
    void Update() {
        system("cls"); // Use "clear" for Linux/Mac
        const auto& text = m_pResource->GetData();
        
        // The middle line format is "* " + text + " *"
        // This adds exactly 4 extra characters to the text length
        size_t lineLength = text.length() + 4; 
        
        auto printLine = 
            [lineLength] {
                for (size_t i = 0; i < lineLength; ++i) {
                    cout << "*";
                }
                cout << "\n"; // Ensure the border line breaks cleanly
            };
        
        printLine();
        cout << "* " << text << " *\n";
        printLine();
    }

    /**
     * @brief Destructor.
     */
    ~PrettyPrinter() {
    }
};
/*===========================================================================*
 *                       S T A T I C  F U N C T I O N S                     *
 *===========================================================================*/
/**
 * @brief Sends a message to the debug output without a trailing newline.
 * @param message The string to emit.
 */
static void DebugDisplay(const std::string& message) {
#ifdef _MSC_VER
    _RPT0(_CRT_WARN, message.c_str());
#else
    OutputDebugStringA(message.c_str());
#endif
}

/**
 * @brief Sends a message to the debug output followed by a newline.
 * @param message The string to emit.
 */
static void DebugDisplayLn(const std::string& message) {
    DebugDisplay(message);
#ifdef _MSC_VER
    _RPT0(_CRT_WARN, "\n");
#else
    OutputDebugStringA("\n");
#endif
}

/*===========================================================================*
 *                       G L O B A L  F U N C T I O N S                     *
 *===========================================================================*/
/** 
 * @brief Entry point 
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return 0 upon successful execution.
 */
int main(int argc, char const *argv[])
{
    auto r = make_shared<Resource>("Hello world");
    PrettyPrinter printer{r};
    DebugDisplayLn("[Press enter to change the resource data]");
    std::cin.get();
    r->SetData("Using raw pointers");
    DebugDisplayLn("[Press enter to delete the resource]");
    std::cin.get();
    r.reset();
    DebugDisplayLn("[Press enter to exit the application]");
    std::cin.get();
}
