//#pragma once
//void HeapInsert(int index) {//½¨¶Ñ
//	int parentindex = (index - 1) / 2;
//	while (arry[index] < arry[parentindex]) {
//		swapcnt++;
//		cmpcnt++;
//		swap(arry[index], arry[parentindex]);
//		index = parentindex;
//		parentindex = (index - 1) / 2;
//	}
//}
//
//void Heapify(int index = 0) {
//	swap(arry[index], arry[currlen - 1]);
//	currlen--;
//	int leftindex = 2 * index + 1;
//	int rightindex = leftindex + 1;
//	while (leftindex < currlen) {
//		cmpcnt++;
//		int min = (rightindex >= currlen || arry[leftindex] < arry[rightindex]) ? arry[leftindex] : arry[rightindex];
//		int minindex = (rightindex >= currlen || arry[leftindex] < arry[rightindex]) ? leftindex : rightindex;
//		if (min >= arry[index]) {
//			break;
//		}
//		else {
//			swap(arry[index], arry[minindex]);
//			swapcnt++;
//			index = minindex;
//			leftindex = 2 * index + 1;
//			rightindex = leftindex + 1;
//		}
//	}
//}
//
//
//void HeapSort() {
//	for (int i = 0; i < len; i++) HeapInsert(i);
//	ofstream outfile("outputfile.txt");
//	for (int i = 0; i < len; i++) {
//		outfile << (int)arry[0] << " ";
//		Heapify();
//	}
//	cout << "Comparasion count:" << cmpcnt << endl << "Swap count:" << swapcnt << endl;
//}