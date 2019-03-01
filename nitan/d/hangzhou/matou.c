// Room: /d/hangzhou/matou.c
// Last Modified by winder on Mar. 8 2001

#include <ansi.h>;
string look_sign();
int do_go(string);
inherit ROOM;

mapping *sign=({
        ([        "name" : "蘇州",
                "id"   : "sz",
                "file" : "/d/suzhou/szyunhe",
                "value": 100,
                "time" : 10
        ]),
        ([        "name" : "揚州",
                "id"   : "yz",
                "file" : "/d/city/matou",
                "value": 200,
                "time" : 20
        ]),
        ([        "name" : "北京",
                "id"   : "bj",
                "file" : "/d/beijing/matou",
                "value": 300,
                "time" : 30
        ])
});

void create()
{
        set("short", "臨安碼頭");
        set("long", @long
這裡是古老的運河的終點，運河自燕山腳下的帝都南下，橫穿中國
的華北大平原，連綿海河、黃河、淮河、長江和錢塘江五大水系，止于
號稱天堂和魚米之鄉的杭州城。運河中滿是來來往往的檣影，江南的豐
厚的產出經此國家命脈，源源北上。
    你走進碼頭，就看見一位老船夫站在船邊，手上高舉著一個寫滿字
的木牌(sign)。
long);
        set("exits",([
                "southwest" : __DIR__"road9",
        ]));
        set("item_desc", ([
                "sign" : (: look_sign :)
        ]));
        set("outdoors", "xihu");
        set("no_clean_up", 0);
	set("coor/x", 830);
	set("coor/y", -1990);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_go", "qu");
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
                return notify_fail("你正忙著呢！\n");
        while(i--)
        {
                if (arg == sign[i]["id"])
                {
                        switch (MONEY_D->player_pay(ob, sign[i]["value"]))
                        {
                                case 0:
                                        return notify_fail("窮光蛋，一邊呆著去！\n");
                                case 2:
                                        return notify_fail("有零錢嗎？\n");
                        }
                        message_vision("$N登上了去" + sign[i]["name"] + "的船。\n", ob);
//                        ob->disable_player("<旅途中>");
                        set_temp("noliving/journey", 1, ob);
                        set_temp("block_msg/all", 1, ob);
                        ob->move("/d/suzhou/onroad");
                        call_out("do_move", sign[i]["time"], ob, i);
                        return 1;
                }
        }
        return notify_fail("你要去哪裡？\n");
}