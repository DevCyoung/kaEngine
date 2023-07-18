#include "pch.h"
#include "NoiseTest.h"
#include "Components.h"
#include "ResourceManager.h"

NoiseTest::NoiseTest()
    : ScriptComponent(eScriptComponentType::NoiseTest)
    , matArray{}
{
}

NoiseTest::~NoiseTest()
{
}

void NoiseTest::initialize()
{
    matArray[0] = gResourceManager->FindOrNull<Material>(L"Noise01");
    matArray[1] = gResourceManager->FindOrNull<Material>(L"Noise02");
    matArray[2] = gResourceManager->FindOrNull<Material>(L"Noise03");
    matArray[3] = gResourceManager->FindOrNull<Material>(L"Noise04");
}

void NoiseTest::update()
{
    //0.1ÃÊ¿¡ 4Àå
    static float delay = 0.f;    

    delay += gDeltaTime;

    if (delay >= 0.16f)
    {
        delay = 0.f;
    }

    if (delay > 0.12f)
    {
        GetOwner()->GetComponent<SpriteRenderer>()->SetMaterial(matArray[3]);
    }
    else if (delay > 0.08f)
    {
        GetOwner()->GetComponent<SpriteRenderer>()->SetMaterial(matArray[2]);
    }
    else if (delay > 0.04f)
    {
        GetOwner()->GetComponent<SpriteRenderer>()->SetMaterial(matArray[1]);
    }
    else
    {
        GetOwner()->GetComponent<SpriteRenderer>()->SetMaterial(matArray[0]);
    }

    
}

void NoiseTest::lateUpdate()
{
}
