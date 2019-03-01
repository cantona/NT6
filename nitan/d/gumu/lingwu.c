// Room: /d/gumu/lingwu.c
// Last Modifyed by Winder on Jan. 14 2002

#include <ansi.h>

inherit ROOM;
void create()
{
        set("short",HIC"領悟室"NOR);
        set("long", @LONG
此地供各弟子打坐靜修之用。地上僅有幾個蒲團，幾對少男少女正
在閉目領悟。東面石壁上有一方凸起，刻著不少文字(wall), 西面地上
有一方凹陷，刻著些古怪的圖形(ground), 頂上有一些美女圖形(top)。
LONG        );
        set("exits", ([
                "north" : __DIR__"mudao23",
        ]));
        set("item_desc", ([
                "top"    : HIC "\t玉女遨遊于空，逍遙穿梭，身形百變。\n"NOR,
                "wall"   : HIC "\t內功心法...古墓子弟可研習于此。\n"NOR,
                "ground" : HIC "\t閃轉騰挪之術...古墓子弟可研習于此。\n"NOR,
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3180);
        set("coor/y", -30);
        set("coor/z", 90);
        setup();
}

void init()
{
        add_action("do_lingwu", "lingwu");
        add_action("do_lingwu", "think");
}

int do_lingwu(string arg)
{
        mapping fam;
        object me=this_player();
        int c_exp, c_skill;

        c_skill=(int)me->query_skill("dodge", 1);
        c_exp=query("combat_exp", me);
        if ( !arg ) 
                return notify_fail("你要參照哪裡來領悟？\n");
        c_exp=query("combat_exp", me);
        if( !(fam=query("family", me)) || fam["family_name"] != "古墓派" )
                return notify_fail("你不是古墓傳人，如何能領悟古墓武功？\n");
        if (me->is_busy() || me->is_fighting())
                return notify_fail("你正忙著哪！\n");
        if ((int)me->query_skill("literate", 1) < 30)
                return notify_fail("你丫鬥字不識一籮筐，領悟個啥？\n");
        if (arg == "top")
        {
                message_vision(HIY"$N開始仰視頂上美女圖形。\n"NOR, me);
                if( query("jing", me)<25 )
                        return notify_fail("你一陣暈旋，想是用腦過度，該休息一會了。\n");
                me->receive_damage("jing", 25);
                if ((int)me->query_skill("force", 1) < 30)
                {
                        message_vision(HIM "$N看著美女圖形開始氣血上湧，目光直勾勾，竟出現猥褻之意。\n"NOR, me);
                        write(HIR"你定力不夠，這樣的圖畫還是少看為妙。\n"NOR);
                        message_vision(HIR"$N忽然搖晃起來，驀地噴出口鮮血。\n"NOR, me);
                        me->receive_wound("qi", 10);
                        me->unconcious();
                        return 1;
                }
                if ((int)me->query_skill("unarmed", 1) < 30 )
                        return notify_fail("你雖能平心審視這些裸女圖，卻不解其中奧妙所在。\n");
                if (me->query_skill("meinv-quan", 1) >= 1)
                        return notify_fail("你已學會了美女拳，要更上一步，只能靠自己勤加練習。\n");
                write(HIY"你靜心研習頂上的美女身形，領悟到古墓派美女拳法的精髓所在，頓時茅塞頓開。\n"NOR);
                me->improve_skill("meinv-quan", 10);
                write(HIR "恭喜，這位" + RANK_D->query_respect(me)+"，你已經學會美女拳法了。\n"NOR);
                return 1;
        }
        if (arg == "wall")
        {
                c_skill=(int)me->query_skill("force", 1);
                if (c_skill > 50)
                        return notify_fail("石壁所述盡在你心，你無法再悟出什麼新東西。\n");
                if( query("jing", me)<20 )
                        return notify_fail("你覺得好累，好想睡覺。\n");
                me->receive_damage("jing", 5 + random(15));
                write("你靜心研習石壁的秘籍，對內功心法有些領悟。\n");
                if (c_skill*c_skill*c_skill/10<c_exp)
                        me->improve_skill("force",random(query("int", me)));
                return 1;
        }
        if ( arg =="ground" )
        {
                c_skill=(int)me->query_skill("parry", 1);
                if (c_skill > 50)
                        return notify_fail("你對著地上研習一會，只覺所述早已盡藏心胸。\n");
                if( query("jing", me)<20 )
                        return notify_fail("你一陣暈旋，想是用腦過度，該休息一會了。\n");
                me->receive_damage("jing",5 + random(15));
                write("你模仿地上的圖形上跳下縱，修習招架閃躲。\n");
                if (c_skill*c_skill*c_skill/10<c_exp)
                        me->improve_skill("parry",random(query("int", me)));
                return 1;
        }
        return notify_fail("你無法參照那裡來領悟。\n");
}
