// Room: /d/huangshan/jiulong.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "九龍瀑");
        set("long", @LONG
九龍瀑源於天都，玉屏諸峯，然後在香爐，羅漢兩峯的懸崖九折而
下，一折一潭，九瀑九潭，因此得名。每逢大雨之後，瀑水從天而降，
流而復折，折而復聚，懸於千仞絕壁，宛如九龍飛舞，姿態曼妙。
LONG
        );
        set("exits", ([ 
                "westdown" : __DIR__"baizhang",
                "eastdown" : __DIR__"kuzhu",
        ]));
        set("item_desc", ([
                "絕壁": "這裏雖然陡峭無比，但石壁突兀不平，你可以試着從這（cliff）爬（climb）上去。\n"
        ]) );
        set("outdoors", "huangshan");
        set("coor/x", -585);
        set("coor/y", -1080);
        set("coor/z", -10);
        setup();
}
void init()
{
        add_action("do_climb","climb");
}
int do_climb(string arg)
{
        object me = this_player();

        if(!arg || arg != "cliff") return 0;
        message_vision("$N抓住絕壁上突出的石塊，向上小心爬去！\n", me);
        me->start_busy(2);
        call_out("arrive",2,me);
        return 1;
}
int arrive(object me)
{
        if(me)
        {
                message_vision("$N一失手，從上面掉了下來！\n",me);
                me->receive_wound("qi",100);
        }
        return 1;
}