#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short", "密室");
        set("long", @LONG
這裡是一座不大的石室，房間落滿灰塵，好象有多年沒人打掃似
的。室內只有一床一案，一縷陽光從洞頂的巖縫中射入，照射在室壁
上，你發現石壁(wall)上似乎有一些花紋。室內光線明亮。牆邊有一
個青石床，一個寬大的石案上擺著一個石匣(xia)。
LONG
        );
        set("sleep_room", 1);
        set("no_fight", 1);

        set("exits", ([
                "eastup" : __DIR__"shixi",
        ]));
        set("item_desc",([
                "xia": WHT "\n一只石匣，好象是和石案連在一起的，不"
                       "知道敢不敢打開看看。\n " NOR,
                "wall": WHT "\n牆上刻著很多蠅頭小字，還附著一些圖畫，"
                       "似乎是一門極上乘的武學。\n " NOR,
        ]));

        set("mishi_book", 1);
        setup();
}

void init()
{
        add_action("do_think", "think");
        add_action("do_open", "open");
}

int do_open(string arg)
{
        object me, ob;
        me = this_player();

        if( !arg || arg != "xia")
                return 0;

        if( query("mishi_book") == 1/* && query("can_learn/千蛛萬毒手", me)*/ )
        {
                message_vision(HIC "$P" HIC "打開石匣，發現內有一束絹"
                               "冊，立忙取了出來。\n" NOR, me);
                addn("mishi_book", -1);
                ob = new(__DIR__"obj/qianzhumiji");
                ob->move(me);
        } else
                return notify_fail("\n你打開石匣，但見裡面空空如也。\n");

        return 1;
}
int do_think(string arg)
{
        object ob;
        int c_exp, c_skill;
        ob = this_player();

        if (arg != "wall") return 0;

        c_skill = (int)ob->query_skill("qianzhu-wandushou", 1);
        c_exp=query("combat_exp", ob);

/*
        if( !query("can_learn/千蛛萬毒手", ob) )
        {
                message_vision(HIR "$N" HIR "仔細端詳了石壁半天，還是無法看懂上面的內容。\n" NOR, ob);
                return 1; 
        }
*/

        if( query("character", ob) == "光明磊落" )
        {
                tell_object(ob, HIY "你心中暗想：我為人光明磊落，豈能學習這種害人武功？\n" NOR);
                return 1; 
        }

        if( query("character", ob) == "狡黠多變" )
        {
                tell_object(ob, HIY "你心中暗想：哼，這種武功雖然厲害，但對自身損害極大，學來何用？\n" NOR);
                return 1; 
        }

        if( query("jing", ob)<50 )
        {
                message_vision(HIR "$N" HIR "現在太累了，無法研讀石壁的內容。\n" NOR, ob);
                return 1; 
        }

        if (c_skill > 119)
        {
                message_vision(WHT "$N" WHT "覺得石壁內容太膚淺了。\n" NOR, ob);
                return 1; 
        }

        if ((c_skill * c_skill * c_skill / 10) > c_exp)
        {
                message_vision(HIR "$N" HIR "的實戰經驗不足，無法領悟石壁內容。\n" NOR, ob);
                return 1; 
        }

        message_vision(HIY "$N" HIY "面對著石壁靜思良久，對千蛛萬毒手似有所悟。\n" NOR, ob);
        ob->improve_skill("qianzhu-wandushou",random(30*query("int", ob)));
        ob->receive_damage("jing", 15);
        return 1;
}