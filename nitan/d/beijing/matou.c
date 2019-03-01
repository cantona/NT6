// Room: /d/beijing/matou.c
// Last Modified by winder on Mar. 8 2001

#include <ansi.h>;
string look_sign();
int do_go(string);
inherit ROOM;

mapping *sign=({
        ([        "name" : "揚州",
                "id"   : "yz",
                "file" : "/d/city/matou",
                "value": 100,
                "time" : 10
        ]),
        ([        "name" : "蘇州",
                "id"   : "sz",
                "file" : "/d/suzhou/szyunhe",
                "value": 200,
                "time" : 20
        ]),
        ([        "name" : "杭州",
                "id"   : "hz",
                "file" : "/d/hangzhou/matou",
                "value": 300,
                "time" : 30
        ])
});

void create()
{
        set("short", "通州碼頭");
        set("long", @long
這裡是古老的運河的起始點，運河由此南下，橫穿華北大平原，溝
通海河、黃河、淮河、長江和錢塘江五大水系，縱橫中國南北，是帝都
命脈。河裡來來往往的，都是江南運來的糧米貨物。帆影蔽日，十分繁
華。你走進碼頭，就看見一位老船夫，起身向你迎來，手上掛著一個木
牌(sign)。
long);
        set("exits",([
                "north" : __DIR__"chaoyangmen",
        ]));
        set("item_desc", ([
                "sign" : (: look_sign :)
        ]));
        set("outdoors", "beijing");
        set("no_clean_up", 0);
	set("coor/x", -2800);
	set("coor/y", 7600);
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