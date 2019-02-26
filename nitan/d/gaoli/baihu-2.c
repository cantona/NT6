// /d/gaoli/baihuuedajie3
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "朝陽大街");
        set("long", @LONG
你走在一條寬闊的石板大街上，西面就快到高麗皇宮了。都可以看
見皇宮的圍牆，東面是高麗的東門朝陽門，北面是一家小吃鋪，店雖不
大，可東西卻不少，南面是一間小茶館，不少人在裏面聽書喝茶。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "west" : __DIR__"baihu-1",
                "east" : __DIR__"baihumen",
                "north":__DIR__"xiaochipu",
                "south":__DIR__"chaguan",    
        ]));
set("objects",([
 __DIR__"npc/dipi":1,
 ]));
       setup();
        replace_program(ROOM);
}        
