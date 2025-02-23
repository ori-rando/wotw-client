#include <Core/utils/json_serializers.h>

#include <Common/ext.h>

#include <Modloader/modloader.h>

#include <fstream>

namespace app {
    void to_json(nlohmann::json& j, const Vector2& s) {
        j = {
            { "x", s.x },
            { "y", s.y },
        };
    }

    void from_json(const nlohmann::json& j, Vector2& s) {
        s.x = j.value("x", 0.0f);
        s.y = j.value("y", 0.0f);
    }

    void to_json(nlohmann::json& j, const Vector3& s) {
        j = {
            { "x", s.x },
            { "y", s.y },
            { "z", s.z },
        };
    }

    void from_json(const nlohmann::json& j, Vector3& s) {
        s.x = j.value("x", 0.0f);
        s.y = j.value("y", 0.0f);
        s.z = j.value("z", 0.0f);
    }

    void to_json(nlohmann::json& j, const Vector4& s) {
        j = {
            { "x", s.x },
            { "y", s.y },
            { "z", s.z },
            { "w", s.w },
        };
    }

    void from_json(const nlohmann::json& j, Vector4& s) {
        s.x = j.value("x", 0.0f);
        s.y = j.value("y", 0.0f);
        s.z = j.value("z", 0.0f);
        s.w = j.value("w", 1.0f);
    }

    void to_json(nlohmann::json& j, const Color& s) {
        j = {
            { "r", s.r },
            { "g", s.g },
            { "b", s.b },
            { "a", s.a },
        };
    }

    void from_json(const nlohmann::json& j, Color& s) {
        s.r = j.value("r", 0.0f);
        s.g = j.value("g", 0.0f);
        s.b = j.value("b", 0.0f);
        s.a = j.value("a", 1.0f);
    }
} // namespace app

bool load_json_file(const std::string& path, nlohmann::json& j) {
    using namespace modloader;
    std::ifstream stream(base_path() / path);
    if (stream.is_open()) {
        try {
            stream >> j;
        } catch (nlohmann::json::parse_error& ex) {
            warn("util", std::format("failed to parse '{}' error '{}' at byte '{}'", (base_path() / path).string(), ex.id, ex.byte));
            return false;
        }
    } else {
        warn("util", std::format("failed to open '{}'", (base_path() / path).string()));
        return false;
    }

    return true;
}
