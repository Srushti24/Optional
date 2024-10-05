
template<typedef T>
class Optional{

    public:
    Optional()
    {
    }
    ~Optional();

    private:
    T* m_ptr;

}