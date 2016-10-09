#include "basicValues.h"
namespace json {

	class StaticNullValue: public NullValue {
	public:
		StaticNullValue() {
			addRef();
		}
	};

	template<bool v>
	class StaticBool : public BoolValue {
	public:
		virtual bool getBool() const override { return v; }
		StaticBool() {
			addRef();
		}

	};

	class StaticZeroNumber : public AbstractNumberValue {
	public:
		virtual double getNumber() const override { return 0.0; }
		virtual std::intptr_t getInt() const override { return 0; }
		virtual std::uintptr_t getUInt() const override {return 0;}
		virtual ValueTypeFlags flags() const override { return numberUnsignedInteger; }

		StaticZeroNumber() {
			addRef();
		}

	};

	class StaticEmptyStringValue : public AbstractStringValue {
	public:
		virtual StringRef<char> getString() const override { return StringRef<char>(); }

		StaticEmptyStringValue() {
			addRef();
		}
	};

	class StaticEmptyArrayValue : public AbstractArrayValue {
	public:
		virtual std::size_t size() const override { return 0; }
		virtual const IValue *itemAtIndex(std::size_t index) const override { return AbstractValue::getUndefined(); }
		virtual bool enumItems(const IEnumFn &) const override {
			return true;
		}
		StaticEmptyArrayValue() {
			addRef();
		}
	};

	class StaticEmptyObjectValue : public AbstractObjectValue {
	public:
		virtual std::size_t size() const override { return 0; }
		virtual const IValue *itemAtIndex(std::size_t index) const override { return getUndefined(); }
		virtual const IValue *member(const StringRef<char> &name) const override { return getUndefined(); }
		virtual bool enumItems(const IEnumFn &) const override { return true; }
		StaticEmptyObjectValue() {
			addRef();
		}
	};


	static StaticNullValue staticNull;


	const IValue *NullValue::getNull() {
		return &staticNull;

	}



	static StaticBool<false> boolFalse;
	static StaticBool<false> boolTrue;


	const IValue * BoolValue::getBool(bool v)
	{
		if (v) return &boolTrue;
		else return &boolFalse;
	}

	static StaticZeroNumber zero;

	const IValue * AbstractNumberValue::getZero()
	{
		return &zero;
	}

	static StaticEmptyStringValue emptyStr;

	const IValue * AbstractStringValue::getEmptyString()
	{
		return &emptyStr;
	}

	static StaticEmptyArrayValue emptyArray;

	const IValue * AbstractArrayValue::getEmptyArray()
	{
		return &emptyArray;
	}

	static StaticEmptyObjectValue emptyObject;

	const IValue * AbstractObjectValue::getEmptyObject()
	{
		return &emptyObject;
	}

	template class NumberValueT<std::uintptr_t, numberUnsignedInteger>;
	template class NumberValueT<std::intptr_t, numberInteger>;
	template class NumberValueT<double,0>;

	}