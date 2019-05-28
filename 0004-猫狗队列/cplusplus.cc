#include <iostream>
#include <queue>
#include <string>
#include <assert.h>
using namespace std;

class Pet {
public:
    Pet(const char *p) : type(p) {}
    string& getPetType() {
        return this->type;
    }
private:
    string type;
};
class Dog: public Pet {
public:
    Dog() : Pet("dog") {}
};
class Cat: public Pet {
public:
    Cat() : Pet("cat"){}
};

/**
    猫狗队列
    题目：宠物、狗和猫的类参见上述定义。实现一种狗猫队列的结构，要求如下：
    1. 用户可以调用add方法将cat类或dog类的实例放入队列中；
    2. 用户可以调用pollAll方法，将队列中所有的实例按照入队列的先后顺序依次弹出；
    3. 用户可以调用pollDog方法，将队列中dog类的实例按照入队列的先后顺序依次弹出；
    4. 用户可以调用pollCat方法，将队列中cat类的实例按照入队列的先后顺序依次弹出；
    5. 用户可以调用isEmpty方法，检查队列中是否还有dog或cat的实例；
    6. 用户可以调用isDogEmpty方法，检查队列中是否还有dog类的实例；
    5. 用户可以调用isCatEmpty方法，检查队列中是否还有cat类的实例；
*/
/**
    解题思路：可以考虑将dog和cat的实例分别保存在两个队列中，这样对于add/pollDog/pollCat/isEmpty/
    isDogEmpty/isCatEmpty的方法而言非常好实现，唯一的难点在于pollAll方法，因为dog和cat的实例是分
    别保存在两个队列中的，因此在调用这个方法时，我们总是需要将最先入队的实例弹出，因此这种设计
    的重点是要再添加一个时间戳(计数器)的功能，即每次在入队操作时，我们通过给实例添加时间戳，这样
    在做出队操作时，只需要比较dog队列和cat队列中最旧的时间戳即可。
*/

class PetEnqueue {
public:
    PetEnqueue(Pet *pet, uint32_t count) {
        this->pet = pet;
        this->count = count;
    }
    Pet *getPet() {
        return this->pet;
    }
    uint32_t getCount() {
        return this->count;
    }
    string& getEnqueuePetType() {
        return this->pet->getPetType();
    }
private:
    Pet *pet;
    uint32_t count;
};

class DogCatQueue {
public:
    DogCatQueue() : mDogQueue(), mCatQueue(), count(0) {}
    void add(Pet *pet) {
        assert(pet);
        if (pet->getPetType().compare("dog") == 0) {
            mDogQueue.push(PetEnqueue(pet, this->count++));
        } else if (pet->getPetType().compare("cat") == 0) {
            mCatQueue.push(PetEnqueue(pet, this->count++));
        } else {
            assert(0);
        }
    }
    Pet* pollAll() {
        if (!mDogQueue.empty() && !mCatQueue.empty()) {
            // 计数值越小，时间戳越旧，越应该先出列
            if (mDogQueue.front().getCount() < mCatQueue.front().getCount()) {
                Pet* pet = mDogQueue.front().getPet();
                mDogQueue.pop();
                return pet;
            } else {
                Pet* pet = mCatQueue.front().getPet();
                mCatQueue.pop();
                return pet;
            }
        } else if (!mDogQueue.empty()) {
            Pet* pet = mDogQueue.front().getPet();
            mDogQueue.pop();
            return pet;
        } else if (!mCatQueue.empty()) {
            Pet* pet = mCatQueue.front().getPet();
            mCatQueue.pop();
            return pet;
        } else {
            return NULL;
        }
    }
    Dog* pollDog() {
        if (!mDogQueue.empty()) {
            Pet* pet = mDogQueue.front().getPet();
            mDogQueue.pop();
            return static_cast<Dog*>(pet);
        } else {
            return NULL;
        }
    }
    Cat* pollCat() {
        if (!mCatQueue.empty()) {
            Pet* pet = mCatQueue.front().getPet();
            mCatQueue.pop();
            return static_cast<Cat*>(pet);
        } else {
            return NULL;
        }
    }
    bool isEmpty() {
        return (mDogQueue.empty() && mCatQueue.empty());
    }
    bool isDogEmpty() {
        return mDogQueue.empty();
    }
    bool isCatEmpty() {
        return mCatQueue.empty();
    }
private:
    queue<PetEnqueue> mDogQueue;
    queue<PetEnqueue> mCatQueue;
    uint32_t count;
};

int main(int nargs, char* argv[]) {
    DogCatQueue dcQueue;
    Pet* dog = new Dog();
    Pet* cat = new Cat();
    dcQueue.add(dog);
    dcQueue.add(cat);
    dcQueue.add(cat);
    dcQueue.add(dog);
    dcQueue.add(dog);
    dcQueue.add(dog);
    dcQueue.add(cat);
    dcQueue.add(cat);
    dcQueue.add(cat);
    dcQueue.add(dog);

    cout << dcQueue.pollCat()->getPetType() << endl;
    cout << dcQueue.pollAll()->getPetType() << endl;
    cout << dcQueue.pollDog()->getPetType() << endl;
    
    return 0;
}
