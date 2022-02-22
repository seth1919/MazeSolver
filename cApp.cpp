#include "cApp.h"
#include <vector>

wxIMPLEMENT_APP(cApp);

using namespace std;

cApp::cApp()
{
}


cApp::~cApp()
{
}

struct pixelTypeType {
	int type;
	unsigned int number;
	bool taken = false;
};

struct node {
	int y;
	int x;
	node* previous = nullptr;
	unsigned int distance;
	node* left = nullptr;
	node* top = nullptr;
	node* bottom = nullptr;
	node* right = nullptr;
};

struct coordinatesList {
	int y;
	int x;
	node* previous;
	unsigned int distance;
};

bool pathFindNonRecursive(int y, int x, vector<vector<pixelTypeType>>& pixelType, unsigned int distance, node* previous, vector<coordinatesList>& pending, vector<node*>& for_deletion) {
	//create a new node with the proper information
	node* newNode = new node;
	newNode->y = y;
	newNode->x = x;
	if (previous != nullptr) {
		newNode->previous = previous;
	}
	newNode->distance = distance;
	if (previous != nullptr) {
		if (previous->x < x) {
			previous->right = newNode;
		}
		else if (previous->x > x) {
			previous->left = newNode;
		}
		else if (previous->y < y) {
			previous->bottom = newNode;
		}
		else {
			previous->top = newNode;
		}
	}
	for_deletion.push_back(newNode);
	//remove self from the pending
	pending.pop_back();

	//if this is the start
	if (pixelType[y][x].type == 3) {
		//add just the bottom pixel to the pending
		coordinatesList NewCoordinate;
		NewCoordinate.y = y + 1;
		NewCoordinate.x = x;
		NewCoordinate.previous = newNode;
		NewCoordinate.distance = distance + 1;
		pending.push_back(NewCoordinate);
		return false;
	}
	else if (pixelType[y][x].type == 4) { //if this is the end
		//work your way up the chain of (previous)s, making the pixelType[][] = 2 each time
		pixelType[y][x].number = distance;
		node* searchNode = newNode->previous;
		while (pixelType[searchNode->y][searchNode->x].type != 3) {
			pixelType[searchNode->y][searchNode->x].type = 2;
			pixelType[searchNode->y][searchNode->x].number = searchNode->distance;
			searchNode = searchNode->previous;
		}
		//delete the whole linked list
		int y = 5;
		for (int i = 0; i < for_deletion.size(); i++) {
			delete (for_deletion[i]);
		}
		return true;
	}

	//for each of the adjascent pixels, if it's pixelType == 0 || pixelType == 4 add it to the pending
	//left
	if ((pixelType[y][x - 1].type == 0 || pixelType[y][x - 1].type == 4) && pixelType[y][x - 1].taken == false) {
		coordinatesList NewCoordinate;
		NewCoordinate.y = y;
		NewCoordinate.x = x - 1;
		NewCoordinate.previous = newNode;
		NewCoordinate.distance = distance + 1;
		pending.push_back(NewCoordinate);
		pixelType[y][x - 1].taken = true;
	}
	//top
	if ((pixelType[y - 1][x].type == 0 || pixelType[y - 1][x].type == 4) && pixelType[y - 1][x].taken == false) {
		coordinatesList NewCoordinate;
		NewCoordinate.y = y - 1;
		NewCoordinate.x = x;
		NewCoordinate.previous = newNode;
		NewCoordinate.distance = distance + 1;
		pending.push_back(NewCoordinate);
		pixelType[y - 1][x].taken = true;
	}
	//bottom
	if ((pixelType[y + 1][x].type == 0 || pixelType[y + 1][x].type == 4) && pixelType[y + 1][x].taken == false) {
		coordinatesList NewCoordinate;
		NewCoordinate.y = y + 1;
		NewCoordinate.x = x;
		NewCoordinate.previous = newNode;
		NewCoordinate.distance = distance + 1;
		pending.push_back(NewCoordinate);
		pixelType[y + 1][x].taken = true;
	}
	//right
	if ((pixelType[y][x + 1].type == 0 || pixelType[y][x + 1].type == 4) && pixelType[y][x + 1].taken == false) {
		coordinatesList NewCoordinate;
		NewCoordinate.y = y;
		NewCoordinate.x = x + 1;
		NewCoordinate.previous = newNode;
		NewCoordinate.distance = distance + 1;
		pending.push_back(NewCoordinate);
		pixelType[y][x + 1].taken = true;
	}
	return false;
}

bool pathFind(int y, int x, vector<vector<pixelTypeType>> &pixelType, unsigned int distance) {
	pixelType[y][x].taken = true;
	if (pixelType[y][x].type == 3) { //is this the start
		pathFind(y + 1, x, pixelType, distance + 1);
		pixelType[y][x].number = distance;
		return true;
	}
	else if (pixelType[y][x].type == 4) { //is this the end
		pixelType[y][x].number = distance;
		return true;
	}
	//call pathfind on all adjascent corridors
	if ((pixelType[y - 1][x].type == 0 || pixelType[y-1][x].type == 4) && pixelType[y-1][x].taken == false) {
		if (pathFind(y - 1, x, pixelType, distance + 1) == true) {
			pixelType[y][x].type = 2;
			pixelType[y][x].number = distance;
			return true;
		}
	}
	if ((pixelType[y][x - 1].type == 0 || pixelType[y][x - 1].type == 4) && pixelType[y][x - 1].taken == false) {
		if (pathFind(y, x - 1, pixelType, distance + 1) == true) {
			pixelType[y][x].type = 2;
			pixelType[y][x].number = distance;
			return true;
		}
	}
	if ((pixelType[y][x + 1].type == 0 || pixelType[y][x + 1].type == 4) && pixelType[y][x + 1].taken == false) {
		if (pathFind(y, x + 1, pixelType, distance + 1) == true) {
			pixelType[y][x].type = 2;
			pixelType[y][x].number = distance;
			return true;
		}
	}
	if ((pixelType[y + 1][x].type == 0 || pixelType[y+1][x].type == 4) && pixelType[y + 1][x].taken == false) {
		if (pathFind(y + 1, x, pixelType, distance + 1) == true) {
			pixelType[y][x].type = 2;
			pixelType[y][x].number = distance;
			return true;
		}
	}
	return false;
}

