// This program is a part of NT MudLIB

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "衙門正廳");
        set("long", @LONG
這裡是江陵知府的衙門大堂。兩邊是“肅靜”、“回避”的牌子，
十幾個衙役齊刷刷地站著，手拿水火棍，虎視耽耽的。知府大人坐在案
台後，冷冷地逼視著你。大堂上方掛一巨匾，上寫“明鏡高懸”四個大
字。一個師爺打扮的人站在知府大人身後，不時俯身對大人耳語幾句。
LONG );
        set("region", "jingzhou");
        set("exits", ([
                "north" : __DIR__"jzyamen",
                "south" : __DIR__"houyuan",
                "east"  : __DIR__"laofang",
        ]));
        set("objects", ([
                "/d/city/npc/yayi" : 4,
                __DIR__"npc/shiye" : 1,
                __DIR__"npc/ling"  : 1,
        ]));

        create_door("east", "鐵門", "west", DOOR_CLOSED);
        set("coor/x", -7110);
	set("coor/y", -2070);
	set("coor/z", 0);
	setup();
        //replace_program(ROOM);
}

int valid_leave(object me, string dir)
{
        if (! wizardp(me) && objectp(present("ling tuisi", environment(me))) &&
                dir == "east")
                return notify_fail("凌翰林擋住了你：請勿入牢房。\n");
        return ::valid_leave(me, dir);
}