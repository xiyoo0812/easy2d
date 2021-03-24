#ifndef SINGLETON_H
#define SINGLETON_H

namespace Easy2D
{
    template<typename T>
    class Singleton
    {
    public:
        static T* getInstance()
        {
            if (mInatance == nullptr)
            {
                mInatance = new T();
            }
            return mInatance;
        }

    protected:
        Singleton() {}
        virtual ~Singleton() {}

    private:
        inline static T* mInatance = nullptr;
    };
}

#endif