class Maze1 {
public:
	Maze1() {
		wxFileDialog dlg(nullptr, "Open image File", "", "", "*.*", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
		if (dlg.ShowModal() == wxID_OK)
		{
			//create input image
			wxInitAllImageHandlers();
			wxImage* input_Image = new wxImage;
			input_Image->LoadFile(dlg.GetPath());
			unsigned char* input_Image_Data = input_Image->GetData();

			//create path datastructure
			// 0 = corridor (white)
			// 1 = wall (black)
			// 2 = path (red/blue)
			// 3 = start (red)
			// 4 = finish (blue)
			vector<vector<pixelTypeType>> pixelType;
			//initialize the structure with walls and corridors
			//for every row in the image (top to bottom)
			for (int i = 0; i < input_Image->GetHeight(); i++) {
				//for every column in the image (left to right)
				vector<pixelTypeType> row;
				for (int j = 0; j < input_Image->GetWidth(); j++) {
					if (*input_Image_Data == 255) {
						pixelTypeType newType;
						newType.type = 0;
						row.push_back(newType);
					}
					else {
						pixelTypeType newType;
						newType.type = 1;
						row.push_back(newType);
					}
					input_Image_Data++;
					input_Image_Data++;
					input_Image_Data++;
				}
				pixelType.push_back(row);
			}
			int x = 0;
			int y = 0;
			//for every pixel in the first row
			for (int i = 0; i < pixelType[0].size(); i++) {
				if (pixelType[0][i].type == 0) {
					pixelType[0][i].type = 3;
					x = i;
				}
			}
			int xFinish = 0;
			int yFinish = pixelType.size() - 1;
			//for every pixel in the last row
			for (int i = 0; i < pixelType[pixelType.size() - 1].size(); i++) {
				if (pixelType[pixelType.size() - 1][i].type == 0) {
					pixelType[pixelType.size() - 1][i].type = 4;
					xFinish = i;
				}
			}
			//create list of (pixelType[][])s and (previous)s to be added to the tree
			vector<coordinatesList> pending;
			//create the first pending at the start position
			coordinatesList start;
			start.x = x;
			start.y = y;
			start.distance = 0;
			start.previous = nullptr;
			pending.push_back(start);
			bool finished = false;
			vector<node*> for_deletion;
			while (finished == false) {
				//call pathFindNonRecursive on the next node in the list
				finished = pathFindNonRecursive(pending[pending.size() - 1].y, pending[pending.size() - 1].x, pixelType, pending[pending.size() - 1].distance, pending[pending.size() - 1].previous, pending, for_deletion);
			}

			//create output image
			wxImage* output_Image = new wxImage(wxSize(input_Image->GetWidth(), input_Image->GetHeight()), true);
			unsigned char* output_Image_Data = output_Image->GetData();
			// 0 = corridor (white)
			// 1 = wall (black)
			// 2 = path (red/blue)
			// 3 = start (red)
			// 4 = finish (blue)
			//for every pixel in the output image
			for (int i = 0; i < output_Image->GetHeight(); i++) {
				for (int j = 0; j < output_Image->GetWidth(); j++) {
					switch (pixelType[i][j].type) {
					case 0:
						*output_Image_Data = 255;
						output_Image_Data++;
						*output_Image_Data = 255;
						output_Image_Data++;
						*output_Image_Data = 255;
						output_Image_Data++;
						break;
					case 1:
						*output_Image_Data = 0;
						output_Image_Data++;
						*output_Image_Data = 0;
						output_Image_Data++;
						*output_Image_Data = 0;
						output_Image_Data++;
						break;
					case 2:
						*output_Image_Data = 255 - ((double)(pixelType[i][j].number / (double)pixelType[yFinish][xFinish].number) * (double)255);
						output_Image_Data++;
						*output_Image_Data = 0;
						output_Image_Data++;
						*output_Image_Data = (unsigned char)((double)(pixelType[i][j].number / (double)pixelType[yFinish][xFinish].number) * (double)255);
						output_Image_Data++;
						break;
					case 3:
						*output_Image_Data = 255;
						output_Image_Data++;
						*output_Image_Data = 0;
						output_Image_Data++;
						*output_Image_Data = 0;
						output_Image_Data++;
						break;
					case 4:
						*output_Image_Data = 0;
						output_Image_Data++;
						*output_Image_Data = 0;
						output_Image_Data++;
						*output_Image_Data = 255;
						output_Image_Data++;
						break;
					}
				}
			}

			wxFileDialog dlg(nullptr, "Save png File", "", "", ".png Files (*.png)|*.png", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
			if (dlg.ShowModal() == wxID_OK)
			{
				output_Image->SaveFile(dlg.GetPath(), wxBITMAP_TYPE_PNG);
			}
			delete output_Image;
			delete input_Image;
		}
	}
};

bool cApp::OnInit()
{
	Maze1* solveMaze = new Maze1();
	delete solveMaze;

	m_frame1 = new cMain();
	//m_frame1->Show();

	return true;
}
