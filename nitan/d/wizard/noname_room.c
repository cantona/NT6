// /d/wizard/guest_room.c

#include <room.h>
#include <ansi.h>

inherit ROOM;

int is_chat_room() { return 1; }

void create()
{
        set("short", HIR "匿名留言室" NOR);
        set("long", @LONG
如果您有問題留言給泥潭巫師但又不想其他玩家看到，那麼您可
以在這裏(post)，其他玩家將不能看到您的留言，在這裏您可以舉報
有問題的id和其他作弊行為，泥潭巫師將為您的留言完全保密。    
                                    ==泥潭製作羣==
LONG );

        set("exits", ([
                "south": __DIR__"guest_room",              
        ]));

        set("no_fight", 1);

        set("coor/x", 10000);
        set("coor/y", 10010);
        set("coor/z", 9990);
        setup();
        "/clone/board/noname_b"->foo();
}

int valid_leave(object me, string dir)
{
        if (dir == "west" && ! wizardp(me))
                return notify_fail("只有巫師才能進去！\n");

        return ::valid_leave(me, dir);
}