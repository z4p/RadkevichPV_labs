#ifndef SMARTPTR_H
#define SMARTPTR_H

template <typename T>
class SmartPtr {
private:
	T *object;
	int *counter;

public:
	SmartPtr()
		: object(nullptr), counter(nullptr)
	{}

	SmartPtr(T* object)
		: object(object), counter(nullptr)
	{
		counter = new int();
		*counter = 1;
	}

	SmartPtr(const SmartPtr& orig)
		: object(orig.object), counter(orig.counter)
	{
		if (counter) (*counter)++;
	}

	SmartPtr& operator=(const SmartPtr& rval) {
		if (this == &rval) {
			object = rval.object;
			counter = rval.counter;
			if (counter) (*counter)++;
		}
		return *this;
	}

	SmartPtr(SmartPtr&& orig) = delete;
	SmartPtr& operator=(const SmartPtr&& rval) = delete;

	~SmartPtr() {
		if (counter) {
			--(*counter);
			if (*counter == 0) {
				delete object;
				delete counter;
			}
		}
	}

	T*	operator->() {
		if (*counter > 0) {
			return object;
		} else {
			return nullptr;
		}
	}
};

#endif /* SMARTPTR_H */
