// inwell.c
inherit ROOM;

void create()
{
        set("short", "井底");
        set("long", @LONG
這是一口極深的水井。浮在水面往上看，只覺得圓圓的天空是那麼
可愛。井壁(wall)上滿是滑溜溜的青苔。一個□轆的頭上, 吊著一根長
繩(string)，繩端系著一個木桶(mutong)。木桶懸在空中，離你很近，
只差一點就可以夠得著。
LONG
        );
        set("outdoors", "huanggong");
        set("resource/water", 1);
        set("coor/x", -180);
        set("coor/y", 5250);
        set("coor/z", -20);
        setup();
}

void init()
{
        add_action("do_climb", "climb");
        add_action("do_climb", "pa");
        add_action("do_jump", "tiao");
        add_action("do_jump", "jump");
        add_action("do_reach", "reach");
}

int do_reach(string arg)
{
        object me;
        me = this_player();
        if (!arg||arg=="") return 0;
        if( arg=="mutong") {
                message_vision(
                "\n$N試著去抓木桶，但總是差一點夠著，要能跳高一點就好了。\n", me);
        }
        if( arg=="string") {
                message_vision(
                "\n$N試著去抓長繩，但總是差一點夠著，要能跳高一點就好了。\n", me);
        }
return 1;
}

int do_climb(string arg)
{
        object me;
        me = this_player();
        if (!arg && (arg != "wall")&& (arg != "string"))
                return notify_fail("你要爬什麼？\n");
        if( arg=="wall" ) {
                message_vision(
                "\n$N接連試了好幾次，可是井壁太滑，怎麼也上不去。\n", me);
        }
        if( arg=="string" )
        {
                if( query_temp("hasjump", me) )
                {
                        delete_temp("hasjump", me);
                        message_vision(
        "$N順著長繩往上爬，終于爬出了深井，重見天日。\n", me);
                        message_vision(
        "$N仰天長笑道：這世上就沒有我做不成的事啊，哈哈哈。。。\n", me);
                        me->move(__DIR__"houyuan");
                }
                else return notify_fail("\n你夠不著。\n");
        }
        return 1;
}

int do_jump(string arg)
{
        object me;
        me = this_player();
        if (!arg && (arg != "mutong") && (arg != "string"))
                return notify_fail("你要往那兒跳？\n");
        message_vision(
                "\n$N深吸一口氣，向上猛的一跳，一下抓住了木桶。\n", me);
        message_vision(
                "只聽骨碌碌一陣亂響，木桶一下拉到了頭。$N高興極了。\n", me);
        set_temp("hasjump", 1, me);
        return 1;
}