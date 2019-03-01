//Edited by fandog, 01/31/2000

inherit ROOM;
void create ()
{
        set ("short", "甬道");
        set ("long", @LONG
一條陰暗潮濕的甬道，東邊盡頭是一間牢房，是知府衙門用來關押
朝廷重犯的地方。
LONG);
        set("exits", ([ 
                "east" : __DIR__"laofang",
                "west" : __DIR__"lingtang",
        ]));
  
        set("no_clean_up", 0);
        set("coor/x", -1460);
        set("coor/y", -2029);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}