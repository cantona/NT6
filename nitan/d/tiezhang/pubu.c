// Room: /u/zqb/tiezhang/pubu.c

inherit ROOM;

void create()
{
        set("short", "瀑布");
        set("long", @LONG
山路行到這裡，忽聽遠處傳來隱隱水聲，轉過一道山樑，只見一道白龍
似的大瀑布從對面雙峰之間奔騰而下，空山寂寂，那水聲不斷在山谷中激盪
回響，聲勢甚是驚人。
LONG        );
        set("exits", ([ /* sizeof() == 2 */
  "northup" : __DIR__"xzfeng",
  "eastdown" : __DIR__"sblu-1",
]));
        set("no_clean_up", 0);

        setup();
}