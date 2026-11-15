#pragma once
class GameObject
{
public:
    // Wirtualny destruktor gwarantuje poprawne niszczenie obiektów dziedziczących
    virtual ~GameObject() = default;

    // Przykładowa metoda czysto wirtualna (opcjonalna, np. inicjalizacja obiektu)
    virtual void Init() {}
};