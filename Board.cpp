#include "board.h"

//��ʼ��
void Board::initialize(int type)
{
	if (type == 1){
		// �Ȱ������ϵ�ÿ��λ�ö���ʼ��Ϊ�գ�level = 13��
		for (int i = 0; i < BOARD_ROWS; ++i) {
			for (int j = 0; j < BOARD_COLS; ++j) {
				board[i][j] = Piece(13, 0, false, i, j);  // ��ʼ��Ϊ��
			}
		}
		// �����Ϸ�����
		std::srand(std::time(0));
		std::vector<int> pieceLevels1 = { 9, 8, 7, 7, 6, 6, 5, 5, 4, 4, 3, 3, 3, 2, 2, 2, 1, 1, 1, 10, 10, 11 };
		for (int i = 0; i <= 5; ++i) {
			for (int j = 0; j <= 4; ++j) {
				if (i == 0 && j == 3) {
					board[i][j] = Piece(12, 1, 1, i, j);  // �Ϸ��ľ���
				}
				else if ((i == 0 && (j == 2 || j == 4))) {
					board[i][j] = Piece(11, 1, 1, i, j);  // �Ϸ��ĵ���
				}
				else if ((i == 2 && (j == 1 || j == 3)) || (i == 3 && j == 2) || (i == 4 && (j == 1 || j == 3))) {
					board[i][j] = Piece(13, 1, 0, i, j);  // �Ϸ�����Ӫ����
				}
				else {
					if (!pieceLevels1.empty()) {
						int length = pieceLevels1.size();
						int randomNumber = std::rand() % length;  // 0 �� length-1 ֮��������
						board[i][j] = Piece(pieceLevels1[randomNumber], 1, 0, i, j);  // ����λ�������������
						pieceLevels1.erase(pieceLevels1.begin() + randomNumber);
					}
				}
			}
		}
		// �����·�����
		std::vector<int> pieceLevels2 = { 9, 8, 7, 7, 6, 6, 5, 5, 4, 4, 3, 3, 3, 2, 2, 2, 1, 1, 1, 10, 10, 11 };
		for (int i = 6; i <= 12; ++i) {
			for (int j = 0; j <= 4; ++j) {
				if (i == 11 && j == 1) {
					board[i][j] = Piece(12, 2, 1, i, j);  // �·��ľ���
				}
				else if (i == 11 && (j == 0 || j == 2)) {
					board[i][j] = Piece(11, 2, 1, i, j);  // �·��ĵ���
				}
				else if ((i == 7 && (j == 1 || j == 3)) || (i == 9 && j == 2) || (i == 10 && (j == 1 || j == 3))) {
					board[i][j] = Piece(13, 2, 0, i, j);  // �·�����Ӫ����
				}
				else {
					if (!pieceLevels2.empty()) {
						int length = pieceLevels2.size();
						int randomNumber = std::rand() % length;  // 0 �� length-1 ֮��������
						board[i][j] = Piece(pieceLevels2[randomNumber], 2, 0, i, j);  // ����λ�������������
						pieceLevels2.erase(pieceLevels2.begin() + randomNumber);
					}
				}
			}
		}
	}
	else
	{

	}
}

//��ӡ����
void Board::printBoard() const {
	for (int i = 0; i < BOARD_ROWS; ++i) {
		for (int j = 0; j < BOARD_COLS; ++j) {
			//std::cout << "Piece[" << i << "][" << j << "] - ";
			//std::cout << "Level: " << board[i][j].level << ", ";
			std::cout << board[i][j].level << " ";
			//std::cout << "Player: " << board[i][j].player << ", ";
			//std::cout << "FaceUp: " << board[i][j].isFaceUp << std::endl;
		}
		std::cout << std::endl;
	}
}

