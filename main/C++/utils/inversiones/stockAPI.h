#ifndef STOCK_API
#define STOCK_API

namespace stockAPI
{
    class Symbol
    {
    private:
        const char *description;
        const char *displaySymbol;
        const char *symbol;
        const char *type;

    public:
        Symbol(const char *description, const char *displaySymbol, const char *symbol, const char *type);
        const char *getDescription() const;
        const char *getDisplaySymbol() const;
        const char *getSymbol() const;
        const char *getType() const;
        float getCurrentValue() const;
    };
    struct SearchResult
    {
    };
    class Search
    {
    private:
        const char *query;
        int count;
        Symbol **results;

    public:
        Search(const char *query);
        ~Search();
        void performSearch();
        int getCount() const;
        Symbol **getResults() const;
    };
}

#endif