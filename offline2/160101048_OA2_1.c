#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a node for folders
typedef struct _fileNode {
	char fileName[21];
	struct _fileNode *filePtr;
}fileNode;

typedef struct _folderNode {
	char folderName[21];
	struct _folderNode *folderPtr;
	fileNode *filePtr;
}folderNode;

folderNode *createFolderNode() {
	return (folderNode *)malloc(sizeof(folderNode));
}

fileNode *createFileNode() {
	return (fileNode *)malloc(sizeof(fileNode));
}
 
folderNode *new(folderNode *currFolder, char name[21]) {
	folderNode *temp;
	temp = createFolderNode();
	strcpy(temp->folderName, name);
	currFolder->folderPtr = temp;
	printf("Made %s in %s\n", temp->folderName, currFolder->folderName);
	return currFolder->folderPtr;
}

folderNode *back(folderNode *root, folderNode *currFolder){
	if (currFolder == root) {
		printf("Cannot back from root\n");
	}
	else {
		while (root != NULL) {
			if (root->folderPtr == currFolder) {
				root->folderPtr == NULL;
				root->filePtr == NULL;
				printf("Back from %s\n", currFolder->folderName);
				break;
			}
			root = root->folderPtr;
		}
	}
	return root;
}

void create(folderNode *currFolder, char name[21]) {
	// if currFolder->filePtr is null create a new temp, insert name, assign temp to file->ptr;
	// if not null, create temp=head, forward temp, insert name.
	if (currFolder->filePtr == NULL) {
		fileNode *temp = createFileNode();
		strcpy(temp->fileName, name);
		temp->filePtr = NULL;
		currFolder->filePtr = temp;
	}
	else {
		fileNode *temp = currFolder->filePtr;
		while (temp->filePtr != NULL) {temp = temp->filePtr;}
		temp->filePtr = createFileNode();
		strcpy(temp->filePtr->fileName, name);
		temp->filePtr->filePtr = NULL;
	}
	printf("Created %s in %s\n", name, currFolder->folderName);
}
void delete(folderNode *currFolder) {
	if (currFolder->filePtr != NULL) {
		fileNode *temp = currFolder->filePtr;
		currFolder->filePtr = currFolder->filePtr->filePtr;
		printf("Deleted %s from %s\n", temp->fileName, currFolder->folderName);
	}
	else {
		printf("Cannot delete from %s\n", currFolder->folderName);
	}
}

void main() {
	folderNode *root = createFolderNode();
	strcpy(root->folderName, "root");
	folderNode *currFolder = root;
	printf("Enter input sequence:\n");
	while (1) {
		char cmd[7], name[21];
		scanf("%s", cmd);
		if (cmd[0] == '-' && cmd[1] == '1') break;
		if (strcmp(cmd, "NEW") == 0) {
			scanf(" %s", name);
			currFolder = new(currFolder, name);
		}
		if (strcmp(cmd, "BACK") == 0) {
			currFolder = back(root, currFolder);
		}
		if (strcmp(cmd, "CREATE") == 0) {
			scanf(" %s", name);
			create(currFolder, name);
		}
		if (strcmp(cmd, "DELETE") == 0) {
			delete(currFolder);
		}
	}
}