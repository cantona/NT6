// room: mishi.c

#include <ansi.h>
#include <room.h>

inherit ROOM;
int do_press();
int valid_leave();
string look_hua();
string look_liang();

void create()
{
        set("short","密室");
        set("long", @LONG
這是一間黑□□的小房間，牆上的磚頭(zhuan) 已經掉渣子了，房
樑(liang) 也已經朽爛不堪。牆腳處有一個鐵箱子，上面積滿了塵土。
左首處懸掛著一幅畫(hua)，角落處斜放著幾捆幹柴。
LONG );
        set("exits", ([
                "out" : __DIR__"midao",
        ]));
        set("item_desc", ([
                "hua"     : (: look_hua :),
                "liang"   : (: look_liang :),
                "zhuan": "磚頭爛得一塌糊塗。\n",
                //"liang": "房樑是上好的楠木做的，可惜年代太久，已經腐爛得不成樣子了。\n",
        ]) );
        set("objects", ([
                __DIR__"obj/tiexiang" : 1,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", 1820);
        set("coor/y", -6312);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_jump", "jump");
}

string look_hua()
{
        object me = this_player();

        if( query("score", me)<1000 )
                return HIR "\n一幅陳舊的畫卷，畫中乃是達摩老祖，沒有什麼不同。\n" NOR;

        if( query("score", me)<3000 )
                return HIR "\n一幅陳舊的畫卷，畫中達摩老祖左手握個劍訣，慈祥安和。\n" NOR;

        set_temp("marks/辟1", 1, me);
        return HIR "\n一幅陳舊的畫卷，畫中達摩老祖左手握個劍訣，正指向房樑(liang)處。\n" NOR;
}

string look_liang()
{
        object me = this_player();

        if( !query_temp("marks/辟1", me) )
                return "你要看什麼？\n";

        if (query("move"))
                return WHT "一根楠木做的房樑，上面有嶄新的刮痕，似乎不久前才有人動過。\n" NOR;

        set_temp("marks/辟2", 1, me);
        return WHT "一根楠木做的房樑，可惜年代太久，已經腐爛得不成樣子了。\n" NOR;
}

int do_jump(string arg)
{
        object me, ob;
        me = this_player();

        if( !arg || arg=="" )
                return 0;
        if( arg=="liang")
        {
            if( query_temp("marks/跳1", me)){
                if (me->query_dex()<20)
                    write("你試圖跳上房樑，無奈身法不夠敏捷，只好做罷。\n");
                else {
                    write("你縱身躍上了房樑。\n");
                    message("vision",
                             me->name() + "一縱身躍上了房樑。\n",
                             environment(me), ({me}) );
                    set("move", 1);
                    me->move(__DIR__"liang");
                    message("vision",
                             me->name() + "從下面躍了上來。\n",
                             environment(me), ({me}) );
                }
                return 1;
           }

           if( query_temp("marks/辟2", me) )
           {
                if (me->query_dex() < 40)
                        write(HIC "你試圖跳上房樑，無奈身法不夠敏捷，只好做罷。\n" NOR);
                else
                {
                        foreach (ob in deep_inventory(me)) if (ob->is_character())
                        {
                                ob->move(environment(me));
                                message_vision("\n$N將" + ob->name() + "從背上放了下來"
                                               "，躺在地上。\n\n" NOR, me);
                        }

                        message("vision", HIY "只見" + me->name() + HIY "一縱身躍上了房"
                                          "樑。\n" NOR, environment(me), me);
                        set("move", 1);
                        write(HIY "\n你縱身輕輕一躍，跳上了房樑。\n\n" NOR);
                        me->move(__DIR__"liang");
                        message("vision", HIY "只見" + me->name() + HIY "從下面的柴房躍"
                                          "了上來。\n" NOR, environment(me), me);
                }
                return 1;
            }
        }
}

int valid_leave(object me, string dir)
{
        delete_temp("marks/辟1", me);
        delete_temp("marks/辟2", me);
        delete_temp("marks/跳1", me);
        return ::valid_leave(me, dir);
}