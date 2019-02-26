// /yubifeng/yuanfengding.c
// Last modified by winder 2003.9.2

int do_stamp(string arg);

inherit ROOM;

void create()
{
        set("short", "圓峯頂");
        set("long", @LONG
峯頂積滿了千百年來從未消融的堅冰，歷年新雪，層層疊疊。遠望
四周，羣峯在上，峯谷間寒風貫穿，嘶聲凌厲。峯頂正中，有一個微陷
的小窩。
LONG );
        set("exits", ([
                "northdown" : __DIR__"yuanfeng",
        ]));
        set("objects", ([
                __DIR__"npc/tong1" : 1,
                __DIR__"npc/tong2" : 1,
        ]));
        set("outdoors", "yubifeng");
        set("coor/x", 6100);
        set("coor/y", 5120);
        set("coor/z", 10);
        setup();
}

void init()
{
        add_action("do_stamp","stamp");
        add_action("do_stamp","tread");
        add_action("do_stamp","cai");
        add_action("do_stamp","ta");
}

int do_stamp(string arg)
{
        object me = this_player();
        int n;

        n = me->query_skill("force", 1);

        if ( !arg || (arg != "wo" && arg != "xiaowo"))
        {
                write("你要踩踏什麼呀？\n");
                return 1;
        }
        if( n>100 && query("qi", me)>1000 )
        {
                message_vision("$N深吸了一口氣，看準了方位，一步步走將過去。\n...\n待走到圓峯之頂的窩兒正中，用力踩踏，果然腳下鬆動，身子下落。\n...\n$N早有防備，雙足着地，立即幌亮火摺，撥開冰雪，見前面是條長長的通道。\n",me);
                me->move(__DIR__"tongdao1");
        }
        else
        {
                message_vision("$N在峯頂踩來踏去，踢得冰屑雪花濺飛，結果全無動靜。\n", me);
                me->receive_damage("qi",10);
        }
        return 1;
}