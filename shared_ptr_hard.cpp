//
// Реализуйте класс SharedPtr как описано ранее. Задание немного сложнее, чем 
// кажется на первый взгляд. Уделите особое внимание "граничным случаям" - нулевой
// указатель, присваивание самому себе, вызов reset на нулевом SharedPtr и прочее.
//

struct Expression;
struct Number;
struct BinaryOperation;
struct FunctionCall;
struct Variable;

struct SharedPtr
{
    int * count;
    Expression * ptr_;
    
    explicit SharedPtr(Expression *ptr = 0)
    {
        ptr_ = ptr;
        if (ptr_)
            count = new int(1);
    }
    
    ~SharedPtr()
    {
        if (ptr_)
        {
            (*count)--;
            if (!(*count))
            {
                delete ptr_;
                delete count;
            }
        }
    }
    
    SharedPtr(const SharedPtr & s)
    {
        ptr_ = s.ptr_;
        if (ptr_)
        {
            count = s.count;
            (*count)++;
        }
    }
    
    SharedPtr& operator=(const SharedPtr & s)
    {
        if (this != &s)
        {
            if (ptr_)
                (*count)--;
            if (ptr_ && !(*count))
            {
                delete ptr_;
                delete count;
            }
            ptr_ = s.ptr_;
            count = s.count;
            (*count)++;
        }
        return *this;
    }
    
    void reset(Expression *ptr = 0)
    {
        if (ptr_)
            (*count)--;
        if (ptr_ && !(*count))
        {
            delete ptr_;
            delete count;
        }
        ptr_ = ptr;
        if (ptr_)
            count = new int(1);

    }
    
    Expression* get() const {
        return ptr_;
    }
    
    Expression& operator*() const
    {
        return *ptr_;
    }
    Expression* operator->() const {
        return ptr_;
    }
};
