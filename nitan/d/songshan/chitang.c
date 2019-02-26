// Room: /d/songshan/chitang.c
// Last Modified by Winder on Jul. 15 2001

inherit ROOM;

void create()
{
        set("short", "池塘");
        set("long", @LONG
你扶着塘邊的石欄杆往南望，可以看到劍池的那口大鐵劍，回身就
是小花園了。嵩嶽絕頂，天風浩蕩，吹皺一池碧水，大略韻味如此。
LONG );
        set("exits", ([
                "north" : __DIR__"huayuan",
        ]));
        set("outdoors", "songshan");
        set("no_clean_up", 0);
        set("coor/x", -20);
        set("coor/y", 910);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}