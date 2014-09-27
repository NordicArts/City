#ifndef NordicArts_City_Engine_Animations_Handler_H
#define NordicArts_City_Engine_Animations_Handler_H

#include <SFML/Graphics.hpp>

#include <vector>

#include <Animation/Animation.hpp>

namespace NordicArts {
    class AnimationHandler {
    // Variables
    public:
        sf::IntRect m_oBounds;
        sf::IntRect m_oFrameSize;

    protected:
    private:
        std::vector<Animation>  m_vAnimations;

        float                   m_fT;

        int                     m_iCurrentAnimation;

    // Methods
    public:
        void addAnimation(Animation &oAnimation);
        void update(const float fDT);
        void changeAnimation(unsigned int iAnimationID);

        AnimationHandler();
        AnimationHandler(const sf::IntRect &oFrameSize);

    protected:
    private:

    };
};

#endif
