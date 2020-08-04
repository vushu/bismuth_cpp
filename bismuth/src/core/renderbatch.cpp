#include <bismuth/renderbatch.hpp>

using namespace bi;

RenderBatch::~RenderBatch() {}


std::vector<int> RenderBatch::generateIndices() {
    std::vector<int> elements(6 * maxBatchSize);
    for (int i = 0; i < maxBatchSize; i++) {
        loadElementIndices(elements, i);
    }
    return elements;
}

void RenderBatch::loadElementIndices(std::vector<int>& elements, int index) {
    int offsetArrayIndex = 6 * index;
    int offset = 4 * index;

    elements[offsetArrayIndex] = offset + 3;
    elements[offsetArrayIndex + 1] = offset + 2;
    elements[offsetArrayIndex + 2] = offset + 0;

    elements[offsetArrayIndex + 3] = offset + 0;
    elements[offsetArrayIndex + 4] = offset + 2;
    elements[offsetArrayIndex + 5] = offset + 1;
}




