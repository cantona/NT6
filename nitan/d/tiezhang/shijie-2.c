// Room: /u/zqb/tiezhang/shijie-2.c

inherit ROOM;

void create()
{
        set("short", "石階");
        set("long", @LONG
只見一排石階盤旋而下，消失在濃濃的黑暗中。石階上長滿的綠色的青
苔，滑不留腳。遠處黑暗的盡頭似乎有點昏黃的光亮。
LONG        );
        set("exits", ([ /* sizeof() == 2 */
  "westup" : __DIR__"shijie-1",
  "northdown" : __DIR__"shijie-3",
]));
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}