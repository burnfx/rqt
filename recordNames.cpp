#include <string>

// first dimension = block_num
// second dimension = seq_num
// third dimension = row/column of record file
// row = range(1:152) = filename = setup
// column = range(1:5 = data reduction amount
int recordIDs[3][9][10][2] = {
    {{{1, 1},{2, 1},{3, 1},{4, 1},{5, 1},{6, 1},{7, 1},{8, 1},{9, 1},{0, 1}},
    {{11, 1},{12, 1},{13, 1},{14, 1},{15, 1},{16, 1},{17, 1},{18, 1},{19, 1},{10, 1}},
    {{21, 1},{22, 1},{23, 1},{24, 1},{25, 1},{26, 1},{27, 1},{28, 1},{29, 1},{20, 1}},
    {{31, 1},{32, 1},{33, 1},{34, 1},{35, 1},{36, 1},{37, 1},{38, 1},{39, 1},{30, 1}},
    {{41, 1},{42, 1},{43, 1},{44, 1},{45, 1},{46, 1},{47, 1},{48, 1},{49, 1},{40, 1}},
    {{51, 1},{52, 1},{53, 1},{54, 1},{55, 1},{56, 1},{57, 1},{58, 1},{59, 1},{50, 1}},
    {{61, 1},{62, 1},{63, 1},{64, 1},{65, 1},{66, 1},{67, 1},{68, 1},{69, 1},{60, 1}},
    {{71, 1},{72, 1},{73, 1},{73, 1},{73, 1},{73, 1},{73, 1},{73, 1},{73, 1},{70, 1}},
    {{71, 1},{72, 1},{73, 1},{73, 1},{73, 1},{73, 1},{73, 1},{73, 1},{73, 1},{73, 1}}},

    {{{1, 1},{2, 1},{3, 1},{4, 1},{5, 1},{6, 1},{7, 1},{8, 1},{9, 1},{0, 1}},
    {{11, 1},{12, 1},{13, 1},{14, 1},{15, 1},{16, 1},{17, 1},{18, 1},{19, 1},{10, 1}},
    {{21, 1},{22, 1},{23, 1},{24, 1},{25, 1},{26, 1},{27, 1},{28, 1},{29, 1},{20, 1}},
    {{31, 1},{32, 1},{33, 1},{34, 1},{35, 1},{36, 1},{37, 1},{38, 1},{39, 1},{30, 1}},
    {{41, 1},{42, 1},{43, 1},{44, 1},{45, 1},{46, 1},{47, 1},{48, 1},{49, 1},{40, 1}},
    {{51, 1},{52, 1},{53, 1},{54, 1},{55, 1},{56, 1},{57, 1},{58, 1},{59, 1},{50, 1}},
    {{61, 1},{62, 1},{63, 1},{64, 1},{65, 1},{66, 1},{67, 1},{68, 1},{69, 1},{60, 1}},
    {{71, 1},{72, 1},{73, 1},{73, 1},{73, 1},{73, 1},{73, 1},{73, 1},{73, 1},{70, 1}},
    {{71, 1},{72, 1},{73, 1},{73, 1},{73, 1},{73, 1},{73, 1},{73, 1},{73, 1},{73, 1}}},

    {{{1, 1},{2, 1},{3, 1},{4, 1},{5, 1},{6, 1},{7, 1},{8, 1},{9, 1},{0, 1}},
    {{11, 1},{12, 1},{13, 1},{14, 1},{15, 1},{16, 1},{17, 1},{18, 1},{19, 1},{10, 1}},
    {{21, 1},{22, 1},{23, 1},{24, 1},{25, 1},{26, 1},{27, 1},{28, 1},{29, 1},{20, 1}},
    {{31, 1},{32, 1},{33, 1},{34, 1},{35, 1},{36, 1},{37, 1},{38, 1},{39, 1},{30, 1}},
    {{41, 1},{42, 1},{43, 1},{44, 1},{45, 1},{46, 1},{47, 1},{48, 1},{49, 1},{40, 1}},
    {{51, 1},{52, 1},{53, 1},{54, 1},{55, 1},{56, 1},{57, 1},{58, 1},{59, 1},{50, 1}},
    {{61, 1},{62, 1},{63, 1},{64, 1},{65, 1},{66, 1},{67, 1},{68, 1},{69, 1},{60, 1}},
    {{71, 1},{72, 1},{73, 1},{73, 1},{73, 1},{73, 1},{73, 1},{73, 1},{73, 1},{70, 1}},
    {{71, 1},{72, 1},{73, 1},{73, 1},{73, 1},{73, 1},{73, 1},{73, 1},{73, 1},{73, 1}}}
    };

