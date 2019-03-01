// Room: /d/gaochang/eroom1.c
// Last Modified by Winder on Jul. 15 2000

inherit ROOM;

void create()
{
        set("short", "東大殿");
        set("long", @LONG
每一間房中大都供有佛像。偶然在壁上見到幾個漢文，寫的是「高
昌國國王」，「文泰」，「大唐貞觀十三年」等等字樣。有一座殿堂中
供的都是漢人塑像，匾上寫的是「大成至聖先師孔子位」，左右各有數
十人，寫著「顏回」、「子路」、「子貢」、「子夏」、「子張」等名
字。
LONG
        );
        set("exits", ([        
                "north" : __DIR__"eroom2",
                "west"  : __DIR__"dadian",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -36490);
        set("coor/y", 10050);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}