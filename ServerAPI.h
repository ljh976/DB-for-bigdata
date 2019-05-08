#define SERVER_API __declspec(dllexport)

#include <vector>
#include <unordered_map>
#include <string>
#include <stack>
#include <exception>

class SERVER_API InvalidRecord : public std::exception
{
public:
	virtual const char* what() const { return "Function was passed an invalid Record object."; }
};

class SERVER_API InvalidTable : public std::exception
{
public:
	virtual const char* what() const { return "Function was passed an invalid Table object."; }
};

class SERVER_API InvalidDatabase : public std::exception
{
public:
	virtual const char* what() const { return "Function was passed an invalid Database object."; }
};

class SERVER_API CrossJoinException : public std::exception
{
public:
	virtual const char* what() const { return "Invalid cross join occurred."; }
};

class SERVER_API NaturalJoinException : public std::exception
{
public:
	virtual const char* what() const { return "Invalid natural join occurred."; }
};

class SERVER_API AttributeDoesntExistException : public std::exception
{
public:
	virtual const char* what() const { return "Attribute does not exist in table."; }
};

class SERVER_API TableDoesntExistException : public std::exception
{
public:
	virtual const char* what() const { return "Table does not exist in the database."; }
};

class SERVER_API QuerySelectException : public std::exception
{
public:
	virtual const char* what() const { return "Failed to parse \"select\" string of query command."; }
};

class SERVER_API QueryFromException : public std::exception
{
public:
	virtual const char* what() const { return "Failed to parse \"from\" string of query command."; }
};

class SERVER_API QueryWhereException : public std::exception
{
public:
	virtual const char* what() const { return "Failed to parse \"where\" string of query command."; }
};

class Record
{
public:
	std::vector<std::string> elems;

public:
	SERVER_API Record();
	SERVER_API Record(int size);
	SERVER_API Record(const Record& record);
	SERVER_API ~Record();


	SERVER_API int getSize();
	SERVER_API void resize(int size);


	SERVER_API std::string& operator[](int num);
};

class Table
{
public:
	std::string key;
	std::vector<std::string> columns;
	std::vector<Record> records;

public:
	SERVER_API Table();
	SERVER_API Table(const std::vector<std::string>& attributeNames);
	SERVER_API Table(const Table& table);
	SERVER_API ~Table();


	SERVER_API void addColumn(const std::string& attributeName);

	SERVER_API int count(const std::string& attributeName);

	SERVER_API Table crossJoin(const Table* b);
	SERVER_API Table crossJoin(const Table& b);
	static SERVER_API Table crossJoin(const Table* a, const Table* b);
	static SERVER_API Table crossJoin(const Table& a, const Table& b);

	SERVER_API void deleteColumn(const std::string& attributeName);
	void deleteColumn(const int attributeIndex);

	SERVER_API std::vector<std::string> getAttributes();

	SERVER_API int getNumRecords();

	SERVER_API void insertRecord(const Record* record);
	SERVER_API void insertRecord(const Record& record);

	SERVER_API Record max(const std::string& attributeName);
	SERVER_API Record min(const std::string& attributeName);

	SERVER_API Table naturalJoin(const Table* b);
	SERVER_API Table naturalJoin(const Table& b);
	static SERVER_API Table naturalJoin(const Table* a, const Table* b);
	static SERVER_API Table naturalJoin(const Table& a, const Table& b);

	SERVER_API void setAttributeAsKey(const std::string& attributeName);

	Table trimToAttribList(std::vector<std::string>& attribList);
	static Table trimToAttribList(Table& table, std::vector<std::string>& attribList);


	SERVER_API Record& operator[](int num);
};

class Database
{
private:
	typedef enum token_type
	{
		Equals,
		NotEquals,
		Less,
		Greater,
		LessEq,
		GreaterEq,
		And,
		Or,
		Not,
		OpenParen,
		CloseParen,
		NUM_TOKEN_TYPES
	} token_type;

	typedef struct token_info
	{
		token_type type;
		int precedence;
	} token_info;

public:
	std::unordered_map<std::string, Table> tables;

private:
	void addOperatorToken(const token_info& token, Table& sourceTable, std::stack<Table>& tableStack, std::stack<std::string>& valueStack, std::stack<token_info>& operatorStack);

	void evalComparison(Table& sourceTable, std::stack<std::string>& valueStack, int* idx, std::string& value);
	void evalExpression(Table& sourceTable, std::stack<Table>& tableStack, std::stack<std::string>& valueStack, std::stack<token_info>& operatorStack);

	std::vector<std::string> queryParseSelect(const Table& table, const std::string& str);
	Table queryParseWhere(Table& sourceTable, const std::string& str);

	std::string removeLeadingWhitespace(const std::string& str);

public:
	SERVER_API Database();
	SERVER_API ~Database();


	SERVER_API void addTable(const Table* table, const std::string& name);
	SERVER_API void addTable(const Table& table, const std::string& name);
	SERVER_API void dropTable(const std::string& name);

	SERVER_API std::vector<std::string> getTableNames();
	SERVER_API std::vector<Table> getTables();

	SERVER_API Table query(const std::string& select, const std::string& from, const std::string& where);
};