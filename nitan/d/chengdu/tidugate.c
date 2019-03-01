#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "提督府門");
        set("long", @LONG
這便是提督府門。巍峨雄偉的城牆上，成都提督府五個大字十分
顯眼，氣勢輝煌。幾名親兵立在兩旁。
LONG );
        set("outdoors", "chengdu");
        set("exits", ([
            "south" : __DIR__"guangchang",
            "north" : __DIR__"tidufu",
        ]));
        set("objects", ([
            __DIR__"npc/qinbing" : 2,
        ]));
        set("coor/x", -15220);
	set("coor/y", -1820);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        int i;
        object bing;

        bing = present("qin bing", environment(me));
        if (dir != "north" || ! objectp(bing) || ! living(bing))
                return ::valid_leave(me, dir);

        if( query("weiwang", me) >= 10000 )
        {
                message_vision(CYN "$N" CYN "笑道：" + RANK_D->query_respect(me) +
                               "請進，請進！這就去讓人通報。\n" NOR, bing, me);
                return ::valid_leave(me, dir);
        }

        if( query("special_skill/trick", me) )
        {
                message_vision(CYN "$N" CYN "看見$n" CYN "走了過來，剛想攔住，卻"
                               "聽$n" CYN "一聲斷喝：給我散開！\n$N" CYN "不由得"
                               "嚇了一跳，訕訕的不敢說話。\n" NOR, bing, me);
                return ::valid_leave(me, dir);
        }

        return notify_fail(CYN "親兵上前擋住你，朗聲說道：這位" +
                           RANK_D->query_respect(me) + "請回吧。老爺不見客。\n" NOR);
}