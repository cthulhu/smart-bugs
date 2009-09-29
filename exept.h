#ifndef _EXEPTION_H_
#define _EXEPTION_H_

class eExeption
{
protected:
	std::string strExeptionMessage;
public:
	eExeption(std::string strExeptionMsg):strExeptionMessage(strExeptionMsg){}
	eExeption():strExeptionMessage(""){}
	std::string ExeptionStr(void);
	~eExeption(){}	
};
#endif