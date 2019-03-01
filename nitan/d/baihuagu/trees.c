// Room: /d/baihuagu/trees.c
// Last Modified by Winder on Mar. 5 2001

inherit ROOM;
void create()
{
        set("short", "樹林");
        set("long", @LONG
叢林中一片黑暗，你瞪大眼睛，只發現到處都是樹。你迷路了！
LONG);
        set("exits", ([ 
                "north" : __DIR__"tree",  
        ]));
        set("no_clean_up", 0);
        set("coor/x", -450);
        set("coor/y", -400);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}