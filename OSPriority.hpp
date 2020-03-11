#if defined(unix) || defined(__unix__) || defined(__unix)
	#define LINUX
#elif defined(_WIN32)
	#define WINDOWS
#endif

class OSPriority
{
public:
	int getPriority();
	void setPriority(int priority);
};