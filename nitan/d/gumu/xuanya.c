// Room: /d/gumu/xuanya.c
// Last Modifyed by Winder on Jan. 14 2002

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", HIM"懸崖"NOR);
        set("long", @LONG
此處已是終南山絕路，光禿禿的石壁，下面則是雲霧瀰漫的萬丈深
崖(xuanya)，傳聞中有個古墓弟子因受不了古墓之清苦寡慾，從此處一
躍而下，了卻一生。近懸崖邊有棵摩天大樹(tree)，枝葉極盛，如大傘
一張遮掩住方圓之地。
LONG        );
        set("outdoors","gumu");
        set("exits", ([
                "west" : __DIR__"mumen",
        ]));
        set("item_desc", ([
                "xuanya" : "懸崖下一片雲霧繚繞。跳(tiao)下去恐是有去無回。\n",
                "tree"   : "一棵高大的巨樹，上面留下曾經被人搖晃的痕跡。\n", 
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3220);
        set("coor/y", 40);
        set("coor/z", 90);
        setup();
}

void init()
{
        object room, me = this_player();

        if( random(query("kar", me)) >= 15 )
        {
                if(!( room = find_object(__DIR__"tree")))
                        room = load_object(__DIR__"tree");
                if(!(present("du mang", room))) return;
                message_vision(HIR "突然聞到一股腥臭之氣，大樹上倒懸下一條碗口粗細的三角頭巨蟒，把$N捲走了。\n\n"NOR, me);
                me->move(__DIR__"tree");
                me->start_busy(3);
        }
        else
        {
                add_action("do_tiao", "tiao"); 
                add_action("do_yao", "yao");
                add_action("do_climb", "climb");
                add_action("do_climb", "pa");
        }
}

int do_tiao(string arg)
{ 
        object me = this_player();

        if ( arg == "xuanya")
        {
                if( query_temp("mark/jump", me)<2 )
                {
                        write("人生苦短，且古墓神功絕世，你再考慮一下吧。\n");
                        addn_temp("mark/jump", 1, me);
                        return 1;
                }
                message_vision(HIR "$N縱身跳下懸崖，悲呼一聲，兄弟姐妹們，來生再見，回聲不絕於耳。\n"NOR, me);
                delete_temp("mark/jump", me);
                set_temp("last_damage_from", "跳崖自殺而", me);
                me->unconcious();
                me->die();
                return 1;
        }
        return notify_fail("你要跳到哪裏？\n");
}

int do_yao(string arg)
{
        mapping fam;
        object me = this_player();
        int c_exp, c_skill;

        c_skill=(int)me->query_skill("parry", 1);
        c_exp=query("combat_exp", me);

        if( !(fam=query("family", me)) || fam["family_name"] != "古墓派" )
                return notify_fail("搖什麼搖，沒見過樹啊？\n");
        if (me->is_busy() || me->is_fighting())
                return notify_fail("你正忙着哪！\n");
        if( query("qi", me)<30 )
                return notify_fail("你累得夠嗆，去稍作歇息吧。\n");
        if (arg == "tree")
        {
                if (c_skill < 50)
                        return notify_fail("你使出渾身的勁力，但是大樹卻紋絲不動。\n");
                if (c_skill > 100)
                        return notify_fail("你使勁地搖晃大樹，發現大樹快被你搖斷了。\n");
                write("你使勁地搖晃着大樹，震的大樹微微晃動。\n");
                me->receive_damage("qi", 10 + random(20));
                if (c_skill*c_skill*c_skill/10 < c_exp )
                        me->improve_skill("parry",random(query("int", me)));
                return 1;
        }
        return notify_fail("你要搖什麼？\n");
}

int do_climb(string arg)
{ 
        object me = this_player(); 

        if (arg == "tree")
        {
                message_vision(YEL"$N騰身往大樹上爬去。\n"NOR, me);
                if (me->query_skill("dodge", 1) < 30)
                {
                        message_vision(HIR"結果$N從樹上一個筋斗掉下來。\n"NOR, me);
                        me->receive_wound("qi", random(5) + 5);
                        return 1;
                }
                message_vision(HIY"$N很快消失在濃蔭密葉中。\n"NOR, me);
                me->move(__DIR__"tree");
                return 1;
        }
        write("你想往哪爬？\n");
}
