#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>


class IDGenerator {
private:
    int counter;

public:
    IDGenerator() : counter(0) {}

    int generateID() {
        return counter++;
    }
};


template <typename T>
class Object {
private:
    int id;
    T data;

public:
    Object(int id, const T& data) : id(id), data(data) {}

    int getID() const {
        return id;
    }

    const T& getData() const {
        return data;
    }

    
    virtual void print(std::ostream& os) const {
        os << "Object ID: " << id << ", Data: " << data;
    }

    
    virtual Object<T>* clone() const {
        return new Object<T>(*this);
    }
};


template <typename T>
std::ostream& operator<<(std::ostream& os, const Object<T>& obj) {
    obj.print(os);
    return os;
}


class SpecialObject : public Object<std::string> {
public:
    SpecialObject(int id, const std::string& data) : Object(id, data) {}

    
    void print(std::ostream& os) const override {
        os << "Special Object ID: " << getID() << ", Data: " << getData();
    }

    
    Object<std::string>* clone() const override {
        return new SpecialObject(*this);
    }
};


void performDynamicCast(Object<std::string>* obj) {
    SpecialObject* specialObj = dynamic_cast<SpecialObject*>(obj);
    if (specialObj) {
        std::cout << "Dynamic cast successful. Object is a SpecialObject." << std::endl;
    }
    else {
        std::cout << "Dynamic cast failed. Object is not a SpecialObject." << std::endl;
    }
}


class CustomException1 : public std::exception {
public:
    const char* what() const noexcept override {
        return "Custom Exception 1";
    }
};


class CustomException2 : public std::exception {
public:
    const char* what() const noexcept override {
        return "Custom Exception 2";
    }
};

int main() {
    try {
        IDGenerator idGenerator;
        std::vector<Object<std::string>*> objects;

        
        Object<std::string>* obj1 = new Object<std::string>(idGenerator.generateID(), "Data 1");
        objects.push_back(obj1);

        Object<std::string>* obj2 = new SpecialObject(idGenerator.generateID(), "Data 2");
        objects.push_back(obj2);

        Object<std::string>* obj3 = new Object<std::string>(idGenerator.generateID(), "Data 3");
        objects.push_back(obj3);

        
        for (const auto* obj : objects) {
            std::cout << *obj << std::endl;
        }

        

        
        std::cout << "Object 1: " << *obj1 << std::endl;
        std::cout << "Object 2 (Special): " << *obj2 << std::endl;

        
        Object<std::string>* clonedObj = obj3->clone();
        std::cout << "Cloned Object 3: " << *clonedObj << std::endl;
        delete clonedObj;

        
        performDynamicCast(obj2);

        
        try {
            throw CustomException1();
        }
        catch (const CustomException1& ex) {
            std::cout << "Caught CustomException1: " << ex.what() << std::endl;
        }

        try {
            throw CustomException2();
        }
        catch (const CustomException2& ex) {
            std::cout << "Caught CustomException2: " << ex.what() << std::endl;
        }

        
        for (auto* obj : objects) {
            delete obj;
        }
    }
    catch (const std::exception& ex) {
        std::cout << "Caught exception: " << ex.what() << std::endl;
    }

    return 0;
}
