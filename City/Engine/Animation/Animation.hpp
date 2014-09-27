#ifndef NordicArts_City_Engine_Animation_Animation_H
#define NordicArts_City_Engine_Animation_Animation_H

namespace NordicArts {
    class Animation {
    // Variables
    public:
        unsigned int    m_iStartFrame;
        unsigned int    m_iEndFrame;

        float           m_fDuration;

    protected:
    private:

    // Methods
    public:
        Animation(unsigned int iStartFrame, unsigned int iEndFrame, float fDuration);

        unsigned int getLength() const;

    protected:
    private:

    };
};

#endif
