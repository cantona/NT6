// Room: /d/suzhou/zhishuang.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "致爽閣");
        set("long", @LONG
在千人石西面就是致爽閣，又名伏虎閣，在虎丘塔的西南面，是山
上的最高點。閣名取“四山爽氣，日夕西來”之意。舊稱“小五台”，
是海湧峯頂。閣外平台寬闊，俯瞰沃野；遠眺羣峯逶迤，可賞著名上午
“獅子回頭看虎丘”一景。深秋季節觀成羣飛翔的蒼鷹，蔚為壯觀。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "southeast" : __DIR__"qianrenshi",
        ]));
        set("objects", ([
                __DIR__"npc/lady1" :1,
        ]));
	set("coor/x", 1090);
	set("coor/y", -1030);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}