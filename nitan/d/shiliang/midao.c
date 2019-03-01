// Feb. 6, 1999 by Winder
inherit ROOM;
void create()
{
        set("short", "山洞底");
        set("long", @LONG
這是一個極深的山洞。四處死氣沉沉的，你急得快哭了起
來。洞壁(wall)上滿是滑溜溜的青苔。很奇怪的是這裡有根長
繩(string)，繩端系著一個大石頭(stone)。
LONG
        );
        set("coor/x", 1600);
        set("coor/y", -1980);
        set("coor/z", 0);
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
        if( arg=="stone")
        {
message_vision("$N試著去抓石頭，但總是差一點夠著，要能跳高一點就好了。\n",me);
        }
        if( arg=="string")
        {
message_vision("$N試著去抓長繩，但總是差一點夠著，要能跳高一點就好了。\n",me);
        }
        return 1;
}
int do_climb(string arg)
{
        object me;
        me = this_player();
        if (!arg && (arg != "wall")&& (arg != "string"))
                return notify_fail("你要爬什麼？\n");
        if( arg=="wall" )
        {
message_vision("$N接連試了好幾次，可是洞壁實在是太滑，怎麼也上不去。\n", me);
        }
        if( arg=="string" )
        {
                if( query_temp("hasjump", me) )
                {
                        delete_temp("hasjump", me);
message_vision("$N順著長繩往上爬，終于爬出了山洞。\n", me);
message_vision("$N揉了揉眼睛，仿佛還不適應這裡的光線，好象有個人在面前。\n",me);
                        me->move(__DIR__"jinshedong");
                }
        else return notify_fail("\n你夠不著。\n");
        } 
        return 1;
}
int do_jump(string arg)
{
        object me;
        me = this_player();
        if (!arg && (arg != "stone") && (arg != "string"))
                return notify_fail("你要往那兒跳？\n");
        message_vision("$N深吸一口氣，向上猛的一跳，一下抓住了石頭。\n", me);
        message_vision("只聽骨碌碌一陣亂響，石頭一下拉到了頭。$N高興極了。\n", me);
        set_temp("hasjump", 1, me);
        return 1;
}