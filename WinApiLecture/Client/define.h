#pragma once


//Singleton ¸ÞÅ©·Î
#define SINGLE(type) public:\
						static type* GetInst()\
						 {\
							 static type mgr;\
							 return &mgr;\
						 }




