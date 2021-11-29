#include "Account.hpp"
#include <iostream>

int	Account::getNbAccounts( void )
{
	return _nbAccounts;
}

int	Account::getTotalAmount( void )
{
	return _totalAmount;
}

int	Account::getNbDeposits( void )
{
	return _totalNbWithdrawals;
}

int	Account::getNbWithdrawals( void )
{
	return _totalNbWithdrawals;
}

static void	_displayTimestamp( void )
{
	time_t now = time(0);
	tm *ltm = localtime(&now);

	std::cout << '[' << 1900 + ltm->tm_year << 1 + ltm->tm_mon << ltm->tm_mday;
	std::cout << '_' << 5 + ltm->tm_hour << 30 + ltm->tm_min << ltm->tm_sec << "] ";
}

void	Account::displayAccountsInfos( void )
{
	::_displayTimestamp();
	std::cout << "accounts:" << getNbAccounts() << ';';
	std::cout << "total:" << getTotalAmount() << ';';
	std::cout << "deposits:" << getNbDeposits() << ';';
	std::cout << "withdrawals:" << getNbWithdrawals() << std::endl;

//	[19920104_091532] accounts:8;total:20049;deposits:0;withdrawals:0

}

Account::Account( int initial_deposit )
{
	_amount += initial_deposit;
	_totalAmount += initial_deposit;
	_nbAccounts++;
}
//~Account( void );

void	Account::makeDeposit( int deposit )
{
	_nbDeposits++;
	_totalNbDeposits++;
	_amount += deposit;
	_totalAmount += deposit;
}

bool	Account::makeWithdrawal( int withdrawal )
{
	_nbWithdrawals++;
	_totalNbWithdrawals++;
	if (_amount >= withdrawal)
	{
		_amount -= withdrawal;
		_totalAmount -= withdrawal;
		return (1);
	}
	return (0);
}
//
//int		Account::checkAmount( void ) const;
//void	Account::displayStatus( void ) const;