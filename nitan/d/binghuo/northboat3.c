// Room: /binghuo/northboat3.c
// Date: Oct.28 1999 by Winder
#include <ansi.h>;

inherit ROOM;

void create()
{
        set("short", "破帆船");
        set("long", @LONG
帆船這時只剩後帆吃風，那船歪斜傾側，在海面上狂舞亂跳，後
桅向左橫斜，帆邊已碰到水面。船上水手全給海浪卷走了！周圍漆黑
一團，船身格格格的響個不停，隨時都能碎裂。
LONG );
        set("no_sleep_room",1);
        set("outdoors", "binghuo");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
