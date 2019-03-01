// Room: /d/mobei/downxuanya.c
// Last Modified by winder on May. 25 2001

inherit ROOM;

void create()
{
        set("short", "懸崖下");
        set("long", @LONG
陡峭的山崖壁立，漠北苦寒的風沙侵蝕，山崖更是光滑險峻。幾柱
矮樹平平從山石中伸出，鐵灰色的山石癒行癒高，直與天空中的白雲相
接。兩頭白色的大雕圍繞著山崖邊的一株鬆樹鳴叫。
LONG);
        set("outdoors","mobei");
        set("objects", ([ /* sizeof() == 1 */
                __DIR__"npc/baidiao" : 2,
        ]));
        set("exits", ([ /* sizeof() == 1 */
                "south" : __DIR__"xiaolu",
        ]));
        set("coor/x", -250);
        set("coor/y", 5210);
        set("coor/z", 10);
        setup();
}

void init()
{
        add_action("do_climb", "climb");
        add_action("do_climb", "pa");
}
int do_climb(string arg)
{
        object me;
        me = this_player();

        if( !arg || arg=="" ) return 0;
        if( arg=="ya")
        {
                message("vision", me->name() + "吭吃吭吃向懸崖上爬去。\n", environment(me), ({me}) );
                me->move(__DIR__"yading");
                message("vision", me->name() + "從懸崖下爬了上來，粘了一身泥。\n", environment(me), me );
                return 1;
        }
}
