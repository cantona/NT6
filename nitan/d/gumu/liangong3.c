// Room: /d/gumu/liangong3.c
// Last Modifyed by Winder on Jan. 14 2002

#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
        set("short", HIR"練功房"NOR);
        set("long", @LONG
裏面又是一室，卻和先一間處處對稱，而又處處相反，乃是北窄南
寬，西圓東角，室頂也是刻滿了無數符號。此處乃是古墓派祖師林朝英
的武功之祕。
LONG        );      
        set("no_clean_up", 0);
        set("coor/x", -3190);
        set("coor/y", -30);
        set("coor/z", 90);
        setup();
}

void init()
{
        add_action("do_xiulian", "xiulian");
        add_action("do_tui", "tui");
        add_action("do_tui", "push");
}

int do_xiulian(string arg)
{
        mapping fam;
        object me = this_player();
        int c_exp, c_skill;

        if ( !arg ) 
                return notify_fail("你要參照哪裏來修煉？\n");
        c_exp=query("combat_exp", me);
        if( !(fam=query("family", me)) || fam["family_name"] != "古墓派" )
                return notify_fail("你不是古墓傳人，如何能領悟古墓武功？\n");
        if (me->is_busy() || me->is_fighting())
                return notify_fail("你正忙着哪！\n");
        if( query("jing", me)<20 )
                return notify_fail("你精力不能集中，去稍作歇息吧。\n");
        if ((int)me->query_skill("literate", 1) < 30)
                return notify_fail("你丫鬥字不識一籮筐，領悟個啥？\n");
        if (arg == "top")
        {
                if ((int)me->query_skill("sword", 1) < 20)
                        return notify_fail("你基本劍法太差，無法研習玉女劍法。\n"); 
                if (me->query_skill("yunv-jian", 1) >= 1)
                        return notify_fail("你已經學會玉女劍法，自己好好練吧。\n");      
                write("你仰視室頂的圖紋，心中揣摩玉女劍法的精妙之處。\n");
                me->receive_damage("jing", 5);
                me->improve_skill("yunv-jian", 2);
                return 1;
        }
        if (arg == "southwall")
        {
                write("你掄掌劈向南方石壁，蓬一聲被震退數步，手臂一陣痠麻。\n");
                c_skill=(int)me->query_skill("strike", 1);
                if (c_skill < 50)
                        return notify_fail("你看了半天只覺莫測高深，什麼也沒有學會。\n");
                if (c_skill > 100)
                        return notify_fail("你掌力雄渾，不該再死練蠻力了。\n");
                me->receive_damage("jing", 5 + random(15));
                if (c_skill*c_skill*c_skill/10<c_exp)
                        me->improve_skill("strike",random(query("int", me)));
                return 1;
        }
        if (arg == "northwall")
        {
                write("你揮拳直擊北壁，石粉四濺，你也被自己的猛勁震退數步。\n");
                c_skill=(int)me->query_skill("unarmed", 1);
                if (c_skill < 50)
                        return notify_fail("你看了半天只覺莫測高深，什麼也沒有學會。\n");
                if (c_skill > 100)
                        return notify_fail("你拳力已剛猛無比，卻無甚招數。\n");
                me->receive_damage("jing",5 + random(15));
                if (c_skill*c_skill*c_skill/10<c_exp)
                        me->improve_skill("unarmed",random(query("int", me)));
                return 1;
        }
        if (arg == "eastwall")
        {
                write("你繞東面石壁踏着劍步，用心揣摩壁上劍法精髓。\n");
                c_skill=(int)me->query_skill("sword", 1);
                if (c_skill < 50)
                        return notify_fail("你看了半天只覺莫測高深，什麼也沒有學會。\n");
                if (c_skill > 100)
                        return notify_fail("你對石壁上所述劍法已全然掌握，無須再費力了。\n");
                me->receive_damage("jing", 5 + random(15));
                if (c_skill*c_skill*c_skill/10<c_exp)
                        me->improve_skill("sword",random(query("int", me)));
                return 1;
        }
        if (arg == "westwall")
        {
                write("你虛拈手指，面對西面石壁，細心操練暗器的收發手勢。\n");
                c_skill=(int)me->query_skill("throwing", 1);
                if (c_skill < 50)
                        return notify_fail("你看了半天只覺莫測高深，什麼也沒有學會。\n");
                if (c_skill > 100)
                        return notify_fail("你暗器收發隨心，再不能提高於此。\n");
                me->receive_damage("jing", 5 + random(15));
                if (c_skill*c_skill*c_skill/10<c_exp)
                        me->improve_skill("throwing",random(query("int", me)));
                return 1;
        }
        return notify_fail("你無法參照那裏來修煉。\n");
}

int do_tui(string arg)
{        
        object me=this_player();

        if (me->is_busy() || me->is_fighting())
                return notify_fail("你正忙着哪！\n");
        if ( arg == "westwall")
        {
                message_vision(YEL "$N伸手到半圓的弧底推了幾下，一塊大石緩緩移開，現出一扇洞門。\n"NOR,me);
                set("exits/out", __DIR__"liangong2");
                me->receive_damage("qi", 30);
                remove_call_out("close");
                call_out("close", 5, this_object());    
                return 1;
        }
        return notify_fail("你要推什麼？\n");
}

void close(object room)
{
        message("vision",HIY"大石慢慢退回了原位，又擋住了出口。\n"NOR, room);
        delete("exits/out", room);
}
