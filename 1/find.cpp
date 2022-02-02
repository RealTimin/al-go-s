template <typename Iterator, typename Object>
iterator find( Iterator start, Iterator end, const Object & x )
{
    while(start != end && *start != v)
    {
        start++;
    }
    return start;
}