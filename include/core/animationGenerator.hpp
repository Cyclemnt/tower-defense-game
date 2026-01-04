#ifndef ANIMATION_GENERATOR_HPP
#define ANIMATION_GENERATOR_HPP

namespace tdg::core { class Events; class Map; };

namespace tdg::core {
    
    class AnimationGenerator {
    public:
        AnimationGenerator(Map& map);

        void generate(float dt, Events& events);
        
    private:
        Map& m_map;
    };    

} // namespace tdg::core

#endif // ANIMATION_GENERATOR_HPP