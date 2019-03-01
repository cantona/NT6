#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "石柱");
        set("long", @LONG
這是南巖宮前的一根石柱，雕成龍形，自峭壁上橫出，猶如飛龍
在天。龍首刻一香爐，在此上香稱為「上龍頭香」，是香客的最大心
願。石柱僅粗如屋樑，旁無扶欄，前有白雲繚繞，下有萬丈深淵，稍
一失足，即屍骨無存。
LONG );
        set("exits", ([
                "northup" : __DIR__"nanyanfeng",
                "enter" : __DIR__"nanyangong",
        ]));
        set("outdoors", "wudang");
        set("no_clean_up", 0);
        set("coor/x", -360);
        set("coor/y", -330);
        set("coor/z", 100);
        setup();
}

void init()
{
        add_action("do_mianbi", "think");
}

int do_mianbi(string arg)
{
        object ob = this_player();

        if (! arg)
        {
                message_vision("$N面對著石柱趺坐靜思良久，白"
                               "忙一場，一無所獲。\n",ob);
                return 1;
        }

        if ((int)ob->query_skill("literate", 1) < 100)
        {
                message_vision("$N面對著石柱上滿面蝌蚪文，沒"
                               "一個字認識。\n",ob);
                return 1;
        }

        if ((int)ob->query_skill("taoism", 1) < 100)
        {
                message_vision("$N對石柱上每一個字都認識，就"
                               "是不知道說的是什麼。\n",ob);
                return 1;
        }

        if (arg == "taiji-jian" ||
            arg == "taiji-quan" ||
            arg == "tiyunzong")
        {
                if ((int)ob->query_skill(arg, 1) < 100)
                {
                        message_vision("$N的" + to_chinese(arg) +
                                       "顯然太低，無法領悟石柱內容。\n",ob);
                        return 1;
                }

                if ((int)ob->query_skill(arg, 1) > 180)
                {
                        message_vision("$N的" + to_chinese(arg) +
                                       "已經沒必要讀石柱內容了。\n", ob);
                        return 1;
                }

                if (! ob->can_improve_skill(arg))
                {
                        message_vision("$N的實戰經驗不足，無法"
                                       "領悟石柱內容。\n", ob);
                        return 1;
                }

                if( query("jing", ob)<150 )
                {
                        message_vision("$N太累了，現在無法領"
                                       "悟石柱內容。\n", ob);
                        return 1;
                }
                ob->improve_skill(arg,1+random(query("int", ob)));
                addn("jing", -100-random(50), ob);
                message_vision(HIY "$N" HIY "面對著石柱趺坐靜思，過得良"
                               "久，似有所悟。\n" NOR, ob);
                write(HIC "你對「" + to_chinese(arg) + HIC "」有了新的理"
                      "解。\n" NOR);
                return 1;
        } else 

        message_vision(HIY "$N" HIY "面對著石柱趺坐靜思良久，但似乎沒什"
                       "麼啟發。\n" NOR, ob);
        return 1;
}