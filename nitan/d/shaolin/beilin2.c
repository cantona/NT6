#include <ansi.h> 
inherit ROOM;

int do_move(string arg);
string look_tower();
string look_stone();

void create()
{
        set("short", "西碑林");
        set("long", @LONG
這裏是一大片碑林。雖説是碑林，主要是少林歷代高僧的佛塔靈
藏 (tower)。一座座佛塔約有二三人高，有漢白玉的，花岡石的，精
工雕鑿，薄弧的浮雕面上飛禽走獸，佛謁禪詩，諸佛眾生，可謂無所
不包。底座有須彌座的，也有蓮花座的，各態紛呈。佛塔間疏疏落落
的立着幾塊碑(stone)，有的題着幾句詩。
LONG );
        set("exits", ([
                "east" : __DIR__"taijie",
        ]));
        set("outdoors", "shaolin");
        set("item_desc",([
                "tower"        : (: look_tower :),
                "stone"        : (: look_stone :),
        ]));
        set("no_clean_up", 0);
        setup();
}

void init()
{
        add_action("do_move", "move");
}

int do_move(string arg)
{
        int n;
        object me = this_player();

        if (arg != "stone" || arg == "")
                return 0;

        if (query("exits/down"))
                return notify_fail("佛塔已經被移開了，你還移它作甚？\n");

        message_vision(HIY "$N" HIY "走到佛塔前，運力雙掌，使勁推動"
                       "佛塔，打算將它移開。\n" NOR, me);

        if( query("max_neili", me)<1000 )
        {
               message_vision(HIR "結果哪知$N" HIR "內力不濟，連吃奶"
                              "的勁都用上了，佛塔還是紋絲不動。\n" NOR, me);
               set("neili", 0, me);
               return 1;
        }

        message_vision(HIY "佛塔忽然發出軋軋的聲音，向一側緩緩移開，"
                        "向下露出一個黑洞洞的入口。\n" NOR, me);

        set("exits/down", __DIR__"beilin3");
        set("neili", 0, me);
        set("break", 1);
        return 1;
}

string look_tower()
{
        return WHT
        "\n"
        "    ※※※※※※※※※※※※※※※※※※※※※※\n"
        "    ※※※※　　　　　　　　　　　　　　※※※※\n"
        "    ※※※※　一切世界佛，悉發菩提心，　※※※※\n"
        "    ※※※※　　　　　　　　　　　　　　※※※※\n"
        "    ※※※※　上報四重恩，下濟三途苦，　※※※※\n"
        "    ※※※※　　　　　　　　　　　　　　※※※※\n"
        "    ※※※※　無邊大法力，渡劫升極樂，　※※※※\n"
        "    ※※※※　　　　　　　　　　　　　　※※※※\n"
        "    ※※※※　願以此功德，莊嚴佛淨土。　※※※※\n"
        "    ※※※※　　　　　　　　　　　　　　※※※※\n"
        "    ※※※※※※※※※※※※※※※※※※※※※※\n" NOR;
}

string look_stone()
{
        return WHT
        "\n"
        "    ※※※※※※※※※※※※※※※※※※※※※※\n"
        "    ※※※※※※※※※※※※※※※※※※※※※※\n"
        "    ※※※※　　　　　　　　　　　　　　※※※※\n"
        "    ※※※※　清晨入古寺，初日照高林。　※※※※\n"
        "    ※※※※　　　　　　　　　　　　　　※※※※\n"
        "    ※※※※　曲徑通幽處，禪房花木深。　※※※※\n"
        "    ※※※※　　　　　　　　　　　　　　※※※※\n"
        "    ※※※※　山光悦鳥性，潭影空人心。　※※※※\n"
        "    ※※※※　　　　　　　　　　　　　　※※※※\n"
        "    ※※※※　萬籟此俱寂，惟聞鍾磐音。　※※※※\n"
        "    ※※※※　　　　　　　　　　　　　　※※※※\n"
        "    ※※※※※※※※※※※※※※※※※※※※※※\n"
        "    ※※※※※※※※※※※※※※※※※※※※※※\n" NOR;
}
