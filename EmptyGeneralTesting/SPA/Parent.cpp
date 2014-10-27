#include <Parent.h>

// Default constructor
Parent::Parent() {
	// empty constructor
}

// Methods
void Parent::SetParent(int parentStmtIndex, int childStmtIndex) {

}

bool Parent::IsParent(int parentStmtIndex, int childStmtIndex) {
	return false;
}

int Parent::GetChildrenOf(int parentStmtIndex) {
	return -123;
}

int Parent::GetParentOf(int childStmtIndex) {
	return -123;
}