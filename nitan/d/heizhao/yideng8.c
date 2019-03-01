//Cracked by Kafei
// yideng quest room 8

inherit ROOM;

void create()
{
        set("short", "山樑");
        set("long", @LONG
山路就到了盡頭，前面是條寬約尺許的石樑，橫架在兩座山峰之
間，雲霧籠罩，望不見盡處。石樑凹凸不平，又加終年在雲霧之中，
石上溜滑異常。前面不遠處的石樑突然斷開了一段空缺(gap)。
LONG );
        set("exits", ([
                        "down":__DIR__"yideng7",
        ]));

        set("item_desc",([
                "gap" : "一段一丈來長的空缺。迎面山風凜烈，腳下白雲飄飄，如果摔下去 ... ...\n",
                ]));
        
        set("invalid_startroom", 1);
        set("outdoors", "taoyuan");
        set("no_magic", 1);
        set("no_clean_up", 0);
        set("coor/x", -38000);
        set("coor/y", -80010);
        set("coor/z", 500);
        setup();
}

void init()
{
        add_action("do_jump", "jump");
}

int do_jump(string arg)
{
        object me = this_player();
        if ( !arg || arg != "gap" )
                return notify_fail( "什麼？\n");

        message_vision("$N縱身往空缺對面跳去。\n", me);
        if ( me->query_skill("dodge",1) <= 80) {
                message_vision("$N空中感到一陣濁氣上湧，差了三寸沒能跳到對面，發出一陣\n", me);
                message_vision("慘嚎，從空中直墜了下去。\n", me);
                me->receive_wound("qi",query("max_qi", me)+100);
        }
        if ( me->query_skill("dodge",1) > 80 ) {
                me->move(__DIR__"yideng9");
                message("vision", me->name() + "縱身由對面跳了過來。\n",environment(me), ({me}) );
        }
        return 1;
} 