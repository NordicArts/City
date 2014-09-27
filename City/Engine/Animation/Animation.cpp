#include <Animation/Animation.hpp>

namespace NordicArts {
    Animation::Animation(unsigned int iStartFrame, unsigned int iEndFrame, float fDuration) : m_iStartFrame(iStartFrame), m_iEndFrame(iEndFrame), m_fDuration(fDuration) {}

    unsigned int Animation::getLength() const {
        return ((m_iEndFrame - m_iStartFrame) + 1);
    }
};
