#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "馬莊");
        set("long",
"這裡一座頗為豪華的大宅院出現在你的眼前，兩頭高大的
石獅子鎮住了大門兩側，朱漆大門足足有三寸厚。門上掛著兩
個燈籠，寫著「" HIW "馬莊" NOR "」二字。馬大元乃丐幫副幫主，以其家傳
絕技三十二勢鎖喉擒拿手震爍江湖，在武林中威名遠揚。
");
        set("outdoors", "yangzhou");
        set("region", "yangzhou");
        set("exits", ([
                "north" : __DIR__"dongdajie3",
                "south" : __DIR__"ma_dayuan",
        ]));
        set("objects", ([
                "/d/gaibang/npc/1dai" : 1 + random(2),
                "/d/gaibang/npc/2dai" : 1 + random(2),
        ]));
	set("coor/x", 30);
	set("coor/y", -10);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}