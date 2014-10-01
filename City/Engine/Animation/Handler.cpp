#include <SFML/Graphics.hpp>

#include <vector>

#include <Animation/Handler.hpp>

namespace NordicArts {
    void AnimationHandler::update(const float fDT) {
        if ((m_iCurrentAnimation >= this->m_vAnimations.size()) || (m_iCurrentAnimation < 0)) {
            return;
        }

        float fDuration = this->m_vAnimations[m_iCurrentAnimation].getDuration();

        if (int((m_fT + fDT) / fDuration) > int(m_fT / fDuration)) {
            int iFrame = int((m_fT + fDT) / fDuration);

            iFrame %= this->m_vAnimations[m_iCurrentAnimation].getLength();

            sf::IntRect rect    = this->m_oFrameSize;
            rect.left           = (rect.width * iFrame);
            rect.top            = (rect.height * this->m_iCurrentAnimation);
            this->m_oBounds     = rect;
        }

        this->m_fT += fDT;

        if (this->m_fT > (fDuration * this->m_vAnimations[m_iCurrentAnimation].getLength())) {
            this->m_fT = 0.0f;
        }

        return;
    }

    void AnimationHandler::addAnimation(Animation &oAnimation) {
        this->m_vAnimations.push_back(oAnimation);
    }

    void AnimationHandler::changeAnimation(unsigned int iAnimationID) {
        if ((this->m_iCurrentAnimation == iAnimationID) || (iAnimationID >= this->m_vAnimations.size()) || (iAnimationID < 0)) {
            return;
        }

        this->m_iCurrentAnimation = iAnimationID;

        sf::IntRect rect    = this->m_oFrameSize;
        rect.top            = (rect.height * iAnimationID);
        this->m_oBounds     = rect;
        
        this->m_fT = 0.0f;
    
        return;
    }

    AnimationHandler::AnimationHandler() : m_fT(0), m_iCurrentAnimation(-1) {}
    AnimationHandler::AnimationHandler(const sf::IntRect &oFrameSize) : m_oFrameSize(oFrameSize), m_fT(0), m_iCurrentAnimation(-1) {}
};
