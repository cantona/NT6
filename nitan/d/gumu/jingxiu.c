// Room: /d/gumu/jingxiu.c
// Last Modifyed by Winder on Jan. 14 2002

#include <ansi.h>;
inherit ROOM;
void create()
{
        set("short",HIC"石室"NOR);
        set("long", @LONG
此地供各弟子打坐靜修之用。地上僅有幾個蒲團，幾個古墓弟子正
在閉目領悟。正面的石牆( qiang)上刻著不少文字, 仔細一看，原來都
抄錄著四書五經等古籍，用來給古墓弟子提高修養。
LONG        );

        set("exits", ([
                "south" : __DIR__"mudao21",
        ]));
        set("item_desc", ([
                "qiang" : "牆上寫滿了各種古籍文字。\n",
        ]));
        set("coor/x", -3190);
        set("coor/y", 10);
        set("coor/z", 90);
        setup();
}

void init()
{ 
        add_action("do_think", "think");
        add_action("do_think", "lingwu");
}

int do_think(string arg)
{
        mapping fam;
        object me = this_player();

        if ( !living(me) ) return 0;
        if (me->is_busy() || me->is_fighting())
                return notify_fail("你正忙著哪！\n");
        if( !(fam=query("family", me)) || fam["family_name"] != "古墓派" )
                return notify_fail("你不是古墓傳人，如何能領悟古墓武功？\n");
        if (arg == "qiang" || arg == "wall")
        {
                if( query("jing", me)<20 )
                        return notify_fail("你覺得好累,好想睡覺。\n");
                if ( me->query_skill("literate", 1) > 140)
                        return notify_fail("你已經完全讀懂了牆上的文字。\n");
                if ( me->query_skill("literate", 1) > 10 &&
                        me->query_skill("literate",1)>query("combat_exp", me)/1000 )
                        return notify_fail("你的經驗不夠，不能讀懂牆上的文字。\n");
                if( query("potential", me)-query("learned_points", me)<1 )
                        return notify_fail("你沒潛能了，不能再繼續修習了。\n");
                addn("learned_points", 1, me);
                me->receive_damage("jing", 5 + random(10));
                me->improve_skill("literate", random(me->query_int()));
                write("你對著石壁，仿佛有所領悟。\n");
                return 1;
        }
        return notify_fail("你要領悟什麼？\n");
}
