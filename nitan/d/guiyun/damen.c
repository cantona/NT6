// Room: /guiyun/damen.c
// Date: Nov.18 1998 by Winder

inherit ROOM;

void create()
{
        set("short", "大門");
        set("long", @LONG
面前是一座莊院，門樓不甚高大，青磚綠瓦，灰色底的匾上寫著『
歸雲莊』三個大黑字。牌匾較為陳舊，邊角處的漆皮已剝落，露出暗黃
色的木質。看來掛在那已不下二十個春秋了。
LONG );
        set("outdoors", "guiyun");
        set("exits", ([
                "enter" : __DIR__"dayuan",
                "south" : __DIR__"shiqiao",
        ]));
        set("objects", ([
                __DIR__"npc/jiading" : 2,
        ]));
        set("coor/x", 280);
        set("coor/y", -830);
        set("coor/z", 0);
        setup();
}

int valid_leave(object me, string dir)
{
        mapping myfam;
        myfam=query("family", me);

        if ((!myfam || myfam["family_name"] != "桃花島") &&
                !query_temp("marks/guiyun", me) && dir == "enter" && 
                objectp(present("jia ding", environment(me))))
                return notify_fail("家丁做了個揖，說道：尊駕與敝莊素無往來，莊主不見外客，還是請回吧。\n");

        return ::valid_leave(me, dir);
}