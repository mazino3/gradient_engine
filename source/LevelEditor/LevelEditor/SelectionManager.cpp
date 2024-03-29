#include "SelectionManager.h"
#include <unordered_map>
#include <iostream>

struct SelectionSubscriptionImpl : SelectionSubscription
{
	SelectionSubscriptionImpl(SelectionManagerImpl& manager, int id);
	~SelectionSubscriptionImpl();

	SelectionManagerImpl& manager;
	int id;
};

struct SelectionManagerImpl
{
	std::unordered_map<int, std::function<void(int, int)>> subscriptions;
	int counter;
	int internalCounter;
	int prevId;
	bool hasSelection;
	void removeSubscription(int id);
};

SelectionSubscriptionImpl::SelectionSubscriptionImpl(SelectionManagerImpl& manager, int id) :
	manager(manager),
	id(id)
{}

SelectionSubscriptionImpl::~SelectionSubscriptionImpl()
{
	manager.removeSubscription(id);
}

void SelectionManagerImpl::removeSubscription(int id)
{
	auto elemToErase = subscriptions.find(id);
	if (elemToErase != subscriptions.end())
	{
		subscriptions.erase(elemToErase);
	}
}

SelectionManager::SelectionManager()
{
	data = std::make_unique<SelectionManagerImpl>();
	data->counter = 0;
	data->internalCounter = 0;
	data->prevId = -1;
	data->hasSelection = false;
}

SelectionManager::~SelectionManager()
{}

int SelectionManager::getId()
{
	return data->counter++;
}

void SelectionManager::fireSelectionChanged(int selectedId)
{
	for (auto it = data->subscriptions.begin(); it != data->subscriptions.end(); it++)
	{
		it->second(selectedId, data->prevId);
	}
	data->prevId = selectedId;
	if (selectedId != -1)
	{
		data->hasSelection = true;
	}
}

void SelectionManager::removeCurrentSelection()
{
	data->hasSelection = false;
	fireSelectionChanged(-1);
}

bool SelectionManager::hasSelection()
{
	return data->hasSelection;
}

std::shared_ptr<SelectionSubscription> SelectionManager::subscribe(std::function<void(int, int)> callback)
{
	int id = data->internalCounter++;
	data->subscriptions[id] = callback;
	auto subscription = std::make_shared<SelectionSubscriptionImpl>(*data, id);
	return subscription;
}