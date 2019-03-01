// /d/beihai/yongansi.c
// Last Modified by winder on May. 22 2002
inherit ROOM;

void create()
{
        set("short", "永安寺");
        set("long", @LONG
這裡是永安寺，歷史已經很悠久了。由永安寺北上就可到達白塔。
永安寺南是一座石橋，名永安石橋，是連接白塔山和團城的通道。
LONG
        );
        set("exits", ([
                "west"      : __DIR__"yuexin",
                "south"     : __DIR__"yonganqiao",
                "northup"   : __DIR__"baita",
                "northeast" : __DIR__"zhizhu",
        ]));
        set("outdoors", "beihai");
        set("no_clean_up", 0);

        set("coor/x", -190);
        set("coor/y", 4080);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}