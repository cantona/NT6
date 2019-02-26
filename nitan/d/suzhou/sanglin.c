// Room: /d/suzhou/sanglin.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "桑林");
        set("long", @LONG
這裏是一片桑林。江南絲綢甲於天下，蘇繡更是天下絕品。看着滿
眼的綠綠桑樹，想象着春蠶吐絲的情節和亮麗如彩虹的絲緞，你倒有點
想摘下幾片眼前再平常不過的桑葉，好好看看。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("ye_count", 5);
        set("exits", ([
                "southwest" : __DIR__"road1",
        ]));
	set("coor/x", 1120);
	set("coor/y", -1000);
	set("coor/z", 0);
	setup();
}
void init()
{
        add_action("do_zhai","zhai");
}

int do_zhai(string arg)
{
        object ye, me = this_player();

        if( !arg || arg=="" )
        {
                message_vision("你想摘什麼？\n", me);
                return 1;
        }
        if( arg=="ye"||arg=="sang ye" )
        {
                if(query("ye_count") > 0)
                {
                        message_vision("$N從桑樹上摘下一片綠油油的桑葉。\n",me);
                        ye = new("/clone/medicine/vegetable/sangye");
                        ye->move(me);
                        addn("ye_count",-1);
                        return 1;
                }
                else
                {
                        message_vision("桑葉還太嫩了，$N等一會再摘吧。\n",me);
                        return 1;             
                }
        }
        return 0;
}