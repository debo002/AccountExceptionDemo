#include <iostream>
#include <stdexcept>

// Exception thrown when balance is negative
class IllegalBalanceException : public std::exception {
public:
	IllegalBalanceException() noexcept = default;
	~IllegalBalanceException() = default;

	const char* what() const noexcept {
		return "Illegal balance operation attempted.";
	}
};

// Exception thrown when trying to withdraw more than available balance
class InsufficientFundsException : public std::exception {
public:
	InsufficientFundsException() noexcept = default;
	~InsufficientFundsException() = default;

	const char* what() const noexcept {
		return "Insufficient funds for the requested operation.";
	}
};

// Bank account with exception handling
class Account {
private:
	double balance;

public:
	// Create account with initial balance (must be >= 0)
	Account(double initialBalance) : balance(initialBalance) {
		if (initialBalance < 0) {
			throw IllegalBalanceException();
		}
	}

	// Add money to account (must be >= 0)
	void deposit(double amount) {
		if (amount < 0) {
			throw IllegalBalanceException();
		}
		balance += amount;
	}

	// Remove money from account (must have enough funds)
	void withdraw(double amount) {
		if (amount > balance) {
			throw InsufficientFundsException();
		}
		balance -= amount;
	}

	// Get current balance
	double getBalance() const {
		return balance;
	}
};

int main()
{
	try {
		// Test normal operations
		Account myAccount(100.0);
		std::cout << "Initial balance: $" << myAccount.getBalance() << std::endl;

		myAccount.deposit(50.0);
		std::cout << "After deposit: $" << myAccount.getBalance() << std::endl;

		myAccount.withdraw(30.0);
		std::cout << "After withdrawal: $" << myAccount.getBalance() << std::endl;

		// This will throw InsufficientFundsException
		myAccount.withdraw(150.0);
	}
	catch (const IllegalBalanceException& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	catch (const InsufficientFundsException& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Unexpected error: " << e.what() << std::endl;
	}

	return 0;
}