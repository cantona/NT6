// Room: /u/zqb/tiezhang/hclu.c

inherit ROOM;


void create()
{
        set("short", "荒草路");
        set("long", @LONG
你走一條荒蕪的小路上，兩旁荒草齊膝，荊棘遍地，似乎罕有人至。山
石壁立，遮天蔽日，鳥獸全無，四周籠罩在一片陰暗之中，使這裡看起來格
外深隧幽靜。
LONG        );
        set("exits", ([ /* sizeof() == 2 */
 "southeast" : __DIR__"hclu-2",
 "northup" : __DIR__"hclu-4",
]));
        set("no_clean_up", 0);
    set("outdoors", "tiezhang");
        setup();
}
int valid_leave(object me, string dir)
{
 if ((dir != "northup") && (dir != "southeast"));
 if (dir == "northup"){
            me->receive_damage("qi", 50);       
            write("你的雙腿被荊棘刺破，鮮血流了出來。\n");
    }

 if (dir == "southeast"){
        me->receive_damage("qi", 50);       
        write("你的雙腿被荊棘刺破，鮮血流了出來。\n");
}
return 1;
}