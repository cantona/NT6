#include <room.h>
#include <ansi.h>
inherit ROOM;

int do_look(string arg);

void create()
{
    set("short", HIY"擂台"NOR);
        set("long", @LONG
這是一個四方的大擂台，擂台北面掛著一張厚厚的布簾子，你感
覺到一股濃厚的殺氣從布簾後散發出來，彌漫在空氣裡，直鑽入你內
心。
LONG );

    set("no_beg",1);
    set("no_steal",1);
    set("biwu_room",1);

    set("objects",([
    ]));

    set("no_clean_up", 0);
    setup();
}

void init()
{
    add_action("do_get","get");
    add_action("do_put","put");
    add_action("do_drop","drop");
    add_action("do_summon","summon");
}

int do_get()
{
    object me;
    me = this_player();
    if (wizardp(me)) return 0;

    tell_object(me,"在這裡你想幹什麼？\n");
    return 1;
}

int do_drop()
{
    object me;
    me = this_player();
    if (wizardp(me)) return 0;

    tell_object(me,"在這裡你想幹什麼？\n");
    return 1;
}

int do_put()
{
    object me;
    me = this_player();
    if (wizardp(me)) return 0;

    tell_object(me,"在這裡你想幹什麼？\n");
    return 1;
}

int do_summon()
{
    object me;
    me = this_player();
    if (wizardp(me)) return 0;

    tell_object(me,"在這裡你想幹什麼？\n");
    return 1;
}
