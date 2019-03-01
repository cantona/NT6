#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short", "地底");
        set("long", @LONG 
這裡按地勢而言，早已深入地底，乃是大雪山的山腹之中了。
四周土地潮濕，充滿了一股濃濃的泥土味。牆上依然插著幾支火
把，照得四周亮堂堂的。一個腰懸利劍，神情警惕的劍士，正守
在一扇巨大的石門(men)旁。
LONG);
        set("no_clean_up", 0);

        set("exits", ([
                "up" : __DIR__"laolang",
        ]));
        set("objects", ([ 
                __DIR__"npc/shi" : 1,
        ])); 
        set("item_desc", ([
                    "men" : WHT "一扇厚厚的石門，怕有千斤之重。看樣子很難推(push)開。\n" NOR
        ]) );

        setup(); 
}

void init()
{
        add_action("do_push", "push");
}

int do_push(string arg)
{
            object me = this_player();

            message_vision(HIY "只見$N" HIY "氣沉丹田，凝勁于腰，大喝一"
                       "聲，運勁向石門推去。\n" NOR, me);

            if( query("max_neili", me)<500 )
            {
                       message_vision(HIR "可是$N" HIR "累了個半死，石門卻"
                               "紋絲不動。\n" NOR, me);
                       return 1;
            }
            message_vision(HIC "頓時只聽“喀喀喀”機關樞紐運做之聲不絕，"
                       "石門竟緩緩開了。\n" NOR, me);
            set("exits/enter", __DIR__"dilao");

            remove_call_out("close");
            call_out("close", 5, this_object());

            return 1;
}

void close_out()
{
            if (query("exits/enter")) delete("exits/enter");
}

void close(object room)
{
            message("vision", HIW "只聽裡面有人大喝一聲：“小王八蛋，你不進來，就給爺爺滾吧！”\n"
                          "話音剛落，一陣勁風擊到，石門被砰地一下關了。\n" NOR, room);
            delete("exits/enter", room);
}