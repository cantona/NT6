// Room: /d/shaolin/gulou7.c
// Date: YZC 96/01/19

inherit ROOM;

string look_drum();
string look_out();

void create()
{
        set("short", "鼓樓七層");
        set("long", @LONG
這裡就是鼓樓之頂。直入眼簾的便是一只大鼓。大鼓鼓身通紅，
似由白楊木箍成。兩頭包以水牛皮，用一匝大銅釘釘在鼓身邊緣。鼓
心有一圈白漬，看來是因為多次擊打形成的。整個大鼓放在一個一人
高的架子上，架子底層擱著兩根大鼓槌。盡管山風吹人欲倒，誰都禁
不住想擊一下鼓(drum)試試。往外看，有個很大的漢白玉窗台(out)，
上面足可站一個人。
LONG );
        set("exits", ([
                "down" : __DIR__"gulou6",
        ]));
        set("item_desc",([
                "drum"                :        (: look_drum :),
                "out"                :        (: look_out :),
        ]));
        set("objects",([
                CLASS_D("shaolin") + "/qing-wen" : 1,
        ]));
        setup();
}

void init()
{
        add_action("do_hit", "hit");
        add_action("do_out", "out");
}

int do_hit(string arg)
{
        object me;

        me = this_player();
        if (! arg || ( arg != "drum" ))
                return notify_fail("你要敲什麼？\n");

        me->receive_damage("qi", 30);

        if( random(query("dex", me))<5 )
        {
                message_vision("$N一不小心敲到自己頭上了。\n", me);
                me->unconcious();
        } else
        {
                mapping mine;

                mine = me->query_entire_dbase();
                message_vision("$N敲了一下大鼓，『咚……』聲音傳遍整個寺廟。\n", me);
                write("鼓聲如迅雷般在你耳邊炸響，你頭腦中一片糊塗，\n"
                        "全身搖搖欲墜，勉力支撐著不倒在地上。心中一個\n"
                        "聲音告訴你，得趕快離開這裡，不然就沒命了。\n");
                if (random(2) == 0)
                {
                        if (mine["potential"] - mine["learned_points"] < 100)
                                addn("potential", 1, me);
                } else
                {
                        if (mine["potential"] >= mine["learned_points"])
                                addn("potential", -1, me);
                }
        }
        return 1;
}

int do_out(string arg)
{
        object me;

        int i, ging_cost, qi_cost;

        me = this_player();
        me->start_busy(5);
        i = (int)me->query_skill("dodge") + random(5);

        ging_cost=600/query("int", me);
        qi_cost=500/query("int", me);

        if( (query("jing", me)<ging_cost) || 
            (query("qi", me)<qi_cost) )
                i = 0;

        message_vision("$N爬上窗台，一個縱身，跳了下去。\n", me);
        me->move(__DIR__"gulou");
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

string look_drum()
{
        return
        "※※※※※※※※※※※※※※※※※※※※※※\n"
        "※※※※　　　　　　　　　　　　　　※※※※\n"
        "※※※※　　　　　佛語有曰：　　　　※※※※\n"
        "※※※※　　　　　　　　　　　　　　※※※※\n"
        "※※※※　『求一次菩薩，擊一次鼓』　※※※※\n"
        "※※※※　　　　　　　　　　　　　　※※※※\n"
        "※※※※　　（ｈｉｔ　ｄｒｕｍ）　　※※※※\n"
        "※※※※　　　　　　　　　　　　　　※※※※\n"
        "※※※※※※※※※※※※※※※※※※※※※※\n";
}

string look_out()
{
        return  "這裡是鼓樓頂層的窗台，從這裡可以遙望整個少室山脈，\n"
"以及高聳入雲的嵩山。浮世煙塵，盡在眼底。據說在此地\n"
"可以與天界諸佛直接交流，對禪修大有益處。\n";
}
