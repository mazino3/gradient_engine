#ifndef SELECTION_MANAGER_H
#define SELECTION_MANAGER_H

#include <memory>
#include <functional>

struct SelectionSubscription
{
	virtual ~SelectionSubscription() {}
};

struct SelectionManagerImpl;

struct SelectionManager
{
	SelectionManager();
	~SelectionManager();

	int getId();
	void fireSelectionChanged(int selectedId);
	std::shared_ptr<SelectionSubscription> subscribe(std::function<void(int, int)> callback);

private:
	std::unique_ptr<SelectionManagerImpl> data;
};

#endif