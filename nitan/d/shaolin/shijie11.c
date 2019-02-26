// Room: /d/shaolin/shijie11.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "石階");
        set("long", @LONG
松林漸漸開闊，面前出現了一條寬廣的石板道，筆直通向前方。
沿道稀稀落落地種着幾棵柏樹，卻顯得高大挺拔，蝤龍般的枝幹向天
空高高伸展着。
LONG );
        set("exits", ([
                "southdown" : __DIR__"shijie10",
                "north" : __DIR__"guangchang1",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "shaolin");
        setup();
}

int valid_leave(object me, string dir)
{
        if( query("id", me) == "sengbing" && dir == "southdown" )
                return 0;

        return ::valid_leave(me, dir);
}