std::string recordFiles[54][5] = {
    {"e0d30l1m1r1h444","e0d30l1m1r1h444","e0d30l1m1r1h444","e0d30l1m1r1h444","e0d30l1m1r1h444"},
    {"e0d30l1m2r1h444","e0d30l1m2r1h444","e0d30l1m2r1h444","e0d30l1m2r1h444","e0d30l1m2r1h444"},
    {"e1d60l1m2r1h111","e1d60l1m2r1h111","e1d60l1m2r1h111","e1d60l1m2r1h111","e1d60l1m2r1h111"},
    {"e1d30l1m2r6h111f123","e1d30l1m2r6h111f123","e1d30l1m2r6h111f123","e1d30l1m2r6h111f123","e1d30l1m2r6h111f123"},
    {"e1d30l6m5r1h111f321","e1d30l6m5r1h111f321","e1d30l6m5r1h111f321","e1d30l6m5r1h111f321","e1d30l6m5r1h111f321"},
    {"e1d60l1m1r1h111","e1d60l1m1r1h111","e1d60l1m1r1h111","e1d60l1m1r1h111","e1d60l1m1r1h111"},
    {"e0d30l2m1r1h444","e0d30l2m1r1h444","e0d30l2m1r1h444","e0d30l2m1r1h444","e0d30l2m1r1h444"},
    {"e0d30l1m1r4h444","e0d30l1m1r4h444","e0d30l1m1r4h444","e0d30l1m1r4h444","e0d30l1m1r4h444"},
    {"e0d60l1m1r2h444","e0d60l1m1r2h444","e0d60l1m1r2h444","e0d60l1m1r2h444","e0d60l1m1r2h444"},
    {"e0d60l6m1r1h444","e0d60l6m1r1h444","e0d60l6m1r1h444","e0d60l6m1r1h444","e0d60l6m1r1h444"},
    {"e0d60l1m1r4h444","e0d60l1m1r4h444","e0d60l1m1r4h444","e0d60l1m1r4h444","e0d60l1m1r4h444"},
    {"e0d30l4m1r1h444","e0d30l4m1r1h444","e0d30l4m1r1h444","e0d30l4m1r1h444","e0d30l4m1r1h444"},
    {"e1d30l1m2r3h311f123","e1d30l1m2r3h311f123","e1d30l1m2r3h311f123","e1d30l1m2r3h311f123","e1d30l1m2r3h311f123"},
    {"e0d60l4m1r1h444","e0d60l4m1r1h444","e0d60l4m1r1h444","e0d60l4m1r1h444","e0d60l4m1r1h444"},
    {"e1d30l1m4r1h111","e1d30l1m4r1h111","e1d30l1m4r1h111","e1d30l1m4r1h111","e1d30l1m4r1h111"},
    {"e1d30l6m1r1h111","e1d30l6m1r1h111","e1d30l6m1r1h111","e1d30l6m1r1h111","e1d30l6m1r1h111"},
    {"e1d30l1m1r1h111","e1d30l1m1r1h111","e1d30l1m1r1h111","e1d30l1m1r1h111","e1d30l1m1r1h111"},
    {"e1d30l1m6r1h111","e1d30l1m6r1h111","e1d30l1m6r1h111","e1d30l1m6r1h111","e1d30l1m6r1h111"},
    {"e1d30l1m3r1h111f312","e1d30l1m3r1h111f312","e1d30l1m3r1h111f312","e1d30l1m3r1h111f312","e1d30l1m3r1h111f312"},
    {"e1d60l6m1r1h111","e1d60l6m1r1h111","e1d60l6m1r1h111","e1d60l6m1r1h111","e1d60l6m1r1h111"},
    {"e0d60l1m6r1h444","e0d60l1m6r1h444","e0d60l1m6r1h444","e0d60l1m6r1h444","e0d60l1m6r1h444"},
    {"e1d60l1m1r6h111","e1d60l1m1r6h111","e1d60l1m1r6h111","e1d60l1m1r6h111","e1d60l1m1r6h111"},
    {"e1d30l4m1r1h111","e1d30l4m1r1h111","e1d30l4m1r1h111","e1d30l4m1r1h111","e1d30l4m1r1h111"},
    {"e0d30l6m1r1h444","e0d30l6m1r1h444","e0d30l6m1r1h444","e0d30l6m1r1h444","e0d30l6m1r1h444"},
    {"e0d60l2m1r1h444","e0d60l2m1r1h444","e0d60l2m1r1h444","e0d60l2m1r1h444","e0d60l2m1r1h444"},
    {"e0d30l1m1r6h444","e0d30l1m1r6h444","e0d30l1m1r6h444","e0d30l1m1r6h444","e0d30l1m1r6h444"},
    {"e0d60l1m1r1h444","e0d60l1m1r1h444","e0d60l1m1r1h444","e0d60l1m1r1h444","e0d60l1m1r1h444"},
    {"e0d30l1m4r1h444","e0d30l1m4r1h444","e0d30l1m4r1h444","e0d30l1m4r1h444","e0d30l1m4r1h444"},
    {"e1d30l1m1r1h122f333","e1d30l1m1r1h122f333","e1d30l1m1r1h122f333","e1d30l1m1r1h122f333","e1d30l1m1r1h122f333"},
    {"e1d30l1m1r6h111","e1d30l1m1r6h111","e1d30l1m1r6h111","e1d30l1m1r6h111","e1d30l1m1r6h111"},
    {"e1d30l1m3r1h111f132","e1d30l1m3r1h111f132","e1d30l1m3r1h111f132","e1d30l1m3r1h111f132","e1d30l1m3r1h111f132"},
    {"e1d30l2m1r3h121f213","e1d30l2m1r3h121f213","e1d30l2m1r3h121f213","e1d30l2m1r3h121f213","e1d30l2m1r3h121f213"},
    {"e0d30l1m1r2h444","e0d30l1m1r2h444","e0d30l1m1r2h444","e0d30l1m1r2h444","e0d30l1m1r2h444"},
    {"e1d30l6m3r1h111f321","e1d30l6m3r1h111f321","e1d30l6m3r1h111f321","e1d30l6m3r1h111f321","e1d30l6m3r1h111f321"},
    {"e1d30l1m2r3h211f123","e1d30l1m2r3h211f123","e1d30l1m2r3h211f123","e1d30l1m2r3h211f123","e1d30l1m2r3h211f123"},
    {"e1d30l1m2r3h111f123","e1d30l1m2r3h111f123","e1d30l1m2r3h111f123","e1d30l1m2r3h111f123","e1d30l1m2r3h111f123"},
    {"e0d60l1m2r1h444","e0d60l1m2r1h444","e0d60l1m2r1h444","e0d60l1m2r1h444","e0d60l1m2r1h444"},
    {"e1d30l1m1r4h111","e1d30l1m1r4h111","e1d30l1m1r4h111","e1d30l1m1r4h111","e1d30l1m1r4h111"},
    {"e0d60l1m4r1h444","e0d60l1m4r1h444","e0d60l1m4r1h444","e0d60l1m4r1h444","e0d60l1m4r1h444"},
    {"e1d30l1m2r3h111f321","e1d30l1m2r3h111f321","e1d30l1m2r3h111f321","e1d30l1m2r3h111f321","e1d30l1m2r3h111f321"},
    {"e1d30l1m1r2h111","e1d30l1m1r2h111","e1d30l1m1r2h111","e1d30l1m1r2h111","e1d30l1m1r2h111"},
    {"e1d30l1m2r1h111","e1d30l1m2r1h111","e1d30l1m2r1h111","e1d30l1m2r1h111","e1d30l1m2r1h111"},
    {"e1d60l4m1r1h111","e1d60l4m1r1h111","e1d60l4m1r1h111","e1d60l4m1r1h111","e1d60l4m1r1h111"},
    {"e1d60l1m1r4h111","e1d60l1m1r4h111","e1d60l1m1r4h111","e1d60l1m1r4h111","e1d60l1m1r4h111"},
    {"e1d60l2m1r1h111","e1d60l2m1r1h111","e1d60l2m1r1h111","e1d60l2m1r1h111","e1d60l2m1r1h111"},
    {"e0d30l1m6r1h444","e0d30l1m6r1h444","e0d30l1m6r1h444","e0d30l1m6r1h444","e0d30l1m6r1h444"},
    {"e1d60l1m1r2h111","e1d60l1m1r2h111","e1d60l1m1r2h111","e1d60l1m1r2h111","e1d60l1m1r2h111"},
    {"e1d60l1m4r1h111","e1d60l1m4r1h111","e1d60l1m4r1h111","e1d60l1m4r1h111","e1d60l1m4r1h111"},
    {"e1d30l2m1r1h111","e1d30l2m1r1h111","e1d30l2m1r1h111","e1d30l2m1r1h111","e1d30l2m1r1h111"},
    {"e1d30l1m4r6h111f123","e1d30l1m4r6h111f123","e1d30l1m4r6h111f123","e1d30l1m4r6h111f123","e1d30l1m4r6h111f123"},
    {"e0d60l1m1r6h444","e0d60l1m1r6h444","e0d60l1m1r6h444","e0d60l1m1r6h444","e0d60l1m1r6h444"},
    {"e1d60l1m6r1h111","e1d60l1m6r1h111","e1d60l1m6r1h111","e1d60l1m6r1h111","e1d60l1m6r1h111"}};
