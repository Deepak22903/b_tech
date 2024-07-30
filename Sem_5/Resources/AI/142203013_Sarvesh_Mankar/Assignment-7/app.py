# A simple Python3 program to find
# maximum score that
# maximizing player can get
import math

def minimax (curDepth, nodeIndex,
			maxTurn, data, 
			targetDepth):

	# base case : targetDepth reached
	if (curDepth == targetDepth): 
		return data[nodeIndex]
	
	if (maxTurn):
		return max(minimax(curDepth + 1, nodeIndex * 2, 
					False, data, targetDepth), 
				minimax(curDepth + 1, nodeIndex * 2 + 1, 
					False, data, targetDepth))
	
	else:
		return min(minimax(curDepth + 1, nodeIndex * 2, 
					True, data, targetDepth), 
				minimax(curDepth + 1, nodeIndex * 2 + 1, 
					True, data, targetDepth))
	
# Test Case - 1
print("Test Case - 1")
lst = [3, 1, 7, 9, 2, 1, 9, 13]
treeDepth = math.log(len(lst), 2)
print("The optimal value is : ", end = "")
print(minimax(0, 0, True, lst, treeDepth))

# Test Case - 2
print("Test Case - 2")
lst = [3, 4, 2, 1, 7, 8, 9, 10, 2, 11, 1, 12, 14, 9, 13, 16]
treeDepth = math.log(len(lst), 2)
print("The optimal value is : ", end = "")
print(minimax(0, 0, True, lst, treeDepth))
