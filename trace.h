#ifndef __TRACE_H__
#define __TRACE_H__
namespace __TRACE_INFOR
{
    class trace
    {
    private:
        std::vector<std::string> vecStrActions;
        std::vector<std::string> vecStrCellTypes;
        std::vector<std::string> vecStrLookDirections;
    public:
        trace();
        std::string GetActionByNumber(unsigned short nActionNumber);
        std::string GetCellTypesByNumber(unsigned short nCellTypeNumber);
        std::string GetLookDirectionsByNumber(unsigned short nActionLookDirection);
        ~trace();
    };
};
#endif
