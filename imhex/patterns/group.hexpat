#pragma once

struct HX_GROUP {
    u32 sectionCount;
    u32 vertCount;
    u32 sections[sectionCount];
    u16 verts[vertCount];
};
