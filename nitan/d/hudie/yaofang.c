// 藥房 yaofang.c
 
#include <ansi.h>
inherit ROOM;

void create() 
{ 
        set("short", "藥房");
        set("long", @LONG
這裡是胡青牛的藥房，靠牆邊都是一排一排的藥櫃，每個藥櫃上
都有一張白紙，上面寫滿了對藥材的注釋。屋的正中央，有一個小爐
子，一個小童正蹲在爐子旁，拿著一把扇子，不停地煽著火，整個屋
子一股中藥的氣息。南北聽起來都很安靜。
LONG );

        set("exits", ([
            "north" : __DIR__"xfang3",
            "west" : __DIR__"maowu",
            "south" : __DIR__"xfang1",
        ]));

        set("objects",([
            __DIR__"npc/xtong2" : 1,
        ]));

        setup();
}