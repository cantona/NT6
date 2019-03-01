//Room: shanhongpb.c 山洪瀑布

#include <ansi.h>

inherit BUILD_ROOM;

string look_hongshui();

void create()
{
        set("short","山洪瀑布");
        set("long", @LONG
這裡是一處峽谷，每年雨季山洪爆發時就形成了一處蔚為壯觀的
瀑布。傳說當年神雕俠楊過就是在這裡練成絕世的玄鐵劍法的。現在
人去谷空，只剩下空寥的山谷和奔騰的洪水(hongshui)。看來倒是個
隱居的好去處。
LONG );
        set("outdoors", "huashan");
        set("item_desc", ([
                "hongshui" : (: look_hongshui :),
                "stone"    : NOR + WHT "一塊天然的巨石，被洪水無情地沖蝕著。\n" NOR,
        ]));
        set("exits",([ /* sizeof() == 1 */
                "southwest"     : __DIR__"shaluo",
        ]));
        setup();
}

void init()
{
        add_action("do_cross", "cross");
        add_action("do_jump", "jump");
}

string look_hongshui()
{
        return @DESC
這是一股奔騰不息的洪水，水中隱隱有個東西在發光，但你定睛
仔細一看，發現那只不過是水面反射的日光罷了。順著洪水俯視，
只見瀑布底矗立著一塊天然的巨石（stone）， 這個瀑布似乎可
以穿(cross)過去。
DESC ;
}

int do_jump(string arg)
{
        object me = this_player();

        if (me->is_busy() || me->is_fighting())
              return notify_fail("你忙完了再說吧！\n");
    
        if (! arg || arg != "stone")
              return notify_fail("你要往哪兒跳？\n");
 
        if (me->query_skill("dodge") < 240)
              return notify_fail("你看了看，覺得自己輕功修為有限，不敢貿然跳下。\n");

        message_vision(HIG "$N" HIG "縱身跳下瀑布 ……\n", me);

        me->move(__DIR__"stone");

        return 1;
}

int do_cross()
{
        object me;       
        object cloth;

        me = this_player();
        if (me->query_dex() / 2 + random(me->query_dex()) < 22)
        {
                message_vision("$N望了望奔騰的瀑布，突然一躍，試圖穿過"
                               "瀑布，結果“撲通”一下摔進了水中。\n", me);

                cloth=query_temp("armor/cloth", me);
                if (cloth && cloth->washed(120 + random(120)))
                        tell_object(me, "你身上的" + cloth->name() + "濕透了！\n");
                return 1;
        }

        message_vision("$N望了望奔騰的瀑布，突然一躍，穿過了"
                       "瀑布。\n", me);
        me->move(__DIR__"shandong");
        return 1;
}