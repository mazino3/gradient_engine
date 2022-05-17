#include "SnappingProperty.h"
#include <cmath>

struct SnappingPropertyImpl
{
	float targetValue;
	float currentValue;
	float snappedValue;

	float step;
	float currentWeight;

	std::function<void(float, float)> valueChangedCallback;

	SnappingPropertyImpl() :
		targetValue(0.0f),
		currentValue(0.0f),
		snappedValue(0.0f),
		step(0.0f),
		currentWeight(0.5f),
		valueChangedCallback([](float, float) {})
	{}
};

SnappingProperty::SnappingProperty(float step)
{
	data = std::make_unique<SnappingPropertyImpl>();
	data->step = step;
}

SnappingProperty::SnappingProperty()
{
	data = std::make_unique<SnappingPropertyImpl>();
	data->step = 0.2f;
}

SnappingProperty::~SnappingProperty()
{
}

void SnappingProperty::setTargetValue(float targetValue)
{
	data->targetValue = targetValue;
	data->snappedValue = std::roundf(targetValue / data->step) * data->step;
}

float SnappingProperty::getTargetValue()
{
	return data->targetValue;
}

void SnappingProperty::setCurrentValue(float currentValue)
{
	data->currentValue = currentValue;
}

float SnappingProperty::getCurrentValue()
{
	return data->currentValue;
}

void SnappingProperty::setCurrentWeight(float weight)
{
	data->currentWeight = weight;
}

float SnappingProperty::getCurrentWeight()
{
	return data->currentWeight;
}

void SnappingProperty::onValueChanged(std::function<void(float, float)> callback)
{
	data->valueChangedCallback = callback;
}

void SnappingProperty::update()
{
	float oldValue = data->currentValue;
	data->currentValue = data->currentValue * data->currentWeight + data->snappedValue * (1.0f - data->currentWeight);
	if (data->currentValue != oldValue)
	{
		data->valueChangedCallback(oldValue, data->currentValue);
	}
}
