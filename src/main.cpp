#include "arena_alloc.h"

// some helpers for testing

struct velocity {
    float vx, vy, vz;
};

struct vector3 {
    float x, y, z;
};

static constexpr int BULLET_POOL_SIZE = 500;
struct bullet {
    float damage;
    bool active;
};

struct bullet_data {
    vector3 positions[BULLET_POOL_SIZE];
    velocity velocities[BULLET_POOL_SIZE];
    bullet more_bullet_data[BULLET_POOL_SIZE];
};

int main() {

    arena_alloc arena(sizeof(bullet_data));

    void* raw_memory = arena.add(sizeof(bullet_data));
    if (!raw_memory) {
        std::cerr << "Arena allocation failed!";
        return 1;
    }
    auto* bullets = static_cast<bullet_data*>(raw_memory);

    int count = 0;
    for (int i = 0; i < BULLET_POOL_SIZE; i++) {
        bullets->more_bullet_data[i].active = false;
        bullets->positions[i] = {0, 0, 0};
        bullets->velocities[i] = {0, 0, 0};
        count++;
    }
    std::cout << count;
    return 0;
}

