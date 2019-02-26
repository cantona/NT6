// Room: /d/suzhou/szyunhe.c
// Last Modified by winder on Mar. 8 2001

#include <ansi.h>;
string look_sign();
int do_go(string);
inherit RIVER;

mapping *sign=({
        ([        "name" : "北京",
                "id"   : "bj",
                "file" : "/d/beijing/matou",
                "value": 200,
                "time" : 20
        ]),
        ([        "name" : "揚州",
                "id"   : "yz",
                "file" : "/d/city/matou",
                "value": 100,
                "time" : 10
        ]),
        ([        "name" : "杭州",
                "id"   : "hz",
                "file" : "/d/hangzhou/matou",
                "value": 100,
                "time" : 10
        ])
});

void create()
{
        set("short", "運河");
        set("long", @long
這裏是古老的運河的橋頭邊，只見這條運河(river) 蜿蜒流淌，從
蘇州城裏穿過。運河的兩岸都是蘇州的尋常百姓家，在蘇州的城裏出門
最好的交通工具就是船了。只見進處有一位老船伕，見你走過來，起身
向你迎來，手上掛着一個竹牌(sign)。
long);
        set("exits",([
                "southeast" : __DIR__"xidajie1",
        ]));
        set("item_desc", ([
                "river" : "近岸處有一葉小舟，也許喊(yell)一聲船家就能聽見。\n",
                "sign" : (: look_sign :)
        ]));
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
  set("yell_about", "船家");             // yell 船家
  set("river_type", "湖");               // 江面上傳來回響
  set("need_dodge",300);                 // 需要多少輕功
  set("come_msg_out",   "一葉扁舟緩緩地駛了過來，採蓮女將一塊踏腳板搭上堤岸，以便乘客上下。\n");
  set("busy_msg",       "只聽得河面不遠處隱隱傳來：“別急嘛，這兒正忙着吶……”\n");
  set("wait_msg",       "岸邊一隻渡船上的採蓮女説道：正等着你呢，上來吧。\n");
  set("leave_msg_out",  "採蓮女把踏腳板收了起來，竹篙一點，扁舟向運河駛去。\n");
  set("leave_msg_in",   "採蓮女把踏腳板收起來，説了一聲“坐穩嘍”，竹篙一點，扁舟向運河駛去。\n");
  set("come_msg_in",    "採蓮女説“到啦，上岸吧”，隨即把一塊踏腳板搭上堤岸。\n");
  set("item_desc/river", HIC "\n只見近岸處有一葉小舟，也許大聲喊("
                         HIY "yell" HIC ")一聲船家(" HIY "boat" HIC
                        ")就\n能聽見。倘若你自負輕功絕佳,也可直接"
                        "渡水(" HIY "cross" HIC ")踏水而過。\n" NOR);
  set("boat_short", "渡船");    
  set("boat_desc",  @LONG
一葉小舟，最多也就能載七、八個人。一名十多歲的採蓮小姑娘手
持長竹篙，正在船尾輕輕地盪舟。
LONG );
                                   // 渡船上的描述
  set("to",         __DIR__"huzhongdao");  // 船的終點 /*   必選   */
	set("coor/x", 1090);
	set("coor/y", -1050);
	set("coor/z", 0);
	setup();
}

void init()
{
        ::init();
        add_action("do_go", "qu");
}

void do_move(object ob, int i)
{
//        ob->enable_player();
        delete_temp("noliving", ob);
        delete_temp("block_msg/all", ob);
        tell_object(ob, "終點站到了。\n");
        ob->move(sign[i]["file"]);
        tell_room(environment(ob), ob->name() + "從船上走了下來。\n", ({ob}));
}

int do_go(string arg)
{
        object ob=this_player();
        int i=sizeof(sign);

        if (!arg) return 0;
        if (ob->is_busy() || ob->is_fighting())
                return notify_fail("你正忙着呢！\n");
        while(i--)
        {
                if (arg == sign[i]["id"])
                {
                        switch (MONEY_D->player_pay(ob, sign[i]["value"]))
                        {
                                case 0:
                                        return notify_fail("窮光蛋，一邊呆着去！\n");
                                case 2:
                                        return notify_fail("有零錢嗎？\n");
                        }
                        message_vision("$N登上了去" + sign[i]["name"] + "的船。\n", ob);
//                        ob->disable_player("<旅途中>");
                        set_temp("noliving/journey", 1, ob);
                        set_temp("block_msg/all", 1, ob);
                        ob->move(__DIR__"onroad");
                        call_out("do_move", sign[i]["time"], ob, i);
                        return 1;
                }
        }
        return notify_fail("你要去哪裏？\n");
}
string look_sign()
{
        string str="由此去(qu)到下列碼頭：\n";
        int i=sizeof(sign);

        while (i--)
        {
                str += sign[i]["name"];
                str += "(" + sign[i]["id"] + ") ";
                str += MONEY_D->price_str(sign[i]["value"]) + "\n";
        }

        return str;
}
