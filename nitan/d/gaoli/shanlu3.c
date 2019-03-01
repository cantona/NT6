// /d/gaoli/xuanwumen
// Room in 高麗
inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
這裡是一條山路。東邊是一條繹道。這裡的山路崎嶇曲折，你不禁
小心起來。抬頭望去，西邊有一個烽火台。這裡已經沒有什麼行人了。
LONG
        );

        set("exits", ([
                "northeast" : __DIR__"edao2",
                "westup":__DIR__"shanlu4",
        ]));
         set("outdoors", "gaoli");
        setup();
        replace_program(ROOM);
}


