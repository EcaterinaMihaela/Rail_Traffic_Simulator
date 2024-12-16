#ifndef RUN_H
#define RUN_H

#include "train.h"

class Run
{
public:
	static void CaseInfo(const vector<Train>& trains);
	static void CaseChooseRoute(const vector<Train>& trains);
	static void CaseBuyTicket(vector<Train>& trains);
	static void CaseMyTickets(const vector<Train>& trains);

	static int RunTheApp();
};

#endif