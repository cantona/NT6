// Room: /u/zqb/tiezhang/hclu.c

inherit ROOM;


void create()
{
        set("short", "荒草路");
        set("long", @LONG
你走一條荒蕪的小路上，兩旁荒草齊膝，荊棘遍地，似乎罕有人至。山
石壁立，遮天蔽日，鳥獸全無，四周籠罩在一片陰暗之中，使這裏看起來格
外深隧幽靜。
LONG        );
        set("exits", ([ /* sizeof() == 2 */
 "southdown" : __DIR__"hclu",
 "northwest" : __DIR__"hclu-3",
]));
        set("no_clean_up", 0);
    set("outdoors", "tiezhang");
        setup();
}
int valid_leave(object me, string dir)
{
 if ((dir != "northwest") && (dir != "southdown"));
 if (dir == "northwest"){
            me->receive_damage("qi", 50);       
            write("你的雙腿被荊棘刺破，鮮血流了出來。\n");
    }

 if (dir == "southdown"){
        me->receive_damage("qi", 50);       
        write("你的雙腿被荊棘刺破，鮮血流了出來。\n");
}
return 1;
}