// Code of ShenZhou
// Ryu, 5/10/97

inherit ROOM;

void create()
{
        set("short", "冰洞");
        set("long", @LONG
進到冰洞裡面，那洞頂上緊緊垂掛著冰錐(icicle)，長短不齊，
粗細不一；洞底下冰樹叢生，千姿萬態。穿行洞內，好似進了光怪陸
離的神話世界。洞頂有個窟窿似乎可以爬出去(out)。
LONG );

        set("item_desc",([
                "icicle" : "這些冰錐長短不一，在火折照耀下散發出晶瑩的光澤，你很想彈(flick)幾根下來玩玩。\n",
        ]));

        set("exits", ([
                "east" : "/d/xingxiu/icecave1",
        ]));
        set("bing_can", 3);
        set("cost", 2);
        set("icicle", 100);

        setup();
}
void init()
{
        add_action("do_flick", "flick");
        add_action("do_flick", "tan");
        add_action("do_out", "out");
}
int do_flick(string arg)
{
        object me;
        me = this_player();

        if( !arg || arg=="" )
                return 0;

        if (me->query_busy())
                return notify_fail("你正忙著呢。\n");

        if (query("icicle") < 1)
                return notify_fail("這裡的冰錐你都夠不著了。\n");

        if( query("jing", me)<30 || query("jingli", me)<30 )
                return notify_fail("你的精神不能集中。\n");

        if( arg=="icicle")
        {
        me->receive_damage("jing", 15);        
        me->receive_damage("qi", 15);
        addn("icicle", -1);
        message_vision("$N輕輕地用手指彈斷了一根冰錐。\n", me);
        if (random(me->query_skill("feixing-shu", 1)) > 30){
        me->improve_skill("feixing-shu",query("int", me));
        message_vision("$N彈飛出去的冰錐撞斷了另一根冰錐，乒乒乓乓亂響。\n", me);
        tell_object(me, "你似乎領悟了一層暗器的技能。\n");
        if (me->query_skill("feixing-shu", 1) > 100)
        me->receive_damage("jing", 15);
        if (me->query_skill("feixing-shu", 1) > 150)
        me->receive_damage("jing", 15);
        }
        if (query("icicle") < 1){
        remove_call_out("renew_up");
        call_out("renew_up", 300+random(200));
        }
        return 1;
        }
}
void renew_up()
{
        set("icicle", 100);
}
int do_out(string arg)
{
        object me;
        me = this_player();

        message_vision("$N攀上洞壁從窟窿裡爬了出去，\n", me);
        me->move("/d/xingxiu/shanluan");
        message("vision", me->name() + "水淋淋的不知從什麼地方爬了上來。\n",
                    environment(me), ({me}) );
        return 1;
}