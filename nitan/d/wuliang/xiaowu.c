// Room: /wuliang/xiaowu.c
// Date: Oct.18 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "囚室");
        set("long", @LONG
這是一間木頭小屋。房中陳設簡陋，窗上鐵條縱列，看來竟然便
是無量劍關人的所在，只是開間寬敞，倒無侷促之感，
LONG );
        set("no_sleep_room",1);
        set("exits", ([
                "west"       : __DIR__"huayuan",
        ]));
        set("coor/x", -70970);
        set("coor/y", -79890);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}