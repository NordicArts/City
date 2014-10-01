#include <Animation/Animation.hpp>

namespace NordicArts {
    Animation::Animation(unsigned int iStartFrame, unsigned int iEndFrame, float fDuration) : m_iStartFrame(iStartFrame), m_iEndFrame(iEndFrame), m_fDuration(fDuration) {}

    unsigned int Animation::getLength() const {
        return ((this->m_iEndFrame - this->m_iStartFrame) + 1);
    }

    float Animation::getDuration() const {
        return this->m_fDuration;
    }
};
