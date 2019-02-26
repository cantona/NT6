#include <ansi.h>
inherit ROOM;

void close_andao();
string look_xiang();
int do_move(string arg);

void create()
{
        set("short","南巖宮");
        set("long", @LONG
這裏是就是武當山南巖宮。此宮半卧懸崖之下。殿內三清坐像 (
xiang)金光閃閃，氣宇軒昂。殿內天井處芳草迷徑，百卉爭妍。有幾
個裝束醒目的武當三代弟子從這匆匆走過。南面高台擺有真武劍陣，
劍氣逼人而來。
LONG );
        set("exits", ([
                  "out"    : __DIR__"shizhu",
                  "southup": __DIR__"gaotai",
              ]));
              set("item_desc",([
                  "三清坐像" : (: look_xiang :),
                  "xiang"    : (: look_xiang :),
              ]));
              set("no_clean_up", 0);
        set("coor/x", -360);
        set("coor/y", -330);
        set("coor/z", 100);
        setup();
}

int valid_leave(object ob, string dir)
{
        mapping myfam;

        ob = this_player();
        myfam=query("family", ob);

        if( query("combat_exp", ob)<10000 && 
           (dir == "southup"))
                    return notify_fail(HIY "外面的真武劍陣威力太大，你被"
                                   "內力鼓盪，不能上去。\n");

        if ((! myfam || (myfam["family_name"] != "武當派")) &&
           (dir == "southup"))
                    return notify_fail(HIY "外面的真武劍陣威力太大，你被"
                                   "內力鼓盪，退了回來。\n");
        return 1;
}

void init()
{
        add_action("do_move", "move");
}

string look_xiang()
{
        return YEL "三清坐像純銅打就，鍍以純金，光照滿殿。只是好像三"
               "個坐像擺得並不很整齊。\n" NOR;
}

int do_move(string arg)
{
        object room, ob;

        ob = this_player();

        if (! arg || arg != "xiang" )
                return notify_fail("你要移動什麼？\n");

        message_sort(HIY "\n$N" HIY "走到三清坐像背後，用力使勁推移老"
                     "君像，慢慢的推着，坐像終於推了。像下露出一個大"
                     "洞，幾排石階往下伸去，從這裏分明通向一個暗道。"
                     "\n\n" NOR, ob);
        set("exits/down", __DIR__"nanyan0");

        if (room = find_object(__DIR__"nanyan0"))
        {
                set("exits/up", __FILE__, room);
                   message("vision", HIY "\n天花板忽然發出軋軋的聲音，"
                        "露出一個向上的樓梯。\n" NOR, room );
        }
        remove_call_out("close_andao");
        call_out("close_andao", 3);
        return 1;
}

void close_andao()
{
            object room;
        int i;

        if (! query("exits/down")) return;
                    message("vision", HIY "\n只聽乒地一聲響，老君像自動"
                        "移回原處。\n" NOR, this_object());

            if (room = find_object(__DIR__"nanyan0"))
            {
                message("vision", HIY "\n只聽乒地一聲響，向上的洞口"
                        "自動嚴嚴實實地關了起來。\n" NOR, room);
            }
            delete("exits/down");
}
