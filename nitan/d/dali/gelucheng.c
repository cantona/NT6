//Room: /d/dali/gelucheng.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","葛魯城");
        set("long",@LONG
此城是烏蠻族屈部的治府，屈部領葛魯、昌州、德昌，面積頗大。
附近多山地叢林，居民多狩獵為生，河谷內低地也多草皮，適合放牧
牛羊。此去北和西皆入深山，東邊平原上另有村鎮。
LONG);
        set("objects", ([
           __DIR__"npc/shanyang": 2,
           __DIR__"npc/muyangren": 1,
        ]));
        set("outdoors", "daliw");
        set("exits",([ /* sizeof() == 1 */
            "northup"    : __DIR__"shanlin",
            "south"      : __DIR__"zhenxiong",
            "east"       : __DIR__"minadian",
        ]));
	set("coor/x", -19210);
	set("coor/y", -6850);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}