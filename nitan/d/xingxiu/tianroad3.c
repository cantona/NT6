// room: /d/xingxiu/tianroad3.c
// Last Modified by winder on Feb. 28 2001

inherit ROOM;

void init();
int do_jump(string arg);

void create()
{
        set("short", "天山山路");
        set("long", @LONG
這裏是天山東麓，山風從山上吹來，你冷得瑟瑟發抖。路邊是一片
草原。西面一條深澗(valley)擋住了上山的路。
LONG );
        set("exits", ([
                "northup"  : __DIR__"xxroad4",
                "eastdown" : __DIR__"xxh",
        ]));
        set("item_desc", ([
                "valley" : "深澗有三丈多寬，不知道能不能跳(jump)過去。\n"
        ]) );
        set("objects", ([
                CLASS_D("xingxiu")+"/azi" : 1
        ]));
//        set("no_clean_up", 0);
        set("outdoors", "xingxiu");
        set("coor/x", -51000);
        set("coor/y", 20100);
        set("coor/z", 20);
        setup();
}

void init()
{
        add_action("do_jump", "jump");
}

int do_jump(string arg)
{
        object me;
        me = this_player();

        if( !arg || arg=="" ) return 0;
        if( arg=="valley" )
        {
/*                if (present("horse", me)) { */
                if( query_temp("marks/騎", me) )
                {
                        message("vision", me->name() + "猛地一提韁繩，胯下的伊犁馬一聲長嘶越過了深澗。\n", environment(me), ({me}) );
                        write("你猛地一提韁繩，胯下的伊犁馬一聲長嘶越過了深澗。\n");
                        me->move("/d/xingxiu/tianroad4");
                        message("vision","只聽得唏溜溜一聲馬嘶，" + me->name() + "從深澗的那端縱馬跳了過來，好似當年馬跳\n檀溪的玄德公。\n", environment(me), ({me}) );
                        write( "只聽得唏溜溜一聲馬嘶，你從深澗的那端縱馬跳了過來，真是酷呆了。\n你樂得從馬背上滾了下來。\n");
                        set_temp("marks/騎", 0, me);
                        return 1;
                }
                else
                {
                        write("你試了試，發現深澗的那邊比這邊高，非是人力可以跳上去的。\n");
                        return 1;
                }
        }
}
/*
int do_jump(string arg)
{
        object me;
        me = this_player();

        if (! arg || arg != "valley")
                return notify_fail("你要往哪跳？\n");

        message_vision(HIY "\n$N" HIY "豫了一下，鼓氣勇氣，朝着對面的山崖跳了過"
                       "去。\n\n" NOR, me);

        if ((int)me->query_skill("dodge", 1) < 100 )
        {
                me->move(__DIR__"shanjiao");
                me->receive_wound("qi", 300);
                me->unconcious();
                message("vision", HIR "\n突然聽得「砰」的一聲，只見一個人從上面"
                                  "的山峯上墜了下來，真是壯觀。\n" NOR,
                                  environment(me), ({me}));
        } else
        {
                me->move(__DIR__"tianroad4");
                message("vision", HIY "\n只見" + me->name() + HIY "從對面的山崖"
                                  "上跳了過來。\n" NOR, environment(me), ({me}));
        }
        return 1;
}

*/