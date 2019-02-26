#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "匯英酒樓二樓");
        set("long", @LONG
酒樓裏桌椅潔淨。座中客人衣飾豪奢，十九是富商大賈。這裏可
以俯瞰整個紫禁城的全景。
LONG );
        set("exits", ([
                "down" : "/d/beijing/huiying",
        ]));
        set("objects", ([
                CLASS_D("gaibang") + "/ada" : 1,
                "/d/tulong/yitian/npc/zhaomin2" : 1,
                "/d/tulong/yitian/npc/zhao1" : 1,
                "/d/tulong/yitian/npc/qian2" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2790);
	set("coor/y", 7640);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}