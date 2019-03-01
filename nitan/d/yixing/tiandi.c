// Room: /yixing/tiandi.c
// Date: Nov.18 1998 by Winder

inherit ROOM;

void create()
{
        set("short", "田地");
        set("long", @LONG
這裡是一片農田。不遠處有一些村莊，炊煙裊裊升起。村莊周圍是
一塊塊的田地，很有次序的排成一個個井字，田裡有一些正在耕作的農
人，過路人貪近路也可以從田間井字分割的小徑穿過。
LONG );
        set("outdoors", "yixing");
        set("exits", ([
                "west"      : __DIR__"yixing",
                "northeast" : __DIR__"shulin5",
        ]));
        set("objects", ([
                __DIR__"npc/banjiu" : 1,
        ]));
        set("coor/x", 240);
	set("coor/y", -1020);
	set("coor/z", 0);
	setup();
}
int valid_leave(object me, string dir)
{
        int c_exp,c_skill;
        if (userp(me))
        if (dir == "west" )
        {
                me->receive_damage("qi", 10);
                tell_object(me,"你走上田間突起的小土□，覺的很是狹窄，慢慢的走了進去。\n");
        }
        else
        {
                me->receive_damage("qi", 10);
                message_vision("$N踩著田間的小土□，慢慢向前走去。\n", me);
        }
        return 1;
}