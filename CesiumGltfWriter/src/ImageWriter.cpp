#include "ImageWriter.h"
#include <magic_enum.hpp>
#include <algorithm>

void CesiumGltf::writeImage(
    const std::vector<Image>& images,
    rapidjson::Writer<rapidjson::StringBuffer>& jsonWriter
) {
    if (images.empty()) {
        return;
    }

    auto& j = jsonWriter;
    j.Key("images");
    j.StartArray();

    for (const auto& image : images) {
        j.StartObject();

        if (image.uri) {
            j.Key("uri");
            j.String(image.uri->c_str());
        }

        if (image.mimeType) {
            j.Key("mimeType");
            // TODO: Terrible hack. Automagically converts XXX_XXX to XXX/XXX
            //       The autogenerated class should provide a enum to string.
            //       function to avoid this.
            auto mimeType = std::string(magic_enum::enum_name(*image.mimeType));
            std::replace(mimeType.begin(), mimeType.end(), '_', '/');
            j.String(mimeType.c_str());
        }

        if (image.bufferView >= 0) {
            j.Key("bufferView");
            j.Int(image.bufferView);
        }

        if (!image.name.empty()) {
            j.Key("name");
            j.String(image.name.c_str());
        }

        // todo: extensions / extras

        j.EndObject();
    }

    j.EndArray();
}