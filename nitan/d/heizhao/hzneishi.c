// Room: /heizhao/hzneishi.c
// Date: Dec. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "黑沼內室");
        set("long", @LONG
內室牆壁圍成圓形，地下滿舖細沙，沙上畫著許多橫直符號和
圓圈，又寫著些“太”、“天元”、“地元”、“人元”、“物元
”等字。你看著地下符字，盡是些術數中的難題，是算經中的“天
元之術”。
LONG );
        set("no_clean_up", 0);

        set("exits", ([
                "south" : __DIR__"hzneitang",
        ]));
        set("coor/x", -5100);
        set("coor/y", -1470);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}