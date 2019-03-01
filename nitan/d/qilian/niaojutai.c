// Room: /d/qilian/niaojutai.c
// Winder 2000/09/05 

inherit ROOM;

void create()
{
        set("short", "鳥居台");
        set("long", @LONG
沿著大通嶺往上走，道路癒顯艱難。沿途荊棘叢生，怪石嶙嶙，眼
見已是獸跡罕至了，卻有百鳥群飛，兩耳只聞啾啾之聲。仰頭望天，一
片碧藍之下，耳畔鳥鳴，蒼蒼大地，盡在腳下，不禁豪情頓生。
LONG );
        set("outdoors", "qilian");
        set("exits", ([
                "eastdown" : __DIR__"datongling",
                "northup"  : __DIR__"mazongshan",
                "northwest": __DIR__"qilianshan",
        ]));
        set("objects", ([
                "/d/hangzhou/npc/wuya"  : random(3),
                "/d/hangzhou/npc/maque" : random(3),
        ]));
        set("coor/x", -11000);
        set("coor/y", 3000);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}