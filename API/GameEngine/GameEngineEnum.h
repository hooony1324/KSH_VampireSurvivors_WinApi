#pragma once

enum class RenderPivot
{
	CENTER,		// 이미지의 중심이 피벗
	BOT,		// 이미지의 중하단이 피벗
};

enum class RenderScaleMode
{
	Image,		// 불러온 이미지 설정값으로 사용
	User,		// 유저가 커스텀한 설정값으로 사용
};