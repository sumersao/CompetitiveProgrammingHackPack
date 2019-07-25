export void fillFirstRow(uniform int data[], 
					uniform int row[], uniform int N) {
	foreach(i = 0 ... N) {
		if(data[i] < data[i+1])
			row[i] = i;
		else
			row[i] = i+1;
	}
}

export void fillOtherRows(uniform int data[], 
					uniform int row1[], uniform int row2[], 
					uniform int N, uniform int pow) {
	foreach(i = 0 ... N) {
		if(data[row1[i]] < data[row1[i+pow]])
			row2[i] = row1[i];
		else
			row2[i] = row1[i+pow];
	}
}

export void findBlockMinimums(uniform int data[], uniform int topMinimums[], uniform int topMinimumsInd[],
							  uniform int topSize, uniform int blockSize) {
	foreach(i = 0 ... topSize) {
		int min = data[i * blockSize];
		int ind = i * blockSize;
		for(int j = 0; j < blockSize; j++) {
			if(data[i * blockSize + j] < min) {
				min = data[i * blockSize + j];
				ind = i*blockSize + j;
			}
		}
		topMinimums[i] = min;
		topMinimumsInd[i] = ind;
	}
}