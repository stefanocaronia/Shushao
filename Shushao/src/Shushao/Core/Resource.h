#pragma once

namespace Shushao {

    /*
        interface Resources
        per gli object che possono essere caricati da disco dalla classe Resources
    */
    class Resource
    {
    public:
        virtual bool Load(std::string) = 0;
        virtual bool LoadEmbedded(int IDRES, std::string library = "") = 0;
        virtual bool LoadBytes(std::vector<char> data)
        {
            return true;
        };
    };
}  // Shushao