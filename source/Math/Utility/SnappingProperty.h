#ifndef SNAPPING_PROPERTY_H
#define SNAPPING_PROPERTY_H

#include <memory>
#include <functional>

struct SnappingPropertyImpl;

struct SnappingProperty
{
	SnappingProperty(float step);
	~SnappingProperty();

	void setTargetValue(float value);
	float getTargetValue();

	void setCurrentValue(float value);
	float getCurrentValue();

	void setCurrentWeight(float weight);
	float getCurrentWeight();

	void onValueChanged(std::function<void(float, float)> callback);

	void update();

private:
	std::unique_ptr<SnappingPropertyImpl> data;
};

#endif