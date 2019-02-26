// Room: /d/songshan/eastting.c
// Last Modified by Winder on Jul. 15 2001

inherit ROOM;
void create()
{
        set("short", "東庭");
        set("long", @LONG
這裏是一個小小庭院，院子裏常有嵩山弟子結伴往來。庭院四周矮
牆下長着的小灌木裏，偶爾冒出幾星白色小花。鵝卵細石鋪就的小路在
灌木叢和長草間穿過。
LONG );
        set("outdoors", "songshan");
        set("exits", ([
                "east"  : __DIR__"jianlu",
                "west"  : __DIR__"eastpath1",
                "north" : __DIR__"eastpath2",
                "south" : __DIR__"shuzhai",
        ]));
        set("objects", ([
                __DIR__"npc/dizi": random(2),
        ]));
        set("coor/x", 0);
        set("coor/y", 900);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}