#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "廣場");
        set("long", @LONG
山路行到這裏，忽然變得開闊，你眼前出現了一片很大的廣場。一些鐵
掌幫的弟子來回穿梭於其間，顯得很忙碌。在廣場的周圍有很多巖石建的房
子。正面的這間尤其顯得高大雄偉。左面的房子中不時的湧出陣陣熱氣，其
間還加雜着鼓風的聲音。
LONG    );
        set("exits", ([
                "south" : __DIR__"shanlu-2",
                "west" : __DIR__"lgfang",
                "east" : __DIR__"guajia",
                "northup" : __DIR__"wztang",
        ]));

        set("objects", ([
                __DIR__"npc/huiyi" : 1,
                __DIR__"npc/heiyi" : 2,
                CLASS_D("tiezhang") + "/fen" : 1,
        ]));

        set("valid_startroom", 1);
        set("no_clean_up", 0);
        set("outdoors", "tiezhang");

        setup();

        "/clone/board/tiezhang_b"->foo();
}

int valid_leave(object me, string dir)
{
        int i;
        object ob;
        me = this_player();
        if(dir == "northup")
        {
                if( query("family/family_name", me) != "鐵掌幫"
                   & objectp(present("feng yong", environment(me)))
                   &!query("move_party/絕情谷—鐵掌幫", me) )
                        return notify_fail(CYN "馮勇身形一晃，忽然擋住你，厲聲説道：這位" +
                                           RANK_D->query_respect(me) + CYN "不是本幫弟子，"
                                           "休得在本幫亂闖。\n" NOR);
        }
        return ::valid_leave(me, dir);
}