//move
int Board::move(int currentX, int currentY, int nextX, int nextY) {
	int levelcr = board[currentX][currentY].getLevel();
	int levelnt = board[nextX][nextY].getLevel();
	int playcr = board[currentX][currentY].getPlayer();
	int playnt = board[nextX][nextY].getPlayer();
	int wret = 0;


	if (playcr == playnt)
	{
		std::cout << "��ͬ��Ӫ������" << std::endl;
		return 0;
	}




	int xydiff = abs(nextX + nextY - currentX - currentY);
	if (xydiff == 1)
		wret = 1;
	if (xydiff == 2)
	{
		if (abs(nextX - currentX) == 1 && abs(nextY - currentY) == 1)
		{
			if ((nextX == 2 || nextX == 3 || nextX == 4 || nextX == 7 || nextX == 8 || nextX == 9) && (nextY == 1 || nextY == 2 || nextY == 3))
				wret = 1;
			if ((currentX == 2 || currentX == 3 || currentX == 4 || currentX == 7 || currentX == 8 || currentX == 9) && (currentY == 1 || currentY == 2 || currentY == 3))
				wret = 1;
		}
		if (nextX == currentX || nextY == currentY)
		{
			if (nextX == 5 || nextX == 6)
			{
				if (currentX == 5 || currentX == 6)
					wret = 1;
			}
		}
	}
	if (xydiff > 2)
	{
		if (nextX == currentX || nextY == currentY)
		{
			if (nextX == 5 || nextX == 6)
			{
				if (currentX == 5 || currentX == 6)
					wret = 1;
			}
		}
	}


	if (wret == 0)
	{
		printf("�ƶ����Ϸ�");
		return 0;
	}



	//���жϸ������ǲ��� ���׺;���
	if (levelcr == 11 || levelcr == 12)
	{
		printf("���������ǲ��ܶ���");
	}
	else
	{
		// �жϵȼ��ǲ���С�ڶԷ�
		if (levelcr < levelnt)
		{
			//���ж϶Է��ǲ���ը���͵���
			if (levelnt == 10 || levelnt == 11)
			{
				//�ж��Լ��ǲ��ǹ���
				if (levelcr == 1)
				{
					//printf("������ը�����ߵ���");
					//�ѵ�ǰ�����ƹ�ȥ
					board[nextX][nextY].setPosition(currentX, currentY);
					board[nextX][nextY].setLevel(board[currentX][currentY].getLevel());
					board[nextX][nextY].setPlayer(board[currentX][currentY].getPlayer());
					board[nextX][nextY].setIsFaceUp(board[currentX][currentY].getIsFaceUp());
					//��յ�ǰ����
					board[currentX][currentY].setLevel(13);
					return 1;
				}
				else
				{
					//printf("��ը���͵���ը��");
					board[currentX][currentY].setLevel(13);
					board[nextX][nextY].setLevel(13);
					return 1;
				}

			}
			else
			{
				//�ж϶Է��ǲ��Ǿ���
				if (levelnt == 12)
				{
					//printf("�Ծ���");
					//�ѵ�ǰ�����ƹ�ȥ
					board[nextX][nextY].setPosition(currentX, currentY);
					board[nextX][nextY].setLevel(board[currentX][currentY].getLevel());
					board[nextX][nextY].setPlayer(board[currentX][currentY].getPlayer());
					board[nextX][nextY].setIsFaceUp(board[currentX][currentY].getIsFaceUp());
					//��յ�ǰ����
					board[currentX][currentY].setLevel(13);
					return 1;
				}
				else
				{
					//�������û����
					if (levelnt == 13)
					{
						//printf("�ƶ����ӵ��ո�ط�");
						//�ѵ�ǰ�����ƹ�ȥ
						board[nextX][nextY].setPosition(currentX, currentY);
						board[nextX][nextY].setLevel(board[currentX][currentY].getLevel());
						board[nextX][nextY].setPlayer(board[currentX][currentY].getPlayer());
						board[nextX][nextY].setIsFaceUp(board[currentX][currentY].getIsFaceUp());
						//��յ�ǰ����
						board[currentX][currentY].setLevel(13);
						return 1;
					}
					else
					{
						if (board[nextX][nextY].getIsFaceUp() == 0)
						{
							//printf("�Ա��ŵ�����");
							//��յ�ǰ����
							board[currentX][currentY].setLevel(13);
							board[nextX][nextY].setIsFaceUp(1);
							return 1;

						}
						else
						{
							//printf("���ӵȼ�û�Է��߲����ƶ�");
							return 0;
						}
						
					}
				}
			}
		}
		//����ȼ���С�ڶԷ�
		else
		{
			if (levelcr == levelnt)
			{
				//printf("���һ����");
				board[currentX][currentY].setLevel(13);
				board[nextX][nextY].setLevel(13);
				return 1;
			}
			else
			{
				//�ѵ�ǰ�����ƹ�ȥ
				//printf("���С");
				board[nextX][nextY].setPosition(currentX, currentY);
				board[nextX][nextY].setLevel(board[currentX][currentY].getLevel());
				board[nextX][nextY].setPlayer(board[currentX][currentY].getPlayer());
				board[nextX][nextY].setIsFaceUp(board[currentX][currentY].getIsFaceUp());
				//��յ�ǰ����
				board[currentX][currentY].setLevel(13);
				return 1;
			}
		}
	}

}

// �����Ƿ񷭿�
int Board::isFaceup(int currentX, int currentY){
	int ret = board[currentX][currentY].getIsFaceUp();
	return ret;
}

// �����������
int Board::getplayer(int xret, int yret){
	return board[xret][yret].getPlayer();
}

// �Ƿ��������
int Board::existPiece(int xret, int yret){
	int l = board[xret][yret].getLevel();
	if (l == 13)
	{
		return 0;
	}
	else
	{
		return 1;
	}

}

// ��������״̬
std::string Board::getBoardState(){
	std::string result = "";
	for (int i = 0; i < BOARD_ROWS; ++i) {
		for (int j = 0; j < BOARD_COLS; ++j) {
			int re = ((board[i][j].player - 1) * 13 + board[i][j].level) * board[i][j].isFaceUp;
			result = result + std::to_string(re) + ",";
		}
	}
	//std::cout << result << std::endl;
	return result;
}

int Board::getLevel(int x,int y){
	return board[x][y].getLevel();
}

void Board::setOpen(int x,int y){
	board[x][y].setIsFaceUp(1);
}
