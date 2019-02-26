// Code of ShenZhou
// Ryu, 5/10/97

inherit ROOM;
string look_cliff();
void create()
{
        set("short", "天池");
        set("long", @LONG
靈山上白雪皚皚，冰川縱橫，鋪銀蓋玉。大大小小的冰面湖、冰
洞，廣為分佈。高懸在冰峯峽谷裏的天池，恰似一面巨大的銀鏡，溢
彩流光，閃爍耀眼。迷人的山色湖光，山風習習，空氣清涼如水。 山
前的峭壁(cliff)上刻有幾行字跡，入石三分。
LONG );
        set("exits", ([
                "westup" : "/d/xingxiu/shanluan",
                "southdown" : "/d/xingxiu/guozi",
        ]));
        set("item_desc",([
                "cliff"         :       (: look_cliff :),
        ]));
        set("cost", 7);
        set("bing_can", 7);
        set("resource/water",1);
        set("outdoors", "tianshan");

        setup();
}
string look_cliff()
{
        return
        "\n"
        "              冰    雪    四    三\n\n"
        "              池    嶺    壁    峯\n\n"
        "              耀    界    橫    並\n\n"
        "      長      日    天    陳    起\n"
        "      春                          \n"
        "      真      俗    人    繞    插\n"
        "      人                          \n"
        "      丘      難    不    澗    雲\n"
        "      處                          \n"
        "      機      觀    到    盤    寒\n";
}
void init()
{
        add_action("do_climb", "climb");
        add_action("do_climb", "pa");
}
int do_climb(string arg)
{
        object me;
        me = this_player();

        if( !arg || arg=="" )
                return notify_fail("你要跟哪兒爬？\n");

        if (me->query_busy())
                return notify_fail("你正忙着呢。\n");

        if( arg=="cliff")
        {
        message_vision("$N手腳並用順着峭壁往峯頂上爬去。\n", me);
        me->start_busy(5);

        if (random(me->query_skill("dodge")) < 50){
        remove_call_out("drop_down");
        call_out("drop_down", 5, me);
        return 1;
        }
        
        message("vision", me->name()+"一會兒便消失在雲氣裏了。\n", environment(me), ({me}) );
        remove_call_out("climb_up");
        call_out("climb_up", 5, me);
        return 1;
        }
}
void drop_down(object me)
{
        tell_object(me, "突然你一失手，從峭壁上掉了下來，屁股重重地摔在地上。\n");
        message("vision", me->name() + "突然一失手，從峭壁上掉了小來，屁股重重地摔在地上。\n",
                             environment(me), ({me}) );
        me->receive_damage("qi", 50);
        me->receive_wound("qi",  50);
}
void climb_up(object me)
{
        tell_object(me, "你深吸一口氣縱身躍起，幾個起落間，已竄上了峯頂。\n");
        addn("jingli", -50, me);
        me->move("/d/xingxiu/lingshan");
        message("vision", me->name() + "氣喘吁吁地從下面爬了上來。\n",
                             environment(me), ({me}) );
}
