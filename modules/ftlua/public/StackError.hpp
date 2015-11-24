
class StackError
{
public:

	/* CONSTRUCTION ***************** */
	StackError();
	// virtual ~StackError();
	~StackError();

	// StackError() = delete;
	StackError(StackError const &src) = delete;
	StackError(StackError &&src) = delete;
	StackError				&operator=(StackError const &rhs) = delete;
	StackError				&operator=(StackError &&rhs) = delete;

protected:
private:
};
