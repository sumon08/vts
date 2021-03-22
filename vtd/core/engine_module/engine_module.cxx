



#include <engine.hxx>
#include <core.hxx>


namespace vts
{

    Engine Engine::engine_instance;



    bool InitEngineModule()
    {
        Engine & eng_inst = Engine::GetInstance();

        

        return eng_inst.Run(2024,10);

    } 
}