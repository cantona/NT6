// Room: /d/shaolin/zhonglou7.c
// Date: YZC 96/01/19

inherit ROOM;

string look_bell();
string look_out();

void create()
{
        set("short", "鐘樓七層");
        set("long", @LONG
這裏就是鐘樓之頂。直入眼簾的便是那口大鐘和一根懸掛空中的
巨杵。細看大鐘，整整有兩丈來高，直徑也有丈許。鐘身似由青銅澆
鑄，上面滿是密密麻麻的印文古篆，估計重逾數千斤。巨杵粗可合抱，
丈把來長，一頭裹以厚皮，正對着鐘腰。儘管山風吹人慾倒，誰都禁
不住想撞一下鍾(bell)試試。往外看，有個很大的漢白玉窗台(out)，
上面足可站一個人。
LONG );
        set("exits", ([
                "down" : __DIR__"zhonglou6",
        ]));
        set("item_desc",([
                "bell"                :        (: look_bell :),
                "out"                :        (: look_out :),
        ]));
        set("objects",([
                CLASS_D("shaolin") + "/qing-xiao" : 1,
        ]));
        setup();
}

void init()
{
        add_action("do_knock", "knock");
        add_action("do_out", "out");
}

int do_knock(string arg)
{
        object me;
        mapping mine;

        me = this_player();
        if ( !arg || ( arg != "bell" ) ) return notify_fail("你要敲什麼？\n");

        addn("qi", -20, me);


        mine = me->query_entire_dbase();
        message_vision("$N敲了一下大鐘，『咣……』聲音傳遍整個寺廟。\n", me);
        write("鐘聲如迅雷般在你耳邊炸響，你頭腦中一片糊塗，\n"
                "全身搖搖欲墜，勉力支撐着不倒在地上。心中一個\n"
                "聲音告訴你，得趕快離開這裏，不然就沒命了。\n");

        if( random(2) == 0)addn("combat_exp", 1, me);
        else addn("combat_exp", -2, me);
        return 1;
}

int do_out(string arg)
{
        object me;
        int i, ging_cost, qi_cost;

        me = this_player();
        i = (int)me->query_skill("dodge") + random(5);

        ging_cost=600/query("dex", me);
        qi_cost=500/query("dex", me);

        if( (query("jing", me)<ging_cost) || 
            (query("qi", me)<qi_cost) )
                i = 0;

        message_vision("$N爬上窗台，一個縱身，跳了下去。\n", me);
        me->move(__DIR__"zhonglou");
        me->start_busy(5);
        message_vision("只聽『砰』地一聲$N從塔頂跳了下來。\n", me);
        if (i < 50)
        {
                set_temp("die_reason", "從塔頂失足掉了下來摔死了", me);
                me->die();
        } else
        if (i < 125)
                me->unconcious();
        else
        {
                message_vision("$N已穩穩地站在地上。\n", me);
                if( i>175 && query("dodge", me)<200 )
                        me->improve_skill("dodge",1+random(query("dex", me)));
                me->receive_damage("jing", ging_cost);
                me->receive_damage("qi", qi_cost);
        }

        return 1;
}

string look_bell()
{
        return
        "※※※※※※※※※※※※※※※※※※※※※※※\n"
        "※※※※　　　　　　　　　　　　　　　※※※※\n"
        "※※※※　　　　　佛語有曰：　　　　　※※※※\n"
        "※※※※　　　　　　　　　　　　　　　※※※※\n"
        "※※※※　『做一天和尚，撞一天鐘』　　※※※※\n"
        "※※※※　　　　　　　　　　　　　　　※※※※\n"
        "※※※※　（ｋｎｏｃｋ　ｂｅｌｌ）　　※※※※\n"
        "※※※※　　　　　　　　　　　　　　　※※※※\n"
        "※※※※※※※※※※※※※※※※※※※※※※※\n";
}

string look_out()
{
        return  "這裏是鐘樓頂層的窗台，從這裏可以遙望整個少室山脈，\n"
"以及高聳入雲的嵩山。浮世煙塵，盡在眼底。據説在此地\n"
"可以與天界諸佛直接交流，對禪修大有益處。\n";
}
