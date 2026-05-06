#include "Subject.h"

void Subject::addObserver(Observer* observer) {
	observers.push_back(observer);
}

void Subject::removeObserver(Observer* observer) {
	observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Subject::notify(ActionNotify eventType) {
	for (Observer* observer : observers) {
		observer->onNotify(eventType);

	}
}