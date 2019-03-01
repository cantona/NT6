// Room: /d/gumu/lianggong1.c
// Last Modifyed by Winder on Jan. 14 2002

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIC"石室"NOR);
        set("long", @LONG
這是一間密閉的石室，室中點著燈火，石室奇小，僅容一人周轉，
牆上刻著一些圖譜，供古墓弟子修煉入門輕功時參看。
LONG        );

        set("exits", ([
                "north" : __DIR__"mudao08",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3200);
        set("coor/y", -10);
        set("coor/z", 90);
        setup();
}

void init()
{
        add_action("do_cankan", "cankan");
        add_action("do_cankan", "watch");
}

int do_cankan(string arg)
{
        object me=this_player();
        int c_exp, c_skill;

        c_skill=(int)me->query_skill("dodge", 1);
        c_exp=query("combat_exp", me);
        if( !arg ) return notify_fail("你東張西望地亂看什麼？\n");
        if( arg != "picture" || arg != "tu" )
                return notify_fail("這裡沒有你想看的東西。\n");
        if( query("jing", me)<30 )
                return notify_fail("你覺得太累了，不如歇會吧？\n");
        me->receive_damage("jing", random(10));
        if( random((int)c_skill/10) + 1 < 2)
        {
                message_vision("$N認真地看牆上的圖譜，可是光線實在太暗，眼睛生痛，好象也沒看到什麼特別的東西。\n", me);
                return 1;
        }
        message_vision("$N正在仔細察看牆上的圖譜。\n", me);
        if ((random(10)>3) && c_skill*c_skill*c_skill/10<c_exp && c_skill<101)
        {
                me->improve_skill("dodge",random(query("int", me)));
                tell_object(me,"你的基本輕功進步了！\n");
        }
        return 1;
}