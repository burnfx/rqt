#ifndef RECORDNAMES_H_
#define RECORDNAMES_H_


#include <string>

// first dimension = block_num
// second dimension = seq_num
// third dimension = row/column of record file
// row = range(1:152) = filename = setup
// column = range(1:5 = data reduction amount
extern int recordIDs[9][10][2];

extern std::string recordFiles[152][5];
#endif
