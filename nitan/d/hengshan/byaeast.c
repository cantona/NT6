// Last Modified by Sir on May. 22 2001
//Room: byaeast.c 白雲庵東廊

inherit ROOM;
void create()
{
        set("short","白雲庵東廊");
        set("long",@LONG
這裡是恆山白雲庵東廊。走廊往北通往練武房，東邊通往藏經閣。
LONG);
        set("outdoors", "hengshan");
        set("exits",([ /* sizeof() == 1 */
                "north" : __DIR__"liangong", 
                "east"  : __DIR__"cangjingge", 
                "west"  : __DIR__"baiyunan",
        ]));
        set("objects", ([
                __DIR__"npc/qin" : 1,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", 50);
        set("coor/y", 3210);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}