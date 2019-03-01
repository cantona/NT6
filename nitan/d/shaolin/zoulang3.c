// Room: /d/shaolin/zoulang3.c
// Date: YZC 96/01/19

inherit ROOM;

string look_duizi();

void create()
{
        set("short", "走廊");
        set("long", @LONG
這裏是禪房走廊。房頂一側支在南面的高牆上，另一側則與北邊
和尚院的屋頂相連。彩樑畫棟，連頂棚也用彩漆繪滿了各種飛天的圖
形，每幅畫似乎都在訴説一個娓娓動人的佛經故事。南邊牆上掛着一
幅對子(duizi)。北望可以觀賞僧眾們練武的場面。
LONG );
        set("exits", ([
                "east" : __DIR__"zoulang4",
                "west" : __DIR__"houdian",
                "north" : __DIR__"wuchang2",
        ]));
        set("item_desc",([
                "duizi"                :        (: look_duizi :),
        ]));
        set("objects",([
                CLASS_D("shaolin") + "/dao-pin" : 1,
        ]));
//        set("no_clean_up", 0);
        setup();
}

string look_duizi()
{
        return
        "\n"
        "    ※※※※※※※※※※※※※※※※※※※※※※※※※※\n"
        "    ※※※※　　　　　　　※※※※　　　　　　　※※※※\n"
        "    ※※※※　　　一　　　※※※※　　　和　　　※※※※\n"
        "    ※※※※　　　　　　　※※※※　　　　　　　※※※※\n"
        "    ※※※※　　　體　　　※※※※　　　合　　　※※※※\n"
        "    ※※※※　　　　　　　※※※※　　　　　　　※※※※\n"
        "    ※※※※　　　真　　　※※※※　　　四　　　※※※※\n"
        "    ※※※※　　　　　　　※※※※　　　　　　　※※※※\n"
        "    ※※※※　　　如　　　※※※※　　　相　　　※※※※\n"
        "    ※※※※　　　　　　　※※※※　　　　　　　※※※※\n"
        "    ※※※※　　　轉　　　※※※※　　　復　　　※※※※\n"
        "    ※※※※　　　　　　　※※※※　　　　　　　※※※※\n"
        "    ※※※※　　　落　　　※※※※　　　修　　　※※※※\n"
        "    ※※※※　　　　　　　※※※※　　　　　　　※※※※\n"
        "    ※※※※　　　塵　　　※※※※　　　身　　　※※※※\n"
        "    ※※※※　　　　　　　※※※※　　　　　　　※※※※\n"
        "    ※※※※※※※※※※※※※※※※※※※※※※※※※※\n";
}
