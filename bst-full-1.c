#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/*이진 탐색 트리는 다음 작업을 효율적으로 수행할 수 있는 데이터 구조입니다.
1. 값 삽입
2. 특정 값이 포함되어 있는지 쿼리
3. 값 삭제*/

typedef struct node {
	int key;
	struct node* left;
	struct node* right;
} Node;

int initializeBST(Node** h);

void inorderTraversal(Node* ptr);	  /* 재귀 중위 순회 */
void preorderTraversal(Node* ptr);  /* 재귀적 선주문 순회 */
void postorderTraversal(Node* ptr);	  /* 재귀적 후위 순회 */
int insert(Node* head, int key); /* 트리에 노드 삽입 */
int deleteLeafNode(Node* head, int key);  /* 키의 리프 노드 삭제 */
Node* searchRecursive(Node* ptr, int key);  /* 키에 대한 노드 검색 */
Node* searchIterative(Node* head, int key);  /* 키에 대한 노드 검색 */
int freeBST(Node* head); /* 트리에 할당된 모든 메모리 해제 */




int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	

	do {
		printf("\n\n");
		printf("[----- [CHEN YUXIANG]  [2020039089] -----]\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* 트리가 비어 있지 않으면 트리에서 할당된 모든 노드를 제거합니다*/
	if (*h != NULL)
		freeBST(*h);

	/* 헤드 노드 생성 */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* 루트 */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)
{
	if (ptr) {
		inorderTraversal(ptr->left);
		printf(" [%d] ", ptr->key);
		inorderTraversal(ptr->right);
	}
}

void preorderTraversal(Node* ptr)
{
	if (ptr) {
		printf(" [%d] ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

void postorderTraversal(Node* ptr)
{
	if (ptr) {
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf(" [%d] ", ptr->key);
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left가 루트 */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while (ptr != NULL) {

		/* 키에 대한 노드가 있으면 그냥 반환 */
		if (ptr->key == key) return 1;

		/* 자식 노드로 이동해야 합니다.
         * parentNode를 사용하여 부모를 계속 추적 */
		parentNode = ptr;

		/* 키 비교, 현재 노드의 키가 입력 키보다 큰 경우
         * 그러면 새 노드가 오른쪽 하위 트리에 삽입되어야 합니다.
         * 그렇지 않으면 왼쪽 하위 트리.
         */
		if (ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* 새 노드를 부모 노드에 연결 */
	if (parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}

int deleteLeafNode(Node* head, int key)
{
	if (head == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left가 루트 */
	Node* ptr = head->left;


	/* 자식 노드로 이동해야 합니다.
     * parentNode를 사용하여 부모를 계속 추적 */
	Node* parentNode = head;

	while (ptr != NULL) {

		if (ptr->key == key) {
			if (ptr->left == NULL && ptr->right == NULL) {

				/* 루트 노드의 경우 */
				if (parentNode == head)
					head->left = NULL;

				/* 왼쪽 노드 케이스 또는 오른쪽 케이스*/
				if (parentNode->left == ptr)
					parentNode->left = NULL;
				else
					parentNode->right = NULL;

				free(ptr);
			}
			else {
				printf("the node [%d] is not a leaf \n", ptr->key);
			}
			return 1;
		}

		/* 부모 노드를 유지 */
		parentNode = ptr;

		/* 키 비교, 현재 노드의 키가 입력 키보다 큰 경우
         * 그러면 새 노드가 오른쪽 하위 트리에 삽입되어야 합니다.
         * 그렇지 않으면 왼쪽 하위 트리.
         */
		if (ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;


	}

	printf("Cannot find the node for key [%d]\n ", key);

	return 1;
}

Node* searchRecursive(Node* ptr, int key)
{
	if (ptr == NULL)
		return NULL;

	if (ptr->key < key)
		ptr = searchRecursive(ptr->right, key);
	else if (ptr->key > key)
		ptr = searchRecursive(ptr->left, key);

	/* ptr->key == key인 경우 */
	return ptr;

}
Node* searchIterative(Node* head, int key)
{
	/* 루트 노드 */
	Node* ptr = head->left;

	while (ptr != NULL)
	{
		if (ptr->key == key)
			return ptr;

		if (ptr->key < key) ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	return NULL;
}

void freeNode(Node* ptr)
{
	if (ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if (head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}
