//1997-3-10 by qyz
#include <room.h>

inherit ROOM;


void create()
{
	set("short","上天梯");
	set("long",@LONG
這裏是唐貞年間，有位仁果禪師在崆峒山開山闢路，鑿通的通向最高峯的唯
一通道“上天梯”，山勢奇險，每逢雷雨，則風喉雷鳴，震撼山谷，此響彼應，
如山崩地裂，令人心驚膽戰。崖壁上密密麻麻鐫滿了摩崖題刻，中有“上天梯”
三個斗大金字，傳説為漢武帝御筆。
LONG);
	set("exits",
	([
          "eastdown" : __DIR__"shijie2",
          "northup" : __DIR__"shijie3",
	]));
        set("outdoors","kongdong");
	set("objects", ([
		__DIR__"npc/youke" : 2,
		]) );
        setup();
        //place_program(ROOM);
}
