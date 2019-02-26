#include <room.h>
#include <ansi.h>
inherit ROOM;

int do_look(string arg);

void create()
{
    set("short", HIY"休息室"NOR);
        set("long", @LONG
這是一個簡單但是色彩柔和的小房間，四周隨意放着一些沙發，
另外中間還有幾張小牀，給打下擂台的挑戰者們時不時給抬到這裏來。
這裏最好請保持安靜。
LONG );

    set("no_fight",1);
    set("no_beg",1);
    set("no_steal",1);
    set("biwu_room",1);

    set("exits", ([
        "east"  : "/d/city/biwu_road",
    ]));

    set("no_clean_up", 0);
	set("coor/x", -70);
	set("coor/y", 10);
	set("coor/z", 0);
	setup();
}

void init()
{
    add_action("do_get","get");
    add_action("do_put","put");
    add_action("do_drop","drop");
}

int do_get()
{
    object me;
    me = this_player();
    if (wizardp(me)) return 0;

    tell_object(me,"在這裏你想幹什麼？\n");
    return 1;
}

int do_drop()
{
    object me;
    me = this_player();
    if (wizardp(me)) return 0;

    tell_object(me,"在這裏你想幹什麼？\n");
    return 1;
}

int do_put()
{
    object me;
    me = this_player();
    if (wizardp(me)) return 0;

    tell_object(me,"在這裏你想幹什麼？\n");
    return 1;
}