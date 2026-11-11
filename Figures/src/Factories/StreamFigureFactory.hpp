#ifndef STREAM_FIGURE_FACTORY
#define STREAM_FIGURE_FACTORY

#include <istream>
#include "FigureFactory.hpp"
#include "StringFigureFactory.hpp"

class StreamFigureFactory : public FigureFactory {
    public:
        explicit StreamFigureFactory(std::istream& _input);

        StreamFigureFactory(const StreamFigureFactory&) = delete;
        StreamFigureFactory(StreamFigureFactory&&) = delete;
        
        std::unique_ptr<Figure> create() override;
    private:
        std::istream& input;
        StringFigureFactory stringFactory;
};

#endif