#include <room.h>
inherit ROOM;

void create()
{
        set("short", "練武場");
        set("long", @LONG
空闊的場地上舖滿了細細的黃土，正好適合演武。四面有
幾個丐幫的弟子正在練武。練武場的中心豎著幾根木樁，木樁
周圍還挖了若幹個大沙坑。西邊是兵器庫。而右邊有一扇小門。
LONG);
        set("outdoors", "yangzhou");
        set("region", "yangzhou");
        set("exits", ([
                "west"  : __DIR__"ma_bingqi",
                "east"  : __DIR__"ma_xiaojing",
                "north" : __DIR__"ma_zoulang2",
        ]));
        set("objects", ([
                "/d/gaibang/npc/1dai" : 1 + random(2),
                "/d/gaibang/npc/2dai" : 1,
                "/d/gaibang/npc/6dai" : 1,
                "/d/gaibang/npc/7dai" : 1,
        ]));
        create_door("east", "木門", "west", DOOR_CLOSED);
        set("no_clean_up", 0);
	set("coor/x", 30);
	set("coor/y", -70);
	set("coor/z", 0);
	setup();
}