// Room: /d/yanziwu/langfang.c
// Date: Jan.28 2000 by Winder

inherit ROOM;

void create()
{
        set("short", "琅繯玉洞");
        set("long", @LONG
這裏就是武林中人皆欲一至的蔓陀山莊的琅繯玉洞。洞中收藏着當
年逍遙子和他的師妹李秋水收藏的普天下各門各派的武功祕籍。逍遙子
因門派變故，秋水伊人遠嫁西夏後，這些典籍被他們的女兒，蔓陀山莊
莊主從無量山琅繯玉洞千里迢迢運抵姑蘇，就藏在這個山洞之中。洞側
天窗一道，天窗外一線天光照着滿洞中都是書架，架上擺滿了顏色古舊
的書籍，架上均貼有標籤(sign)。
LONG );
        set("exits", ([
                "out"    : __DIR__"dong8",
        ]));
        set("item_desc", ([
                "sign" : "簽上標着少林、武當、青城、大理等門派的名稱。\n" 
        ]));
        set("objects", ([
                __DIR__"book/axe_book" : random(2),
                __DIR__"book/club_book" : random(2),
                __DIR__"book/hook_book" : random(2),
                __DIR__"book/whip_book" : random(2),
                __DIR__"book/staff_book" : random(2),
                __DIR__"book/stick_book" : random(2),
                __DIR__"book/spear_book" : random(2),
                __DIR__"book/sword_book" : random(2),
                __DIR__"book/blade_book" : random(2),
                __DIR__"book/hammer_book" : random(2),
                __DIR__"book/dagger_book" : random(2),
                __DIR__"book/throwing_book" : random(2),
        ]));
        set("coor/x", 1190);
        set("coor/y", -1270);
        set("coor/z", -2);
        setup();
        replace_program(ROOM);
}
