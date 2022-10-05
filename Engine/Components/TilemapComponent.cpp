#include "TilemapComponent.h"
#include "Engine.h"

namespace  c14
{
    void TilemapComponent::Initialize()
    {
        for (int i = 0; i < tiles.size(); i++)
        {
            int index = tiles[i];
            if (index == 0) continue;

            auto actor = Factory::Instance().Create<Actor>(tile_names[index]);
            if (actor)
            {
                int x = i % num_columns;
                int y = i / num_columns;

                actor->m_transform.position = m_owner->m_transform.position + (Vector2{ x, y } * size);
                m_owner->GetScene()->AddActor(std::move(actor));
            }
        }

    }

    void TilemapComponent::Update()
    {
    }

    bool TilemapComponent::Write(const rapidjson::Value& value) const
    {
        return true;
    }

    bool TilemapComponent::Read(const rapidjson::Value& value)
    {
        READ_DATA(value, num_columns);
        READ_DATA(value, num_rows);
        READ_DATA(value, size);
        READ_DATA(value, tile_names);
        READ_DATA(value, tiles);

        return true;
    }

}