#pragma once

#include <cstdint>

#include "parser.hpp"

std::string humanReadableSize(int bytes);

void log_entity_data(const fs::path &displayPath, int entitySize,
                     bool humanReadable);

uint32_t du_modern(const fs::path &entityPath, const DuFlags &options);
