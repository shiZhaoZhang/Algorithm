#ifndef OBJECTPOOL
#define OBJECTPOOL

#include "string"
#include "map"
#include "memory"
#include "mutex"
#include "functional"

class Object {
public:
    Object(const std::string& key){
        this->key = key; 
    }
    std::string key;
    
};

class ObjectFactory :public std::enable_shared_from_this<ObjectFactory> {
public:
    ObjectFactory() = default;
    //阻止拷贝和赋值操作
    ObjectFactory(const ObjectFactory&) = delete;
    ObjectFactory &operator=(const ObjectFactory&) = delete;

    ~ObjectFactory() = default;
public:
    //获取对象
    std::shared_ptr<Object> get(const std::string &key);
private:
    static void weakDeleteCallBack(const std::weak_ptr<ObjectFactory>& wkFactory, Object * object);
    void removeObject(Object *object);
private:
    mutable std::mutex locker;
    std::map<std::string, std::weak_ptr<Object>> objects;

};

std::shared_ptr<Object> ObjectFactory::get(const std::string &key){
    std::shared_ptr<Object> pObject;
    locker.lock();
    std::weak_ptr<Object> &wkObject = objects[key];
    //尝试提升成shared_ptr
    pObject = wkObject.lock();
    //提升失败
    if(!pObject){
        pObject.reset(new Object(key),
            std::bind(&ObjectFactory::weakDeleteCallBack, std::weak_ptr<ObjectFactory>(shared_from_this()), std::placeholders::_1)
        );
        wkObject = pObject;
    }
    locker.unlock();
    return pObject;
}
void ObjectFactory::weakDeleteCallBack(const std::weak_ptr<ObjectFactory>& wkFactory, Object * object){
    std::shared_ptr<ObjectFactory> factory(wkFactory.lock());
    if(factory){
        factory->removeObject(object);
    }
    delete object;
}

void ObjectFactory::removeObject(Object *object){
    if(object){
        locker.lock();
        objects.erase(object->key);
        locker.unlock();
    }
}

#endif