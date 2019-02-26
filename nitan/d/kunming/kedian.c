#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "客棧");
        set("long", @LONG
這是一家價簡陋客棧，店鋪雖然不大，生意卻不錯，許多
過往的人都喜歡選擇這裏落腳，因為這裏的店主識得一些江湖
中人，所以很少有人會來此鬧事。店中的小二忙前忙後不停的
招呼着客人，就連店主也是滿臉笑容的陪着説好話。讓人覺的
有歸家的感覺一般。
LONG);
        set("no_fight", 1);
        set("valid_startroom", 1);
        set("no_sleep_room", 1);
        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
                __DIR__"npc/laoban" : 1,
        ]));
        set("exits", ([
                "west" : __DIR__"majiu",
                "east" : __DIR__"nandajie2",
                "westup" : __DIR__"kedian1",
        ]));
	set("coor/x", -16850);
	set("coor/y", -7230);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{

        if (! me->query_temp("rent_paid") && dir == "westup" )
        return notify_fail(CYN "元財對你賠笑道：這位客官，請先這裏"
                           "付了錢再上樓住店。\n" NOR);
        return ::valid_leave(me, dir);
}