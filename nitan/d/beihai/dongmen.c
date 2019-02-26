// /d/beihai/dongmen.c
// Last Modified by winder on May. 22 2002

inherit ROOM;

void create()
{
        set("short", "東門");
        set("long", @LONG
這裏是北海的東門，木製的門框被漆成了大紅色。雖然經過長期的雨打風吹，
顏色卻仍舊十分鮮豔。看的出是有人專門維護的。門上沒有顯著的標誌，但門口
站着幾個衞士在聊天。
LONG
        );
        set("exits", ([
                "south"     : __DIR__"shulin",
                "northeast" : __DIR__"huafang",
        ]));
        set("outdoors", "beihai");
        set("no_clean_up", 0);

        set("coor/x", -170);
        set("coor/y", 4080);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}