#pragma once

enum class RenderPivot
{
	CENTER,		// �̹����� �߽��� �ǹ�
	BOT,		// �̹����� ���ϴ��� �ǹ�
};

enum class RenderScaleMode
{
	Image,		// �ҷ��� �̹��� ���������� ���
	User,		// ������ Ŀ������ ���������� ���
};

enum class CollisionType
{
	Point,
	Circle,
	Rect,
	Max
};