// Room: /d/songshan/jianchi.c
// Last Modified by Winder on Jul. 15 2001

inherit ROOM;

void create()
{
        set("short", "劍池");
        set("long", @LONG
沒有親眼見到，沒幾個人會相信，在這嵩山絕頂之上，居然會有這
麼大一塘水。一炳長達五丈的鐵劍凌空橫臥水塘上，劍刃寬闊，劍尖非
常鋒銳，正是嵩山派慣常使用的劍。
    水塘往北延伸。東西有長廊跨水而過。
LONG );
        set("exits", ([
                "south" : __DIR__"huimengtang",
                "east"  : __DIR__"eastpath1",
                "west"  : __DIR__"westpath1",
        ]));
        set("outdoors", "songshan");
        set("objects", ([
                __DIR__"npc/tang": 1,
        ]));
        set("coor/x", -20);
        set("coor/y", 900);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}