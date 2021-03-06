// Room: /d/shaolin/zoulang4.c
// Date: YZC 96/01/19

inherit ROOM;

string look_poem();

void create()
{
        set("short", "走廊");
        set("long", @LONG
這裏是禪房走廊。房頂一側支在南面的高牆上，另一側則與北邊
羅漢堂的屋頂相連。彩樑畫棟，連頂棚也用彩漆繪滿了各種飛天的圖
形，每幅畫似乎都在訴説一個娓娓動人的佛經故事。南邊牆上題着一
首詩(poem)。往北通往羅漢堂。
LONG );
        set("exits", ([
                "west" : __DIR__"zoulang3",
                "north" : __DIR__"luohan1",
        ]));
        set("item_desc",([
                "poem"                :        (: look_poem :),
        ]));
        set("no_clean_up", 0);
        setup();
}

string look_poem()
{
        return
        "\n"
        "    ※※※※※※※※※※※※※※※※※※※※※※※※※※\n"
        "    ※※※※※※※　　　　　　　　　　　　※※※※※※※\n"
        "    ※※※※※※※　　　　舍利子，　　　　※※※※※※※\n"
        "    ※※※※※※※　　　　　　　　　　　　※※※※※※※\n"
        "    ※※※※※※※  色不異空，空不異色；　※※※※※※※\n"
        "    ※※※※※※※　　　　　　　　　　　　※※※※※※※\n"
        "    ※※※※※※※  色即是空，空即是色。　※※※※※※※\n"
        "    ※※※※※※※　　　　　　　　　　　　※※※※※※※\n"
        "    ※※※※※※※  受想行識，亦復如是。　※※※※※※※\n"
        "    ※※※※※※※　　　　　　　　　　　　※※※※※※※\n"
        "    ※※※※※※※　　　　舍利子，　　　　※※※※※※※\n"
        "    ※※※※※※※　　　　　　　　　　　　※※※※※※※\n"
        "    ※※※※※※※  是諸法相，不生不滅，　※※※※※※※\n"
        "    ※※※※※※※　　　　　　　　　　　　※※※※※※※\n"
        "    ※※※※※※※  不垢不淨，不增不減。　※※※※※※※\n"
        "    ※※※※※※※　　　　　　　　　　　　※※※※※※※\n"
        "    ※※※※※※※※※※※※※※※※※※※※※※※※※※\n";
}
