// shijie.c
inherit ROOM;

void create()
{
        set("short", "孤山石級");
        set("long", @LONG
你向孤山邊的石級上行去，一路欣賞着湖邊長曳的楊柳。不知不
覺地轉了幾個彎，卻見遍地都是梅樹，老幹橫斜，枝葉茂密，想像初
春梅花盛開之日，香雪如海，定然觀賞不盡。
LONG );
        set("exits", ([ /* sizeof() == 2 */
            "eastdown" : "/d/hangzhou/gushan",
            "north"    : __DIR__"xiaolu.c",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "meizhuang");

        setup();
        replace_program(ROOM);
}
