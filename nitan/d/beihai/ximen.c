// /d/beihai/ximen.c
// Last Modified by winder on May. 22 2002

inherit ROOM;

void create()
{
        set("short", "西門");
        set("long", @LONG
這裏是北海的西門，木製的門框被漆成了大紅色。雖然經過長期的
雨打風吹，顏色卻仍舊十分鮮豔。看的出是有人專門維護的。門上沒有
顯著的標誌，但門口站着幾個衞士在聊天。東面遠遠可以看見團城上飄
揚的旗幟。
LONG
        );
        set("exits", ([
                "east"       : __DIR__"yanxiang",
                "north"      : __DIR__"xiaolu1",
                "south"  : "/d/beijing/cagc_w",
        ]));
        set("outdoors", "beihai");
        set("no_clean_up", 0);

        set("coor/x", -200);
        set("coor/y", 4050);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}